/********************************************************************************
** Form generated from reading UI file 'drawrectwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWRECTWND_H
#define UI_DRAWRECTWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <qshowlabel.h>

QT_BEGIN_NAMESPACE

class Ui_drawRectWnd
{
public:
    QPushButton *okButton;
    QShowLabel *drawArea;

    void setupUi(QWidget *drawRectWnd)
    {
        if (drawRectWnd->objectName().isEmpty())
            drawRectWnd->setObjectName(QStringLiteral("drawRectWnd"));
        drawRectWnd->setWindowModality(Qt::NonModal);
        drawRectWnd->resize(507, 378);
        QPalette palette;
        drawRectWnd->setPalette(palette);
        drawRectWnd->setCursor(QCursor(Qt::ForbiddenCursor));
        drawRectWnd->setStyleSheet(QStringLiteral(""));
        okButton = new QPushButton(drawRectWnd);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(400, 220, 61, 23));
        okButton->setCursor(QCursor(Qt::PointingHandCursor));
        okButton->setStyleSheet(QStringLiteral(""));
        okButton->setFlat(false);
        drawArea = new QShowLabel(drawRectWnd);
        drawArea->setObjectName(QStringLiteral("drawArea"));
        drawArea->setGeometry(QRect(40, 40, 311, 251));
        drawArea->setCursor(QCursor(Qt::CrossCursor));
        drawArea->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        retranslateUi(drawRectWnd);

        QMetaObject::connectSlotsByName(drawRectWnd);
    } // setupUi

    void retranslateUi(QWidget *drawRectWnd)
    {
        drawRectWnd->setWindowTitle(QApplication::translate("drawRectWnd", "drawRectWnd", 0));
        okButton->setText(QApplication::translate("drawRectWnd", "\347\241\256\345\256\232", 0));
        drawArea->setText(QApplication::translate("drawRectWnd", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class drawRectWnd: public Ui_drawRectWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWRECTWND_H
