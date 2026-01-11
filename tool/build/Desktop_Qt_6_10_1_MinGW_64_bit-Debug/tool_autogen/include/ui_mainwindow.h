/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "bfnpreviewwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionSave;
    QAction *actionClose;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionRedo;
    QAction *actionSave_As;
    QAction *actionAbout;
    QAction *actionExport_to_JSON;
    QAction *actionImport_to_JSON;
    QAction *actionImport_Folder;
    QAction *actionImport_Font;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *Tab_action;
    QWidget *Tab_translator;
    QVBoxLayout *verticalLayout_7;
    QSplitter *splitter;
    QWidget *leftPanel;
    QVBoxLayout *verticalLayout;
    QLineEdit *txtsearch;
    QTableView *tblList;
    QWidget *centerPanel;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTextEdit *txtOriginal;
    QLabel *label_2;
    QTextEdit *txtTranslation;
    QWidget *rightPanel;
    QVBoxLayout *verticalLayout_3;
    BfnPreviewWidget *widget;
    QWidget *Tab_font;
    QVBoxLayout *verticalLayout_6;
    QSplitter *splitter_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_8;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *lblFontTexture;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *txtHexCode;
    QSpinBox *spinWidth;
    QSpinBox *spinAdvance;
    QPushButton *btnUpdateFont;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuPlugins;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 800);
        actionNew_Project = new QAction(MainWindow);
        actionNew_Project->setObjectName("actionNew_Project");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/res/new.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionNew_Project->setIcon(icon);
        actionOpen_Project = new QAction(MainWindow);
        actionOpen_Project->setObjectName("actionOpen_Project");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/res/open.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionOpen_Project->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/res/save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSave->setIcon(icon2);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName("actionClose");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/res/close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionClose->setIcon(icon3);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/res/exit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionExit->setIcon(icon4);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/res/undo.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionUndo->setIcon(icon5);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/image/res/cut.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionCut->setIcon(icon6);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/image/res/copy.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionCopy->setIcon(icon7);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/image/res/paste.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionPaste->setIcon(icon8);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName("actionRedo");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/image/res/redo.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionRedo->setIcon(icon9);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName("actionSave_As");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/image/res/save as.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSave_As->setIcon(icon10);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionExport_to_JSON = new QAction(MainWindow);
        actionExport_to_JSON->setObjectName("actionExport_to_JSON");
        actionImport_to_JSON = new QAction(MainWindow);
        actionImport_to_JSON->setObjectName("actionImport_to_JSON");
        actionImport_Folder = new QAction(MainWindow);
        actionImport_Folder->setObjectName("actionImport_Folder");
        actionImport_Font = new QAction(MainWindow);
        actionImport_Font->setObjectName("actionImport_Font");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        Tab_action = new QTabWidget(centralwidget);
        Tab_action->setObjectName("Tab_action");
        Tab_translator = new QWidget();
        Tab_translator->setObjectName("Tab_translator");
        verticalLayout_7 = new QVBoxLayout(Tab_translator);
        verticalLayout_7->setObjectName("verticalLayout_7");
        splitter = new QSplitter(Tab_translator);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        leftPanel = new QWidget(splitter);
        leftPanel->setObjectName("leftPanel");
        leftPanel->setEnabled(true);
        verticalLayout = new QVBoxLayout(leftPanel);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(11, -1, -1, -1);
        txtsearch = new QLineEdit(leftPanel);
        txtsearch->setObjectName("txtsearch");
        txtsearch->setEnabled(false);

        verticalLayout->addWidget(txtsearch);

        tblList = new QTableView(leftPanel);
        tblList->setObjectName("tblList");
        tblList->setAlternatingRowColors(true);
        tblList->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tblList->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout->addWidget(tblList);

        splitter->addWidget(leftPanel);
        centerPanel = new QWidget(splitter);
        centerPanel->setObjectName("centerPanel");
        centerPanel->setEnabled(true);
        verticalLayout_2 = new QVBoxLayout(centerPanel);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(centerPanel);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        txtOriginal = new QTextEdit(centerPanel);
        txtOriginal->setObjectName("txtOriginal");

        verticalLayout_2->addWidget(txtOriginal);

        label_2 = new QLabel(centerPanel);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        txtTranslation = new QTextEdit(centerPanel);
        txtTranslation->setObjectName("txtTranslation");

        verticalLayout_2->addWidget(txtTranslation);

        splitter->addWidget(centerPanel);
        rightPanel = new QWidget(splitter);
        rightPanel->setObjectName("rightPanel");
        rightPanel->setEnabled(true);
        verticalLayout_3 = new QVBoxLayout(rightPanel);
        verticalLayout_3->setObjectName("verticalLayout_3");
        widget = new BfnPreviewWidget(rightPanel);
        widget->setObjectName("widget");

        verticalLayout_3->addWidget(widget);

        splitter->addWidget(rightPanel);

        verticalLayout_7->addWidget(splitter);

        Tab_action->addTab(Tab_translator, QString());
        Tab_font = new QWidget();
        Tab_font->setObjectName("Tab_font");
        verticalLayout_6 = new QVBoxLayout(Tab_font);
        verticalLayout_6->setObjectName("verticalLayout_6");
        splitter_2 = new QSplitter(Tab_font);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Orientation::Horizontal);
        widget_2 = new QWidget(splitter_2);
        widget_2->setObjectName("widget_2");
        verticalLayout_8 = new QVBoxLayout(widget_2);
        verticalLayout_8->setObjectName("verticalLayout_8");
        scrollArea = new QScrollArea(widget_2);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 862, 608));
        lblFontTexture = new QLabel(scrollAreaWidgetContents);
        lblFontTexture->setObjectName("lblFontTexture");
        lblFontTexture->setGeometry(QRect(10, 10, 63, 20));
        lblFontTexture->setScaledContents(true);
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_8->addWidget(scrollArea);

        splitter_2->addWidget(widget_2);
        widget_3 = new QWidget(splitter_2);
        widget_3->setObjectName("widget_3");
        verticalLayout_5 = new QVBoxLayout(widget_3);
        verticalLayout_5->setObjectName("verticalLayout_5");
        groupBox = new QGroupBox(widget_3);
        groupBox->setObjectName("groupBox");
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        txtHexCode = new QLineEdit(groupBox);
        txtHexCode->setObjectName("txtHexCode");

        verticalLayout_4->addWidget(txtHexCode);

        spinWidth = new QSpinBox(groupBox);
        spinWidth->setObjectName("spinWidth");

        verticalLayout_4->addWidget(spinWidth);

        spinAdvance = new QSpinBox(groupBox);
        spinAdvance->setObjectName("spinAdvance");

        verticalLayout_4->addWidget(spinAdvance);

        btnUpdateFont = new QPushButton(groupBox);
        btnUpdateFont->setObjectName("btnUpdateFont");

        verticalLayout_4->addWidget(btnUpdateFont);


        verticalLayout_5->addWidget(groupBox);

        splitter_2->addWidget(widget_3);

        verticalLayout_6->addWidget(splitter_2);

        Tab_action->addTab(Tab_font, QString());

        horizontalLayout->addWidget(Tab_action);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuPlugins = new QMenu(menubar);
        menuPlugins->setObjectName("menuPlugins");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuPlugins->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionClose);
        menuFile->addAction(actionExit);
        menuFile->addAction(actionImport_Folder);
        menuFile->addAction(actionImport_Font);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addAction(actionExport_to_JSON);
        menuEdit->addAction(actionImport_to_JSON);
        menuHelp->addAction(actionAbout);
        toolBar->addAction(actionNew_Project);
        toolBar->addAction(actionOpen_Project);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSave_As);
        toolBar->addAction(actionCopy);
        toolBar->addAction(actionPaste);
        toolBar->addAction(actionCut);
        toolBar->addAction(actionRedo);
        toolBar->addAction(actionUndo);

        retranslateUi(MainWindow);

        Tab_action->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew_Project->setText(QCoreApplication::translate("MainWindow", "New Project       ctrl+n", nullptr));
        actionOpen_Project->setText(QCoreApplication::translate("MainWindow", "Open Project         ctrl+o", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save                    ctrl+s", nullptr));
        actionClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo         ctrl+z", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut             ctrl+x", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy          ctrl+c", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste          ctrl+v", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo         ctrl+y", nullptr));
        actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionExport_to_JSON->setText(QCoreApplication::translate("MainWindow", "Export to JSON", nullptr));
        actionImport_to_JSON->setText(QCoreApplication::translate("MainWindow", "Import to JSON", nullptr));
        actionImport_Folder->setText(QCoreApplication::translate("MainWindow", "Import Folder", nullptr));
        actionImport_Font->setText(QCoreApplication::translate("MainWindow", "Import Font", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        Tab_action->setTabText(Tab_action->indexOf(Tab_translator), QCoreApplication::translate("MainWindow", "Translator", nullptr));
        lblFontTexture->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "th\303\264ng s\341\273\221", nullptr));
        btnUpdateFont->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        Tab_action->setTabText(Tab_action->indexOf(Tab_font), QCoreApplication::translate("MainWindow", "Font", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuPlugins->setTitle(QCoreApplication::translate("MainWindow", "Plugins", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
