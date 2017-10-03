/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionMTT;
    QAction *actionPF;
    QAction *actionOpenVideo;
    QAction *actionCT;
    QAction *actionHash;
    QAction *actionKCF;
    QAction *actionSTC;
    QAction *actionSTRUCK;
    QAction *actionCTL;
    QAction *actionKCFL;
    QAction *actionHashL;
    QAction *actionSTCL;
    QAction *actionSTRUCKL;
    QAction *actionPFL;
    QAction *actionMD;
    QAction *actionTR;
    QAction *actionMTCL;
    QAction *actionAbout;
    QAction *actionReturn;
    QAction *actionClose;
    QAction *actionMTL;
    QWidget *centralWidget;
    QGroupBox *frontBox;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_T;
    QMenu *menu_L;
    QMenu *menu_D;
    QMenu *menu_M;
    QMenu *menu_H;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1052, 713);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/Resource/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        actionMTT = new QAction(MainWindowClass);
        actionMTT->setObjectName(QStringLiteral("actionMTT"));
        actionPF = new QAction(MainWindowClass);
        actionPF->setObjectName(QStringLiteral("actionPF"));
        actionOpenVideo = new QAction(MainWindowClass);
        actionOpenVideo->setObjectName(QStringLiteral("actionOpenVideo"));
        actionCT = new QAction(MainWindowClass);
        actionCT->setObjectName(QStringLiteral("actionCT"));
        actionHash = new QAction(MainWindowClass);
        actionHash->setObjectName(QStringLiteral("actionHash"));
        actionKCF = new QAction(MainWindowClass);
        actionKCF->setObjectName(QStringLiteral("actionKCF"));
        actionSTC = new QAction(MainWindowClass);
        actionSTC->setObjectName(QStringLiteral("actionSTC"));
        actionSTRUCK = new QAction(MainWindowClass);
        actionSTRUCK->setObjectName(QStringLiteral("actionSTRUCK"));
        actionCTL = new QAction(MainWindowClass);
        actionCTL->setObjectName(QStringLiteral("actionCTL"));
        actionKCFL = new QAction(MainWindowClass);
        actionKCFL->setObjectName(QStringLiteral("actionKCFL"));
        actionHashL = new QAction(MainWindowClass);
        actionHashL->setObjectName(QStringLiteral("actionHashL"));
        actionSTCL = new QAction(MainWindowClass);
        actionSTCL->setObjectName(QStringLiteral("actionSTCL"));
        actionSTRUCKL = new QAction(MainWindowClass);
        actionSTRUCKL->setObjectName(QStringLiteral("actionSTRUCKL"));
        actionPFL = new QAction(MainWindowClass);
        actionPFL->setObjectName(QStringLiteral("actionPFL"));
        actionMD = new QAction(MainWindowClass);
        actionMD->setObjectName(QStringLiteral("actionMD"));
        actionTR = new QAction(MainWindowClass);
        actionTR->setObjectName(QStringLiteral("actionTR"));
        actionMTCL = new QAction(MainWindowClass);
        actionMTCL->setObjectName(QStringLiteral("actionMTCL"));
        actionAbout = new QAction(MainWindowClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionReturn = new QAction(MainWindowClass);
        actionReturn->setObjectName(QStringLiteral("actionReturn"));
        actionClose = new QAction(MainWindowClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionMTL = new QAction(MainWindowClass);
        actionMTL->setObjectName(QStringLiteral("actionMTL"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        frontBox = new QGroupBox(centralWidget);
        frontBox->setObjectName(QStringLiteral("frontBox"));
        frontBox->setGeometry(QRect(0, 0, 1051, 691));
        frontBox->setStyleSheet(QStringLiteral("background-image: url(:/MainWindow/Resource/front.png);"));
        label = new QLabel(frontBox);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(210, 130, 631, 131));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 0));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        label->setPalette(palette);
        label->setContextMenuPolicy(Qt::NoContextMenu);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("font: 26pt \"\346\226\271\346\255\243\345\247\232\344\275\223\" ;\n"
"background: transparent;"));
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Sunken);
        label->setLineWidth(-1);
        label->setMidLineWidth(-1);
        label_2 = new QLabel(frontBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(760, 530, 241, 81));
        label_2->setStyleSheet(QStringLiteral("background: transparent;"));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1052, 21));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_T = new QMenu(menuBar);
        menu_T->setObjectName(QStringLiteral("menu_T"));
        menu_L = new QMenu(menuBar);
        menu_L->setObjectName(QStringLiteral("menu_L"));
        menu_D = new QMenu(menuBar);
        menu_D->setObjectName(QStringLiteral("menu_D"));
        menu_M = new QMenu(menuBar);
        menu_M->setObjectName(QStringLiteral("menu_M"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QStringLiteral("menu_H"));
        MainWindowClass->setMenuBar(menuBar);

        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_T->menuAction());
        menuBar->addAction(menu_L->menuAction());
        menuBar->addAction(menu_D->menuAction());
        menuBar->addAction(menu_M->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu_F->addAction(actionOpenVideo);
        menu_F->addSeparator();
        menu_F->addAction(actionReturn);
        menu_F->addAction(actionClose);
        menu_T->addAction(actionCT);
        menu_T->addAction(actionKCF);
        menu_T->addAction(actionSTC);
        menu_T->addAction(actionHash);
        menu_T->addAction(actionSTRUCK);
        menu_T->addAction(actionPF);
        menu_L->addAction(actionCTL);
        menu_L->addAction(actionKCFL);
        menu_L->addAction(actionSTCL);
        menu_L->addAction(actionHashL);
        menu_L->addAction(actionSTRUCKL);
        menu_L->addAction(actionPFL);
        menu_D->addAction(actionMD);
        menu_D->addAction(actionTR);
        menu_M->addAction(actionMTT);
        menu_M->addAction(actionMTL);
        menu_M->addSeparator();
        menu_M->addAction(actionMTCL);
        menu_H->addAction(actionAbout);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "\346\227\240\344\272\272\346\234\272\347\233\256\346\240\207\350\267\237\350\270\252\345\244\232\344\273\273\345\212\241\345\256\236\351\252\214\346\274\224\347\244\272\345\271\263\345\217\260", 0));
        actionMTT->setText(QApplication::translate("MainWindowClass", "\345\215\225\346\227\240\344\272\272\346\234\272\350\267\237\350\270\252", 0));
        actionPF->setText(QApplication::translate("MainWindowClass", "\347\262\222\345\255\220\346\273\244\346\263\242", 0));
        actionOpenVideo->setText(QApplication::translate("MainWindowClass", "\350\257\273\345\217\226\350\247\206\351\242\221", 0));
        actionCT->setText(QApplication::translate("MainWindowClass", "CT", 0));
        actionHash->setText(QApplication::translate("MainWindowClass", "Hash", 0));
        actionKCF->setText(QApplication::translate("MainWindowClass", "KCF", 0));
        actionSTC->setText(QApplication::translate("MainWindowClass", "STC", 0));
        actionSTRUCK->setText(QApplication::translate("MainWindowClass", "STRUCK", 0));
        actionCTL->setText(QApplication::translate("MainWindowClass", "CT", 0));
        actionKCFL->setText(QApplication::translate("MainWindowClass", "KCF", 0));
        actionHashL->setText(QApplication::translate("MainWindowClass", "Hash", 0));
        actionSTCL->setText(QApplication::translate("MainWindowClass", "STC", 0));
        actionSTRUCKL->setText(QApplication::translate("MainWindowClass", "STRUCK", 0));
        actionPFL->setText(QApplication::translate("MainWindowClass", "\347\262\222\345\255\220\346\273\244\346\263\242", 0));
        actionMD->setText(QApplication::translate("MainWindowClass", "\350\277\220\345\212\250\346\243\200\346\265\213", 0));
#ifndef QT_NO_TOOLTIP
        actionMD->setToolTip(QApplication::translate("MainWindowClass", "<html><head/><body><p>Motion Detect</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionTR->setText(QApplication::translate("MainWindowClass", "\345\210\206\347\261\273\345\231\250\346\243\200\346\265\213", 0));
        actionMTCL->setText(QApplication::translate("MainWindowClass", "\345\215\217\345\220\214\350\267\237\350\270\252", 0));
        actionAbout->setText(QApplication::translate("MainWindowClass", "\345\205\263\344\272\216\346\234\254\350\275\257\344\273\266", 0));
        actionReturn->setText(QApplication::translate("MainWindowClass", "\350\277\224\345\233\236", 0));
        actionClose->setText(QApplication::translate("MainWindowClass", "\345\205\263\351\227\255", 0));
#ifndef QT_NO_TOOLTIP
        actionClose->setToolTip(QApplication::translate("MainWindowClass", "\345\205\263\351\227\255", 0));
#endif // QT_NO_TOOLTIP
        actionMTL->setText(QApplication::translate("MainWindowClass", "\345\215\225\346\227\240\344\272\272\346\234\272\345\256\232\344\275\215", 0));
        frontBox->setTitle(QString());
        label->setText(QApplication::translate("MainWindowClass", "<html><head/><body><p><span style=\" font-size:28pt; color:#c7c7c7;\">\346\227\240\344\272\272\346\234\272\347\233\256\346\240\207\350\267\237\350\270\252\345\244\232\344\273\273\345\212\241\345\256\236\351\252\214\346\274\224\347\244\272\345\271\263\345\217\260</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("MainWindowClass", "<html><head/><body><p><span style=\" font-size:20pt; font-weight:600; font-style:italic; color:#c31a72;\">\350\245\277\345\256\211\347\224\265\345\255\220\347\247\221\346\212\200\345\244\247\345\255\246</span></p></body></html>", 0));
        menu_F->setTitle(QApplication::translate("MainWindowClass", "\346\226\207\344\273\266(&F)", 0));
        menu_T->setTitle(QApplication::translate("MainWindowClass", "\345\215\225\347\233\256\346\240\207\350\267\237\350\270\252(&T)", 0));
        menu_L->setTitle(QApplication::translate("MainWindowClass", "\347\233\256\346\240\207\345\256\232\344\275\215(&L)", 0));
        menu_D->setTitle(QApplication::translate("MainWindowClass", "\347\233\256\346\240\207\346\243\200\346\265\213(&D)", 0));
        menu_M->setTitle(QApplication::translate("MainWindowClass", "\345\244\232\347\233\256\346\240\207\350\267\237\350\270\252(&M)", 0));
        menu_H->setTitle(QApplication::translate("MainWindowClass", "\345\270\256\345\212\251(&H)", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
