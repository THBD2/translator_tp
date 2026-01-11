#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QLineEdit>
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>

// Include các bộ xử lý
#include "yaz0.h"
#include "rarchandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. CẤU HÌNH GIAO DIỆN
    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);
    ui->splitter->setStretchFactor(2, 1);
    ui->splitter->setSizes(QList<int>() << 350 << 500 << 500);

    ui->splitter_2->setStretchFactor(0, 1);
    ui->splitter_2->setStretchFactor(1, 0);
    ui->splitter_2->setSizes(QList<int>() << 900 << 200);

    // 2. SETUP MODEL
    m_model = new TranslationModel(this);
    ui->tblList->setModel(m_model);

    // Trang trí bảng
    QFont listFont = ui->tblList->font();
    listFont.setPointSize(10);
    ui->tblList->setFont(listFont);
    ui->tblList->verticalHeader()->setDefaultSectionSize(30);
    ui->tblList->verticalHeader()->setVisible(false);
    ui->tblList->setAlternatingRowColors(true);
    ui->tblList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tblList->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    // 3. KẾT NỐI SỰ KIỆN
    connect(ui->tblList->selectionModel(), &QItemSelectionModel::currentChanged,
            [this](const QModelIndex &current, const QModelIndex &prev) {
                if (!current.isValid()) return;
                auto item = m_model->getEntry(current.row());
                ui->txtOriginal->setPlainText(item.original);
                ui->txtTranslation->setPlainText(item.translated);
                ui->widget->setText(item.translated.isEmpty() ? item.original : item.translated);
            });

    connect(ui->txtTranslation, &QTextEdit::textChanged, [this]() {
        QString text = ui->txtTranslation->toPlainText();
        ui->widget->setText(text);
        QModelIndex idx = ui->tblList->currentIndex();
        if (idx.isValid()) {
            m_model->updateTranslation(idx.row(), text);
        }
    });

    // 4. TRẠNG THÁI KHỞI ĐẦU
    setProjectActionsEnabled(false);
    setWindowTitle("Tool Việt Hóa - Chưa mở Project");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// =========================================================
// HELPER FUNCTIONS
// =========================================================
void MainWindow::setProjectActionsEnabled(bool enabled)
{
    ui->actionImport_Folder->setEnabled(enabled);
    ui->actionImport_Font->setEnabled(enabled);
    ui->actionSave->setEnabled(enabled);
    ui->actionSave_As->setEnabled(enabled);
    ui->actionClose->setEnabled(enabled);
    ui->txtTranslation->setEnabled(enabled);
    ui->tblList->setEnabled(enabled);
}

// =========================================================
// PROJECT ACTIONS
// =========================================================
void MainWindow::on_actionNew_Project_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Tạo Project Mới", "", "Twilight Hylian Binary (*.thb)");
    if (fileName.isEmpty()) return;

    m_currentProjectPath = fileName;
    m_model->setEntries({});
    ui->txtOriginal->clear();
    ui->txtTranslation->clear();
    ui->widget->setText("");

    saveProject(m_currentProjectPath);
    setProjectActionsEnabled(true);
}

void MainWindow::on_actionOpen_Project_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Mở Project", "", "Twilight Hylian Binary (*.thb)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray encryptedData = file.readAll();
    file.close();
    QByteArray jsonData = QByteArray::fromBase64(encryptedData);
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (doc.isNull()) {
        QMessageBox::critical(this, "Lỗi", "File bị hỏng!");
        return;
    }

    QJsonObject root = doc.object();
    m_model->fromJson(root["data"].toArray());

    m_currentProjectPath = fileName;
    setWindowTitle("Tool Việt Hóa - " + fileName);
    QMessageBox::information(this, "Thành công", "Đã tải dự án!");

    setProjectActionsEnabled(true);
}

void MainWindow::saveProject(const QString& path)
{
    QJsonObject root;
    root["version"] = "1.0";
    root["data"] = m_model->toJson();
    QByteArray encryptedData = QJsonDocument(root).toJson().toBase64();

    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(encryptedData);
        file.close();
        setWindowTitle("Tool Việt Hóa - " + path);
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (m_currentProjectPath.isEmpty()) on_actionSave_As_triggered();
    else {
        saveProject(m_currentProjectPath);
        QMessageBox::information(this, "Đã lưu", "Lưu thành công!");
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Lưu Project", "", "Twilight Hylian Binary (*.thb)");
    if (!fileName.isEmpty()) {
        m_currentProjectPath = fileName;
        saveProject(fileName);
    }
}

void MainWindow::on_actionClose_triggered()
{
    m_model->setEntries({});
    ui->txtOriginal->clear();
    ui->txtTranslation->clear();
    ui->widget->setText("");
    m_currentProjectPath = "";
    setWindowTitle("Tool Việt Hóa - Chưa mở Project");
    setProjectActionsEnabled(false);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

// =========================================================
// IMPORT LOGIC
// =========================================================

void MainWindow::on_actionImport_Folder_triggered()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "Chọn thư mục Game", "");
    if (dirPath.isEmpty()) return;

    QStringList filters;
    filters << "*.bmg" << "*.arc";

    QDirIterator it(dirPath, filters, QDir::Files, QDirIterator::Subdirectories);

    int count = 0;
    while (it.hasNext()) {
        QString filePath = it.next();

        if (filePath.endsWith(".bmg", Qt::CaseInsensitive)) {
            parseBmgFile(filePath);
            count++;
        }
        else if (filePath.endsWith(".arc", Qt::CaseInsensitive)) {
            parseArcFile(filePath);
            count++;
        }
    }

    if (count > 0) QMessageBox::information(this, "Xong", QString("Đã xử lý %1 file.").arg(count));
    else QMessageBox::warning(this, "Lỗi", "Không tìm thấy file .bmg hoặc .arc nào!");
}

void MainWindow::parseBmgFile(const QString &filePath)
{
    std::vector<TranslationEntry> entries = m_bmgHandler.loadBmg(filePath);
    QFileInfo fi(filePath);
    QString fileName = fi.fileName();

    for (const auto& entry : entries) {
        TranslationEntry newEntry = entry;
        newEntry.id = fileName + "_" + entry.id;
        m_model->appendEntry(newEntry);
    }
} // <--- LẦN TRƯỚC BẠN THIẾU DẤU NÀY NÈ

void MainWindow::parseArcFile(const QString &filePath)
{
    qDebug() << "🚀 Processing:" << filePath;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return;

    // 1. ĐỌC VÀO RAM
    QByteArray data = file.readAll();
    file.close();

    // 2. GIẢI NÉN YAZ0 (Tách biệt)
    if (Yaz0::isYaz0(data)) {
        qDebug() << ">> Yaz0 detected. Decompressing...";
        data = Yaz0::decode(data);
        qDebug() << ">> Decompressed Size:" << data.size();
    } else {
        qDebug() << ">> Raw RARC detected.";
    }

    // 3. PARSE RARC
    RarcHandler rarc;
    QVector<VirtualFile> files = rarc.parse(data);

    if (files.isEmpty()) {
        qDebug() << "⚠️ No BMG files found or extract failed.";
        return;
    }

    QFileInfo fi(filePath);
    QString arcName = fi.fileName();

    // 4. LOAD VÀO TOOL
    for (const auto& vf : files) {
        std::vector<TranslationEntry> entries = m_bmgHandler.loadBmgFromData(vf.data);

        for (const auto& entry : entries) {
            TranslationEntry newEntry = entry;
            newEntry.id = arcName + "_" + vf.fileName + "_" + entry.id;
            m_model->appendEntry(newEntry);
        }
        qDebug() << "   Loaded" << entries.size() << "lines from" << vf.fileName;
    }
}

void MainWindow::on_actionImport_Font_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Chọn Font Texture", "", "Images (*.png *.jpg)");
    if (fileName.isEmpty()) return;

    QPixmap pixmap(fileName);
    if (!pixmap.isNull()) {
        ui->lblFontTexture->setPixmap(pixmap);
        ui->lblFontTexture->adjustSize();
        ui->Tab_action->setCurrentIndex(1);
    }
}

// =========================================================
// EDIT ACTIONS
// =========================================================
void MainWindow::on_actionUndo_triggered() {
    QWidget *w = QApplication::focusWidget();
    if (auto edit = qobject_cast<QTextEdit*>(w)) edit->undo();
    else if (auto line = qobject_cast<QLineEdit*>(w)) line->undo();
}
void MainWindow::on_actionRedo_triggered() {
    QWidget *w = QApplication::focusWidget();
    if (auto edit = qobject_cast<QTextEdit*>(w)) edit->redo();
    else if (auto line = qobject_cast<QLineEdit*>(w)) line->redo();
}
void MainWindow::on_actionCut_triggered() {
    QWidget *w = QApplication::focusWidget();
    if (auto edit = qobject_cast<QTextEdit*>(w)) edit->cut();
    else if (auto line = qobject_cast<QLineEdit*>(w)) line->cut();
}
void MainWindow::on_actionCopy_triggered() {
    QWidget *w = QApplication::focusWidget();
    if (auto edit = qobject_cast<QTextEdit*>(w)) edit->copy();
    else if (auto line = qobject_cast<QLineEdit*>(w)) line->copy();
}
void MainWindow::on_actionPaste_triggered() {
    QWidget *w = QApplication::focusWidget();
    if (auto edit = qobject_cast<QTextEdit*>(w)) edit->paste();
    else if (auto line = qobject_cast<QLineEdit*>(w)) line->paste();
}
