/********************************************************************************
** Form generated from reading UI file 'cooplocationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COOPLOCATIONWIDGET_H
#define UI_COOPLOCATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qmapview.h>

QT_BEGIN_NAMESPACE

class Ui_CoopLocationWidget
{
public:
    QGroupBox *videoBox;
    QLabel *videoInput_1;
    QLabel *videoInput_2;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *mapBox;
    QMapView *mapView;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *loadVideoButton_1;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *loadPoseButton_1;
    QPushButton *loadDetectorButton_1;
    QHBoxLayout *horizontalLayout_2;
    QSlider *videoProgressSlider_1;
    QLabel *frameCount_1;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *loadMapButton;
    QPushButton *runButton;
    QPushButton *stopButton;
    QLineEdit *paramEdit;
    QFrame *line;
    QLabel *label;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *loadVideoButton_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *loadPoseButton_2;
    QPushButton *loadDetectorButton_2;
    QHBoxLayout *horizontalLayout_7;
    QSlider *videoProgressSlider_2;
    QLabel *frameCount_2;
    QTextEdit *infoEdit;

    void setupUi(QWidget *CoopLocationWidget)
    {
        if (CoopLocationWidget->objectName().isEmpty())
            CoopLocationWidget->setObjectName(QStringLiteral("CoopLocationWidget"));
        CoopLocationWidget->resize(1045, 693);
        videoBox = new QGroupBox(CoopLocationWidget);
        videoBox->setObjectName(QStringLiteral("videoBox"));
        videoBox->setGeometry(QRect(10, 5, 341, 676));
        videoBox->setAlignment(Qt::AlignCenter);
        videoInput_1 = new QLabel(videoBox);
        videoInput_1->setObjectName(QStringLiteral("videoInput_1"));
        videoInput_1->setGeometry(QRect(10, 15, 321, 321));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(videoInput_1->sizePolicy().hasHeightForWidth());
        videoInput_1->setSizePolicy(sizePolicy);
        videoInput_1->setMinimumSize(QSize(321, 321));
        videoInput_1->setMaximumSize(QSize(321, 321));
        videoInput_1->setBaseSize(QSize(321, 321));
        videoInput_1->setCursor(QCursor(Qt::CrossCursor));
        videoInput_1->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        videoInput_2 = new QLabel(videoBox);
        videoInput_2->setObjectName(QStringLiteral("videoInput_2"));
        videoInput_2->setGeometry(QRect(10, 345, 321, 321));
        sizePolicy.setHeightForWidth(videoInput_2->sizePolicy().hasHeightForWidth());
        videoInput_2->setSizePolicy(sizePolicy);
        videoInput_2->setMinimumSize(QSize(321, 321));
        videoInput_2->setBaseSize(QSize(321, 321));
        videoInput_2->setCursor(QCursor(Qt::CrossCursor));
        videoInput_2->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        label_2 = new QLabel(videoBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 350, 51, 31));
        label_2->setStyleSheet(QStringLiteral("background: transparent;"));
        label_3 = new QLabel(videoBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 20, 51, 31));
        label_3->setStyleSheet(QStringLiteral("background: transparent;"));
        mapBox = new QGroupBox(CoopLocationWidget);
        mapBox->setObjectName(QStringLiteral("mapBox"));
        mapBox->setGeometry(QRect(360, 5, 676, 471));
        mapBox->setAlignment(Qt::AlignCenter);
        mapView = new QMapView(mapBox);
        mapView->setObjectName(QStringLiteral("mapView"));
        mapView->setGeometry(QRect(10, 15, 656, 451));
        mapView->setStyleSheet(QStringLiteral("background-color: rgb(94, 94, 94);"));
        groupBox = new QGroupBox(CoopLocationWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(360, 510, 211, 111));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 191, 88));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        loadVideoButton_1 = new QPushButton(layoutWidget);
        loadVideoButton_1->setObjectName(QStringLiteral("loadVideoButton_1"));
        loadVideoButton_1->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_4->addWidget(loadVideoButton_1);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        loadPoseButton_1 = new QPushButton(layoutWidget);
        loadPoseButton_1->setObjectName(QStringLiteral("loadPoseButton_1"));
        loadPoseButton_1->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_3->addWidget(loadPoseButton_1);

        loadDetectorButton_1 = new QPushButton(layoutWidget);
        loadDetectorButton_1->setObjectName(QStringLiteral("loadDetectorButton_1"));
        loadDetectorButton_1->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_3->addWidget(loadDetectorButton_1);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        videoProgressSlider_1 = new QSlider(layoutWidget);
        videoProgressSlider_1->setObjectName(QStringLiteral("videoProgressSlider_1"));
        videoProgressSlider_1->setEnabled(true);
        videoProgressSlider_1->setCursor(QCursor(Qt::ArrowCursor));
        videoProgressSlider_1->setStyleSheet(QLatin1String("QSlider::groove:horizontal {  \n"
"border: 1px solid #4A708B;  \n"
"background: #C0C0C0;  \n"
"height: 5px;  \n"
"border-radius: 1px;  \n"
"padding-left:-1px;  \n"
"padding-right:-1px;  \n"
"}  \n"
"  \n"
"QSlider::sub-page:horizontal {  \n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1,   \n"
"    stop:0 #B1B1B1, stop:1 #c4c4c4);  \n"
"background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,  \n"
"    stop: 0 #5DCCFF, stop: 1 #1874CD);  \n"
"border: 1px solid #4A708B;  \n"
"height: 10px;  \n"
"border-radius: 2px;  \n"
"}  \n"
"  \n"
"QSlider::add-page:horizontal {  \n"
"background: #575757;  \n"
"border: 0px solid #777;  \n"
"height: 10px;  \n"
"border-radius: 2px;  \n"
"}  "));
        videoProgressSlider_1->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(videoProgressSlider_1);

        frameCount_1 = new QLabel(layoutWidget);
        frameCount_1->setObjectName(QStringLiteral("frameCount_1"));
        sizePolicy.setHeightForWidth(frameCount_1->sizePolicy().hasHeightForWidth());
        frameCount_1->setSizePolicy(sizePolicy);
        frameCount_1->setMaximumSize(QSize(80, 24));
        frameCount_1->setLayoutDirection(Qt::LeftToRight);
        frameCount_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(frameCount_1);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox_2 = new QGroupBox(CoopLocationWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(360, 620, 441, 61));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 421, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        loadMapButton = new QPushButton(layoutWidget1);
        loadMapButton->setObjectName(QStringLiteral("loadMapButton"));
        loadMapButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(loadMapButton);

        runButton = new QPushButton(layoutWidget1);
        runButton->setObjectName(QStringLiteral("runButton"));
        runButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(runButton);

        stopButton = new QPushButton(layoutWidget1);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(stopButton);

        paramEdit = new QLineEdit(layoutWidget1);
        paramEdit->setObjectName(QStringLiteral("paramEdit"));
        paramEdit->setEnabled(false);
        QPalette palette;
        QBrush brush(QColor(216, 216, 216, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(42, 32, 149, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        paramEdit->setPalette(palette);
        paramEdit->setStyleSheet(QStringLiteral("background-color: rgb(216, 216, 216);"));

        horizontalLayout->addWidget(paramEdit);

        line = new QFrame(CoopLocationWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(360, 475, 676, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(CoopLocationWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(510, 490, 151, 16));
        groupBox_3 = new QGroupBox(CoopLocationWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(590, 510, 211, 111));
        layoutWidget2 = new QWidget(groupBox_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 10, 191, 88));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        loadVideoButton_2 = new QPushButton(layoutWidget2);
        loadVideoButton_2->setObjectName(QStringLiteral("loadVideoButton_2"));
        loadVideoButton_2->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_5->addWidget(loadVideoButton_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        loadPoseButton_2 = new QPushButton(layoutWidget2);
        loadPoseButton_2->setObjectName(QStringLiteral("loadPoseButton_2"));
        loadPoseButton_2->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_6->addWidget(loadPoseButton_2);

        loadDetectorButton_2 = new QPushButton(layoutWidget2);
        loadDetectorButton_2->setObjectName(QStringLiteral("loadDetectorButton_2"));
        loadDetectorButton_2->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_6->addWidget(loadDetectorButton_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        videoProgressSlider_2 = new QSlider(layoutWidget2);
        videoProgressSlider_2->setObjectName(QStringLiteral("videoProgressSlider_2"));
        videoProgressSlider_2->setEnabled(true);
        videoProgressSlider_2->setCursor(QCursor(Qt::ArrowCursor));
        videoProgressSlider_2->setStyleSheet(QLatin1String("QSlider::groove:horizontal {  \n"
"border: 1px solid #4A708B;  \n"
"background: #C0C0C0;  \n"
"height: 5px;  \n"
"border-radius: 1px;  \n"
"padding-left:-1px;  \n"
"padding-right:-1px;  \n"
"}  \n"
"  \n"
"QSlider::sub-page:horizontal {  \n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1,   \n"
"    stop:0 #B1B1B1, stop:1 #c4c4c4);  \n"
"background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,  \n"
"    stop: 0 #5DCCFF, stop: 1 #1874CD);  \n"
"border: 1px solid #4A708B;  \n"
"height: 10px;  \n"
"border-radius: 2px;  \n"
"}  \n"
"  \n"
"QSlider::add-page:horizontal {  \n"
"background: #575757;  \n"
"border: 0px solid #777;  \n"
"height: 10px;  \n"
"border-radius: 2px;  \n"
"}  "));
        videoProgressSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(videoProgressSlider_2);

        frameCount_2 = new QLabel(layoutWidget2);
        frameCount_2->setObjectName(QStringLiteral("frameCount_2"));
        sizePolicy.setHeightForWidth(frameCount_2->sizePolicy().hasHeightForWidth());
        frameCount_2->setSizePolicy(sizePolicy);
        frameCount_2->setMaximumSize(QSize(80, 24));
        frameCount_2->setLayoutDirection(Qt::LeftToRight);
        frameCount_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(frameCount_2);


        verticalLayout_2->addLayout(horizontalLayout_7);

        infoEdit = new QTextEdit(CoopLocationWidget);
        infoEdit->setObjectName(QStringLiteral("infoEdit"));
        infoEdit->setGeometry(QRect(810, 490, 226, 191));
        infoEdit->setStyleSheet(QStringLiteral("background-color: rgb(208, 208, 208);"));

        retranslateUi(CoopLocationWidget);

        QMetaObject::connectSlotsByName(CoopLocationWidget);
    } // setupUi

    void retranslateUi(QWidget *CoopLocationWidget)
    {
        CoopLocationWidget->setWindowTitle(QApplication::translate("CoopLocationWidget", "CoopLocationWidget", 0));
        videoBox->setTitle(QApplication::translate("CoopLocationWidget", "\350\276\223\345\205\245\350\247\206\351\242\221", 0));
        videoInput_1->setText(QString());
        videoInput_2->setText(QString());
        label_2->setText(QApplication::translate("CoopLocationWidget", "<html><head/><body><p><span style=\" font-size:10pt; color:#55aaff;\">\351\200\232\351\201\223 2</span></p></body></html>", 0));
        label_3->setText(QApplication::translate("CoopLocationWidget", "<html><head/><body><p><span style=\" font-size:10pt; color:#55aaff;\">\351\200\232\351\201\223 1</span></p></body></html>", 0));
        mapBox->setTitle(QApplication::translate("CoopLocationWidget", "\345\234\260\345\233\276", 0));
        groupBox->setTitle(QString());
        label_4->setText(QApplication::translate("CoopLocationWidget", "\351\200\232\351\201\223 1", 0));
        loadVideoButton_1->setText(QApplication::translate("CoopLocationWidget", "\345\212\240\350\275\275\350\247\206\351\242\221", 0));
        loadPoseButton_1->setText(QApplication::translate("CoopLocationWidget", "\345\212\240\350\275\275\344\275\215\345\247\277\345\217\202\346\225\260", 0));
        loadDetectorButton_1->setText(QApplication::translate("CoopLocationWidget", "\345\212\240\350\275\275\345\210\206\347\261\273\345\231\250", 0));
        frameCount_1->setText(QApplication::translate("CoopLocationWidget", "0000/9999", 0));
        groupBox_2->setTitle(QApplication::translate("CoopLocationWidget", "\350\277\220\350\241\214\346\216\247\345\210\266", 0));
        loadMapButton->setText(QApplication::translate("CoopLocationWidget", "\345\212\240\350\275\275\345\234\260\345\233\276", 0));
        runButton->setText(QApplication::translate("CoopLocationWidget", "\350\277\220\350\241\214", 0));
        stopButton->setText(QApplication::translate("CoopLocationWidget", "\347\273\223\346\235\237", 0));
        label->setText(QApplication::translate("CoopLocationWidget", "\345\215\217\345\220\214\350\267\237\350\270\252  \346\216\247\345\210\266 / \346\230\276\347\244\272\345\217\260", 0));
        groupBox_3->setTitle(QString());
        label_5->setText(QApplication::translate("CoopLocationWidget", "\351\200\232\351\201\223 2", 0));
        loadVideoButton_2->setText(QApplication::translate("CoopLocationWidget", "\345\212\240\350\275\275\350\247\206\351\242\221", 0));
        loadPoseButton_2->setText(QApplication::translate("CoopLocationWidget", "\345\212\240\350\275\275\344\275\215\345\247\277\345\217\202\346\225\260", 0));
        loadDetectorButton_2->setText(QApplication::translate("CoopLocationWidget", "\345\212\240\350\275\275\345\210\206\347\261\273\345\231\250", 0));
        frameCount_2->setText(QApplication::translate("CoopLocationWidget", "0000/9999", 0));
    } // retranslateUi

};

namespace Ui {
    class CoopLocationWidget: public Ui_CoopLocationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COOPLOCATIONWIDGET_H
