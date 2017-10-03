/********************************************************************************
** Form generated from reading UI file 'multitrackingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTITRACKINGWIDGET_H
#define UI_MULTITRACKINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
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

QT_BEGIN_NAMESPACE

class Ui_MultiTrackingWidget
{
public:
    QGroupBox *videoBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *videoInput;
    QHBoxLayout *videoControlLayout;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *trackingButton;
    QSlider *videoProgressSlider;
    QLabel *frameCount;
    QGroupBox *infoBox_2;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout;
    QSlider *minSizeSlider;
    QLineEdit *minSizeEdit;
    QLabel *label_3;
    QSlider *maxSizeSlider;
    QLineEdit *maxSizeEdit;
    QLabel *label_2;
    QGroupBox *infoBox;
    QTextEdit *infoEdit;
    QGroupBox *bottomBox;
    QLabel *label;
    QLabel *label_4;

    void setupUi(QWidget *MultiTrackingWidget)
    {
        if (MultiTrackingWidget->objectName().isEmpty())
            MultiTrackingWidget->setObjectName(QStringLiteral("MultiTrackingWidget"));
        MultiTrackingWidget->resize(1045, 693);
        videoBox = new QGroupBox(MultiTrackingWidget);
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

        trackingButton = new QPushButton(layoutWidget);
        trackingButton->setObjectName(QStringLiteral("trackingButton"));
        sizePolicy.setHeightForWidth(trackingButton->sizePolicy().hasHeightForWidth());
        trackingButton->setSizePolicy(sizePolicy);
        trackingButton->setMaximumSize(QSize(45, 24));
        trackingButton->setCursor(QCursor(Qt::PointingHandCursor));

        videoControlLayout->addWidget(trackingButton);

        videoProgressSlider = new QSlider(layoutWidget);
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

        infoBox_2 = new QGroupBox(MultiTrackingWidget);
        infoBox_2->setObjectName(QStringLiteral("infoBox_2"));
        infoBox_2->setGeometry(QRect(680, 470, 361, 81));
        infoBox_2->setAlignment(Qt::AlignCenter);
        layoutWidget_2 = new QWidget(infoBox_2);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 20, 341, 52));
        gridLayout = new QGridLayout(layoutWidget_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        minSizeSlider = new QSlider(layoutWidget_2);
        minSizeSlider->setObjectName(QStringLiteral("minSizeSlider"));
        minSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(minSizeSlider, 0, 0, 1, 1);

        minSizeEdit = new QLineEdit(layoutWidget_2);
        minSizeEdit->setObjectName(QStringLiteral("minSizeEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(41);
        sizePolicy1.setVerticalStretch(20);
        sizePolicy1.setHeightForWidth(minSizeEdit->sizePolicy().hasHeightForWidth());
        minSizeEdit->setSizePolicy(sizePolicy1);
        minSizeEdit->setMinimumSize(QSize(41, 20));
        minSizeEdit->setMaximumSize(QSize(41, 20));

        gridLayout->addWidget(minSizeEdit, 0, 1, 1, 1);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        maxSizeSlider = new QSlider(layoutWidget_2);
        maxSizeSlider->setObjectName(QStringLiteral("maxSizeSlider"));
        maxSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(maxSizeSlider, 1, 0, 1, 1);

        maxSizeEdit = new QLineEdit(layoutWidget_2);
        maxSizeEdit->setObjectName(QStringLiteral("maxSizeEdit"));
        sizePolicy1.setHeightForWidth(maxSizeEdit->sizePolicy().hasHeightForWidth());
        maxSizeEdit->setSizePolicy(sizePolicy1);
        maxSizeEdit->setMinimumSize(QSize(41, 20));
        maxSizeEdit->setMaximumSize(QSize(41, 20));

        gridLayout->addWidget(maxSizeEdit, 1, 1, 1, 1);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        infoBox = new QGroupBox(MultiTrackingWidget);
        infoBox->setObjectName(QStringLiteral("infoBox"));
        infoBox->setGeometry(QRect(680, 20, 361, 441));
        infoBox->setAlignment(Qt::AlignCenter);
        infoEdit = new QTextEdit(infoBox);
        infoEdit->setObjectName(QStringLiteral("infoEdit"));
        infoEdit->setGeometry(QRect(10, 20, 341, 411));
        infoEdit->setStyleSheet(QStringLiteral("background-color: rgb(208, 208, 208);"));
        infoEdit->setReadOnly(true);
        bottomBox = new QGroupBox(MultiTrackingWidget);
        bottomBox->setObjectName(QStringLiteral("bottomBox"));
        bottomBox->setGeometry(QRect(10, 550, 1031, 131));
        bottomBox->setStyleSheet(QStringLiteral("background-image: url(:/bottom/Resource/bottom/B_1031x131.png);"));
        label = new QLabel(bottomBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 60, 441, 51));
        label->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 18pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";"));
        label_4 = new QLabel(bottomBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(500, 60, 131, 51));
        label_4->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 18pt \"\346\226\271\346\255\243\345\247\232\344\275\223\";"));

        retranslateUi(MultiTrackingWidget);

        QMetaObject::connectSlotsByName(MultiTrackingWidget);
    } // setupUi

    void retranslateUi(QWidget *MultiTrackingWidget)
    {
        MultiTrackingWidget->setWindowTitle(QApplication::translate("MultiTrackingWidget", "MultiTrackingWidget", 0));
        videoBox->setTitle(QString());
        videoInput->setText(QString());
        playButton->setText(QApplication::translate("MultiTrackingWidget", "\350\277\220\350\241\214", 0));
        stopButton->setText(QApplication::translate("MultiTrackingWidget", "\347\273\223\346\235\237", 0));
        trackingButton->setText(QApplication::translate("MultiTrackingWidget", "\350\267\237\350\270\252", 0));
        frameCount->setText(QApplication::translate("MultiTrackingWidget", "0000/9999", 0));
        infoBox_2->setTitle(QApplication::translate("MultiTrackingWidget", "\345\217\202\346\225\260\350\260\203\346\225\264", 0));
        label_3->setText(QApplication::translate("MultiTrackingWidget", "\346\234\200\345\260\217\351\230\210\345\200\274", 0));
        label_2->setText(QApplication::translate("MultiTrackingWidget", "\346\234\200\345\244\247\351\230\210\345\200\274", 0));
        infoBox->setTitle(QApplication::translate("MultiTrackingWidget", "\344\277\241\346\201\257\346\230\276\347\244\272", 0));
        bottomBox->setTitle(QString());
        label->setText(QApplication::translate("MultiTrackingWidget", "<html><head/><body><p><span style=\" color:#a7a7a7;\">\346\227\240\344\272\272\346\234\272\347\233\256\346\240\207\350\267\237\350\270\252\345\244\232\344\273\273\345\212\241\345\256\236\351\252\214\346\274\224\347\244\272\345\271\263\345\217\260--</span></p></body></html>", 0));
        label_4->setText(QApplication::translate("MultiTrackingWidget", "<html><head/><body><p><span style=\" font-style:italic; color:#ec2643;\">\345\244\232\347\233\256\346\240\207\350\267\237\350\270\252</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MultiTrackingWidget: public Ui_MultiTrackingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTITRACKINGWIDGET_H
