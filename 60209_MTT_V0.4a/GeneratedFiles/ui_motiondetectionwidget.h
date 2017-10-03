/********************************************************************************
** Form generated from reading UI file 'motiondetectionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTIONDETECTIONWIDGET_H
#define UI_MOTIONDETECTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MotionDetectionWidget
{
public:
    QGroupBox *videoBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *videoInput;
    QHBoxLayout *videoControlLayout;
    QPushButton *playButton;
    QPushButton *stopButton;
    QSlider *videoProgressSlider;
    QLabel *frameCount;
    QGroupBox *infoBox;
    QTextEdit *infoEdit;
    QGroupBox *groupBox;
    QLabel *maskInput;
    QGroupBox *bottomBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *MotionDetectionWidget)
    {
        if (MotionDetectionWidget->objectName().isEmpty())
            MotionDetectionWidget->setObjectName(QStringLiteral("MotionDetectionWidget"));
        MotionDetectionWidget->resize(1045, 693);
        MotionDetectionWidget->setMinimumSize(QSize(0, 0));
        MotionDetectionWidget->setMaximumSize(QSize(99999, 99999));
        videoBox = new QGroupBox(MotionDetectionWidget);
        videoBox->setObjectName(QStringLiteral("videoBox"));
        videoBox->setGeometry(QRect(10, 20, 661, 531));
        layoutWidget = new QWidget(videoBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 642, 513));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        videoInput = new QLabel(layoutWidget);
        videoInput->setObjectName(QStringLiteral("videoInput"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(videoInput->sizePolicy().hasHeightForWidth());
        videoInput->setSizePolicy(sizePolicy);
        videoInput->setMinimumSize(QSize(640, 480));
        videoInput->setMaximumSize(QSize(640, 480));
        videoInput->setBaseSize(QSize(640, 480));
        videoInput->setCursor(QCursor(Qt::CrossCursor));
        videoInput->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        videoInput->setMargin(-1);

        verticalLayout->addWidget(videoInput);

        videoControlLayout = new QHBoxLayout();
        videoControlLayout->setSpacing(6);
        videoControlLayout->setObjectName(QStringLiteral("videoControlLayout"));
        playButton = new QPushButton(layoutWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        sizePolicy.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy);
        playButton->setMaximumSize(QSize(45, 24));
        playButton->setBaseSize(QSize(42, 24));
        playButton->setCursor(QCursor(Qt::PointingHandCursor));

        videoControlLayout->addWidget(playButton);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        sizePolicy.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy);
        stopButton->setMaximumSize(QSize(45, 24));
        stopButton->setCursor(QCursor(Qt::PointingHandCursor));

        videoControlLayout->addWidget(stopButton);

        videoProgressSlider = new QSlider(layoutWidget);
        videoProgressSlider->setObjectName(QStringLiteral("videoProgressSlider"));
        videoProgressSlider->setCursor(QCursor(Qt::SplitHCursor));
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

        videoControlLayout->addWidget(videoProgressSlider);

        frameCount = new QLabel(layoutWidget);
        frameCount->setObjectName(QStringLiteral("frameCount"));
        sizePolicy.setHeightForWidth(frameCount->sizePolicy().hasHeightForWidth());
        frameCount->setSizePolicy(sizePolicy);
        frameCount->setMaximumSize(QSize(80, 24));
        frameCount->setLayoutDirection(Qt::LeftToRight);
        frameCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        videoControlLayout->addWidget(frameCount);


        verticalLayout->addLayout(videoControlLayout);

        infoBox = new QGroupBox(MotionDetectionWidget);
        infoBox->setObjectName(QStringLiteral("infoBox"));
        infoBox->setGeometry(QRect(680, 20, 361, 221));
        infoBox->setAlignment(Qt::AlignCenter);
        infoEdit = new QTextEdit(infoBox);
        infoEdit->setObjectName(QStringLiteral("infoEdit"));
        infoEdit->setGeometry(QRect(10, 20, 341, 191));
        infoEdit->setStyleSheet(QStringLiteral("background-color: rgb(208, 208, 208);"));
        infoEdit->setReadOnly(true);
        groupBox = new QGroupBox(MotionDetectionWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(680, 250, 361, 301));
        groupBox->setAlignment(Qt::AlignCenter);
        maskInput = new QLabel(groupBox);
        maskInput->setObjectName(QStringLiteral("maskInput"));
        maskInput->setGeometry(QRect(10, 20, 341, 271));
        maskInput->setStyleSheet(QStringLiteral("background-color: rgb(56, 56, 56);"));
        bottomBox = new QGroupBox(MotionDetectionWidget);
        bottomBox->setObjectName(QStringLiteral("bottomBox"));
        bottomBox->setGeometry(QRect(10, 550, 1031, 131));
        bottomBox->setStyleSheet(QStringLiteral("background-image: url(:/bottom/Resource/bottom/B_1031x131.png);"));
        label = new QLabel(bottomBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 70, 441, 51));
        label->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 18pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";"));
        label_2 = new QLabel(bottomBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(530, 70, 151, 51));
        label_2->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 18pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";"));

        retranslateUi(MotionDetectionWidget);

        QMetaObject::connectSlotsByName(MotionDetectionWidget);
    } // setupUi

    void retranslateUi(QWidget *MotionDetectionWidget)
    {
        MotionDetectionWidget->setWindowTitle(QApplication::translate("MotionDetectionWidget", "MotionDetectionWidget", 0));
        videoBox->setTitle(QString());
        videoInput->setText(QString());
        playButton->setText(QApplication::translate("MotionDetectionWidget", "\346\222\255\346\224\276", 0));
        stopButton->setText(QApplication::translate("MotionDetectionWidget", "\347\273\223\346\235\237", 0));
        frameCount->setText(QApplication::translate("MotionDetectionWidget", "0000/9999", 0));
        infoBox->setTitle(QApplication::translate("MotionDetectionWidget", "\344\277\241\346\201\257\346\230\276\347\244\272", 0));
        groupBox->setTitle(QApplication::translate("MotionDetectionWidget", "\350\277\220\345\212\250\345\214\272\345\237\237", 0));
        maskInput->setText(QString());
        bottomBox->setTitle(QString());
        label->setText(QApplication::translate("MotionDetectionWidget", "<html><head/><body><p><span style=\" color:#a7a7a7;\">\346\227\240\344\272\272\346\234\272\347\233\256\346\240\207\350\267\237\350\270\252\345\244\232\344\273\273\345\212\241\345\256\236\351\252\214\346\274\224\347\244\272\345\271\263\345\217\260--</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("MotionDetectionWidget", "<html><head/><body><p><span style=\" font-style:italic; color:#ec2643;\">\350\277\220\345\212\250\347\233\256\346\240\207\346\243\200\346\265\213</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MotionDetectionWidget: public Ui_MotionDetectionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTIONDETECTIONWIDGET_H
