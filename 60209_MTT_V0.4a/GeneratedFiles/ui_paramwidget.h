/********************************************************************************
** Form generated from reading UI file 'paramwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMWIDGET_H
#define UI_PARAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_paramWidget
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkLBP;
    QSlider *ParticlesNumSlider;
    QLineEdit *particleNumEdit;
    QLabel *label;
    QGroupBox *groupBox_2;
    QCheckBox *checkPHash;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSlider *searchRadiusSlider;
    QLineEdit *radiusEdit;
    QLabel *label_2;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkHOG;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkFixWnd;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkMultiScale;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *methodEdit;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *paramButton;

    void setupUi(QWidget *paramWidget)
    {
        if (paramWidget->objectName().isEmpty())
            paramWidget->setObjectName(QStringLiteral("paramWidget"));
        paramWidget->resize(340, 290);
        groupBox = new QGroupBox(paramWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 321, 61));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 281, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        checkLBP = new QCheckBox(layoutWidget);
        checkLBP->setObjectName(QStringLiteral("checkLBP"));
        checkLBP->setTristate(false);

        horizontalLayout->addWidget(checkLBP);

        ParticlesNumSlider = new QSlider(layoutWidget);
        ParticlesNumSlider->setObjectName(QStringLiteral("ParticlesNumSlider"));
        ParticlesNumSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(ParticlesNumSlider);

        particleNumEdit = new QLineEdit(layoutWidget);
        particleNumEdit->setObjectName(QStringLiteral("particleNumEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(particleNumEdit->sizePolicy().hasHeightForWidth());
        particleNumEdit->setSizePolicy(sizePolicy);
        particleNumEdit->setMinimumSize(QSize(41, 20));
        particleNumEdit->setMaximumSize(QSize(41, 20));

        horizontalLayout->addWidget(particleNumEdit);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        groupBox_2 = new QGroupBox(paramWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 70, 321, 51));
        checkPHash = new QCheckBox(groupBox_2);
        checkPHash->setObjectName(QStringLiteral("checkPHash"));
        checkPHash->setGeometry(QRect(20, 20, 81, 16));
        groupBox_3 = new QGroupBox(paramWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 120, 321, 61));
        layoutWidget1 = new QWidget(groupBox_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 20, 281, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        searchRadiusSlider = new QSlider(layoutWidget1);
        searchRadiusSlider->setObjectName(QStringLiteral("searchRadiusSlider"));
        searchRadiusSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(searchRadiusSlider);

        radiusEdit = new QLineEdit(layoutWidget1);
        radiusEdit->setObjectName(QStringLiteral("radiusEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(41);
        sizePolicy1.setVerticalStretch(20);
        sizePolicy1.setHeightForWidth(radiusEdit->sizePolicy().hasHeightForWidth());
        radiusEdit->setSizePolicy(sizePolicy1);
        radiusEdit->setMinimumSize(QSize(41, 20));
        radiusEdit->setMaximumSize(QSize(41, 20));

        horizontalLayout_2->addWidget(radiusEdit);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        groupBox_4 = new QGroupBox(paramWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 180, 321, 61));
        layoutWidget2 = new QWidget(groupBox_4);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 20, 281, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        checkHOG = new QCheckBox(layoutWidget2);
        checkHOG->setObjectName(QStringLiteral("checkHOG"));

        horizontalLayout_3->addWidget(checkHOG);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        checkFixWnd = new QCheckBox(layoutWidget2);
        checkFixWnd->setObjectName(QStringLiteral("checkFixWnd"));

        horizontalLayout_3->addWidget(checkFixWnd);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        checkMultiScale = new QCheckBox(layoutWidget2);
        checkMultiScale->setObjectName(QStringLiteral("checkMultiScale"));

        horizontalLayout_3->addWidget(checkMultiScale);

        widget = new QWidget(paramWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 250, 281, 25));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        methodEdit = new QLineEdit(widget);
        methodEdit->setObjectName(QStringLiteral("methodEdit"));
        methodEdit->setMinimumSize(QSize(41, 20));
        methodEdit->setMaximumSize(QSize(41, 20));

        horizontalLayout_4->addWidget(methodEdit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        paramButton = new QPushButton(widget);
        paramButton->setObjectName(QStringLiteral("paramButton"));

        horizontalLayout_4->addWidget(paramButton);


        retranslateUi(paramWidget);

        QMetaObject::connectSlotsByName(paramWidget);
    } // setupUi

    void retranslateUi(QWidget *paramWidget)
    {
        paramWidget->setWindowTitle(QApplication::translate("paramWidget", "paramWidget", 0));
        groupBox->setTitle(QApplication::translate("paramWidget", "\347\262\222\345\255\220\346\273\244\346\263\242", 0));
        checkLBP->setText(QApplication::translate("paramWidget", "\344\275\277\347\224\250LBP", 0));
        label->setText(QApplication::translate("paramWidget", "\347\262\222\345\255\220\346\225\260", 0));
        groupBox_2->setTitle(QApplication::translate("paramWidget", "Hash", 0));
        checkPHash->setText(QApplication::translate("paramWidget", "\344\275\277\347\224\250pHash", 0));
        groupBox_3->setTitle(QApplication::translate("paramWidget", "Struck", 0));
        label_2->setText(QApplication::translate("paramWidget", "\346\220\234\347\264\242\345\215\212\345\276\204", 0));
        groupBox_4->setTitle(QApplication::translate("paramWidget", "KCF", 0));
        checkHOG->setText(QApplication::translate("paramWidget", "\344\275\277\347\224\250HOG", 0));
        checkFixWnd->setText(QApplication::translate("paramWidget", "\345\233\272\345\256\232\347\252\227\345\217\243", 0));
        checkMultiScale->setText(QApplication::translate("paramWidget", "\345\244\232\345\260\272\345\272\246", 0));
        label_3->setText(QApplication::translate("paramWidget", "\350\267\237\350\270\252\346\226\271\346\263\225", 0));
        paramButton->setText(QApplication::translate("paramWidget", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class paramWidget: public Ui_paramWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMWIDGET_H
