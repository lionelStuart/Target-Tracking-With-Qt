/********************************************************************************
** Form generated from reading UI file 'multilocationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTILOCATIONWIDGET_H
#define UI_MULTILOCATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qmapview.h>

QT_BEGIN_NAMESPACE

class Ui_MultiLocationWidget
{
public:
    QGroupBox *videoBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *videoInput;
    QHBoxLayout *horizontalLayout;
    QPushButton *playButton;
    QPushButton *stopButton;
    QSlider *videoProgressSlider;
    QLabel *frameCount;
    QGroupBox *mapBox;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QMapView *mapView;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *paramEdit;
    QPushButton *loadDetectorButton;
    QPushButton *loadPoseButton;
    QPushButton *loadMapButton;
    QGroupBox *infoBox;
    QTextEdit *infoEdit;
    QGroupBox *bottomBox;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *MultiLocationWidget)
    {
        if (MultiLocationWidget->objectName().isEmpty())
            MultiLocationWidget->setObjectName(QStringLiteral("MultiLocationWidget"));
        MultiLocationWidget->resize(1045, 693);
        videoBox = new QGroupBox(MultiLocationWidget);
        videoBox->setObjectName(QStringLiteral("videoBox"));
        videoBox->setGeometry(QRect(10, 20, 421, 451));
        widget = new QWidget(videoBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(11, 12, 402, 433));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        videoInput = new QLabel(widget);
        videoInput->setObjectName(QStringLiteral("videoInput"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(videoInput->sizePolicy().hasHeightForWidth());
        videoInput->setSizePolicy(sizePolicy);
        videoInput->setMinimumSize(QSize(400, 400));
        videoInput->setMaximumSize(QSize(400, 400));
        videoInput->setBaseSize(QSize(640, 480));
        videoInput->setCursor(QCursor(Qt::CrossCursor));
        videoInput->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        videoInput->setMargin(-1);

        verticalLayout_2->addWidget(videoInput);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        playButton = new QPushButton(widget);
        playButton->setObjectName(QStringLiteral("playButton"));
        sizePolicy.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy);
        playButton->setMaximumSize(QSize(45, 24));
        playButton->setBaseSize(QSize(42, 24));
        playButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(playButton);

        stopButton = new QPushButton(widget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        sizePolicy.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy);
        stopButton->setMaximumSize(QSize(45, 24));
        stopButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(stopButton);

        videoProgressSlider = new QSlider(widget);
        videoProgressSlider->setObjectName(QStringLiteral("videoProgressSlider"));
        videoProgressSlider->setCursor(QCursor(Qt::ArrowCursor));
        videoProgressSlider->setStyleSheet(QLatin1String("QSlider::groove:horizontal {  \n"
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
        videoProgressSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(videoProgressSlider);

        frameCount = new QLabel(widget);
        frameCount->setObjectName(QStringLiteral("frameCount"));
        sizePolicy.setHeightForWidth(frameCount->sizePolicy().hasHeightForWidth());
        frameCount->setSizePolicy(sizePolicy);
        frameCount->setMaximumSize(QSize(80, 24));
        frameCount->setLayoutDirection(Qt::LeftToRight);
        frameCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(frameCount);


        verticalLayout_2->addLayout(horizontalLayout);

        mapBox = new QGroupBox(MultiLocationWidget);
        mapBox->setObjectName(QStringLiteral("mapBox"));
        mapBox->setGeometry(QRect(440, 20, 601, 451));
        mapBox->setAlignment(Qt::AlignCenter);
        widget1 = new QWidget(mapBox);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(11, 12, 581, 433));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mapView = new QMapView(widget1);
        mapView->setObjectName(QStringLiteral("mapView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mapView->sizePolicy().hasHeightForWidth());
        mapView->setSizePolicy(sizePolicy1);
        mapView->setMinimumSize(QSize(579, 400));
        mapView->setMaximumSize(QSize(579, 400));
        mapView->setStyleSheet(QStringLiteral("background-color: rgb(95, 95, 95);"));

        verticalLayout->addWidget(mapView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        paramEdit = new QLineEdit(widget1);
        paramEdit->setObjectName(QStringLiteral("paramEdit"));
        paramEdit->setEnabled(false);
        QPalette palette;
        QBrush brush(QColor(216, 216, 216, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(27, 39, 206, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        QBrush brush2(QColor(113, 88, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        QBrush brush3(QColor(83, 67, 203, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        paramEdit->setPalette(palette);
        paramEdit->setStyleSheet(QStringLiteral("background-color: rgb(216, 216, 216);"));

        horizontalLayout_2->addWidget(paramEdit);

        loadDetectorButton = new QPushButton(widget1);
        loadDetectorButton->setObjectName(QStringLiteral("loadDetectorButton"));
        sizePolicy.setHeightForWidth(loadDetectorButton->sizePolicy().hasHeightForWidth());
        loadDetectorButton->setSizePolicy(sizePolicy);
        loadDetectorButton->setMaximumSize(QSize(63, 32));
        loadDetectorButton->setBaseSize(QSize(90, 24));
        loadDetectorButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(loadDetectorButton);

        loadPoseButton = new QPushButton(widget1);
        loadPoseButton->setObjectName(QStringLiteral("loadPoseButton"));
        sizePolicy.setHeightForWidth(loadPoseButton->sizePolicy().hasHeightForWidth());
        loadPoseButton->setSizePolicy(sizePolicy);
        loadPoseButton->setMaximumSize(QSize(63, 32));
        loadPoseButton->setBaseSize(QSize(90, 24));
        loadPoseButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(loadPoseButton);

        loadMapButton = new QPushButton(widget1);
        loadMapButton->setObjectName(QStringLiteral("loadMapButton"));
        sizePolicy.setHeightForWidth(loadMapButton->sizePolicy().hasHeightForWidth());
        loadMapButton->setSizePolicy(sizePolicy);
        loadMapButton->setMaximumSize(QSize(63, 23));
        loadMapButton->setBaseSize(QSize(90, 24));
        loadMapButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(loadMapButton);


        verticalLayout->addLayout(horizontalLayout_2);

        infoBox = new QGroupBox(MultiLocationWidget);
        infoBox->setObjectName(QStringLiteral("infoBox"));
        infoBox->setGeometry(QRect(10, 480, 421, 201));
        infoBox->setAlignment(Qt::AlignCenter);
        infoEdit = new QTextEdit(infoBox);
        infoEdit->setObjectName(QStringLiteral("infoEdit"));
        infoEdit->setGeometry(QRect(10, 20, 401, 171));
        infoEdit->setStyleSheet(QStringLiteral("background-color: rgb(208, 208, 208);"));
        infoEdit->setReadOnly(true);
        bottomBox = new QGroupBox(MultiLocationWidget);
        bottomBox->setObjectName(QStringLiteral("bottomBox"));
        bottomBox->setGeometry(QRect(440, 480, 601, 201));
        bottomBox->setStyleSheet(QStringLiteral("background-image: url(:/bottom/Resource/bottom/C_601x201.png);"));
        label_4 = new QLabel(bottomBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 30, 441, 51));
        label_4->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 18pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";"));
        label_5 = new QLabel(bottomBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(370, 90, 161, 51));
        label_5->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 18pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";"));

        retranslateUi(MultiLocationWidget);

        QMetaObject::connectSlotsByName(MultiLocationWidget);
    } // setupUi

    void retranslateUi(QWidget *MultiLocationWidget)
    {
        MultiLocationWidget->setWindowTitle(QApplication::translate("MultiLocationWidget", "MultiLocationWidget", 0));
        videoBox->setTitle(QString());
        videoInput->setText(QString());
        playButton->setText(QApplication::translate("MultiLocationWidget", "\350\277\220\350\241\214", 0));
        stopButton->setText(QApplication::translate("MultiLocationWidget", "\347\273\223\346\235\237", 0));
        frameCount->setText(QApplication::translate("MultiLocationWidget", "0000/9999", 0));
        mapBox->setTitle(QApplication::translate("MultiLocationWidget", "\345\234\260 \345\233\276", 0));
        loadDetectorButton->setText(QApplication::translate("MultiLocationWidget", "\346\243\200\346\265\213\345\231\250", 0));
        loadPoseButton->setText(QApplication::translate("MultiLocationWidget", "\345\247\277\346\200\201\345\217\202\346\225\260", 0));
        loadMapButton->setText(QApplication::translate("MultiLocationWidget", "\345\212\240\350\275\275\345\234\260\345\233\276", 0));
        infoBox->setTitle(QApplication::translate("MultiLocationWidget", "\344\277\241\346\201\257\346\230\276\347\244\272", 0));
        bottomBox->setTitle(QString());
        label_4->setText(QApplication::translate("MultiLocationWidget", "<html><head/><body><p><span style=\" color:#a7a7a7;\">\346\227\240\344\272\272\346\234\272\347\233\256\346\240\207\350\267\237\350\270\252\345\244\232\344\273\273\345\212\241\345\256\236\351\252\214\346\274\224\347\244\272\345\271\263\345\217\260--</span></p></body></html>", 0));
        label_5->setText(QApplication::translate("MultiLocationWidget", "<html><head/><body><p><span style=\" font-style:italic; color:#ec2643;\">\345\215\225\346\227\240\344\272\272\346\234\272\345\256\232\344\275\215</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MultiLocationWidget: public Ui_MultiLocationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTILOCATIONWIDGET_H
