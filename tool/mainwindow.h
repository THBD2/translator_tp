#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "translationmodel.h"
#include "bmghandler.h" // Xử lý file BMG
#include "rarchandler.h" // Xử lý file ARC/Yaz0

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // File Actions
    void on_actionNew_Project_triggered();
    void on_actionOpen_Project_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();

    // Import Actions
    void on_actionImport_Folder_triggered();
    void on_actionImport_Font_triggered();

    // Edit Actions
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();

private:
    Ui::MainWindow *ui;
    TranslationModel *m_model;

    // Handlers
    BmgHandler m_bmgHandler;

    QString m_currentProjectPath;

    // Helper Functions
    void saveProject(const QString& path);
    void setProjectActionsEnabled(bool enabled);
    void parseBmgFile(const QString& filePath);

    // Hàm mới để xử lý file ARC
    void parseArcFile(const QString& filePath);
};

#endif // MAINWINDOW_H
