#pragma once
/********************************************************************************
** Form generated from reading UI file ''
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CStatusDialogClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *dockWidgetLabel;
    QComboBox *dockWidgetsComboBox;
    QGroupBox *statusGroupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *isClosedCheckBox;
    QCheckBox *isFloatingCheckBox;
    QCheckBox *tabbedCheckBox;
    QCheckBox *isCurrentTabCheckBox;
    QGroupBox *flagsGroupBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *closableCheckBox;
    QCheckBox *movableCheckBox;
    QCheckBox *floatableCheckBox;
    QCheckBox *deleteOnCloseCheckBox;
    QCheckBox *customCloseHandlingCheckBox;

    void setupUi(QDialog *CStatusDialogClass)
    {
        if (CStatusDialogClass->objectName().isEmpty())
            CStatusDialogClass->setObjectName(QString::fromUtf8("CStatusDialogClass"));
        CStatusDialogClass->resize(357, 428);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CStatusDialogClass->sizePolicy().hasHeightForWidth());
        CStatusDialogClass->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(CStatusDialogClass);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        dockWidgetLabel = new QLabel(CStatusDialogClass);
        dockWidgetLabel->setObjectName(QString::fromUtf8("dockWidgetLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dockWidgetLabel->sizePolicy().hasHeightForWidth());
        dockWidgetLabel->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(dockWidgetLabel);

        dockWidgetsComboBox = new QComboBox(CStatusDialogClass);
        dockWidgetsComboBox->setObjectName(QString::fromUtf8("dockWidgetsComboBox"));
        dockWidgetsComboBox->setMinimumSize(QSize(300, 0));

        verticalLayout_2->addWidget(dockWidgetsComboBox);

        statusGroupBox = new QGroupBox(CStatusDialogClass);
        statusGroupBox->setObjectName(QString::fromUtf8("statusGroupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(statusGroupBox->sizePolicy().hasHeightForWidth());
        statusGroupBox->setSizePolicy(sizePolicy2);
        verticalLayout = new QVBoxLayout(statusGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        isClosedCheckBox = new QCheckBox(statusGroupBox);
        isClosedCheckBox->setObjectName(QString::fromUtf8("isClosedCheckBox"));

        verticalLayout->addWidget(isClosedCheckBox);

        isFloatingCheckBox = new QCheckBox(statusGroupBox);
        isFloatingCheckBox->setObjectName(QString::fromUtf8("isFloatingCheckBox"));

        verticalLayout->addWidget(isFloatingCheckBox);

        tabbedCheckBox = new QCheckBox(statusGroupBox);
        tabbedCheckBox->setObjectName(QString::fromUtf8("tabbedCheckBox"));

        verticalLayout->addWidget(tabbedCheckBox);

        isCurrentTabCheckBox = new QCheckBox(statusGroupBox);
        isCurrentTabCheckBox->setObjectName(QString::fromUtf8("isCurrentTabCheckBox"));

        verticalLayout->addWidget(isCurrentTabCheckBox);


        verticalLayout_2->addWidget(statusGroupBox);

        flagsGroupBox = new QGroupBox(CStatusDialogClass);
        flagsGroupBox->setObjectName(QString::fromUtf8("flagsGroupBox"));
        sizePolicy2.setHeightForWidth(flagsGroupBox->sizePolicy().hasHeightForWidth());
        flagsGroupBox->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(flagsGroupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        closableCheckBox = new QCheckBox(flagsGroupBox);
        closableCheckBox->setObjectName(QString::fromUtf8("closableCheckBox"));

        verticalLayout_3->addWidget(closableCheckBox);

        movableCheckBox = new QCheckBox(flagsGroupBox);
        movableCheckBox->setObjectName(QString::fromUtf8("movableCheckBox"));

        verticalLayout_3->addWidget(movableCheckBox);

        floatableCheckBox = new QCheckBox(flagsGroupBox);
        floatableCheckBox->setObjectName(QString::fromUtf8("floatableCheckBox"));

        verticalLayout_3->addWidget(floatableCheckBox);

        deleteOnCloseCheckBox = new QCheckBox(flagsGroupBox);
        deleteOnCloseCheckBox->setObjectName(QString::fromUtf8("deleteOnCloseCheckBox"));

        verticalLayout_3->addWidget(deleteOnCloseCheckBox);

        customCloseHandlingCheckBox = new QCheckBox(flagsGroupBox);
        customCloseHandlingCheckBox->setObjectName(QString::fromUtf8("customCloseHandlingCheckBox"));

        verticalLayout_3->addWidget(customCloseHandlingCheckBox);


        verticalLayout_2->addWidget(flagsGroupBox);


        retranslateUi(CStatusDialogClass);

        QMetaObject::connectSlotsByName(CStatusDialogClass);
    } // setupUi

    void retranslateUi(QDialog *CStatusDialogClass)
    {
        CStatusDialogClass->setWindowTitle(QCoreApplication::translate("CStatusDialogClass", "Dock Widget Status", nullptr));
        dockWidgetLabel->setText(QCoreApplication::translate("CStatusDialogClass", "Dock Widget:", nullptr));
        statusGroupBox->setTitle(QCoreApplication::translate("CStatusDialogClass", "Status", nullptr));
        isClosedCheckBox->setText(QCoreApplication::translate("CStatusDialogClass", "closed", nullptr));
        isFloatingCheckBox->setText(QCoreApplication::translate("CStatusDialogClass", "floating", nullptr));
        tabbedCheckBox->setText(QCoreApplication::translate("CStatusDialogClass", "tabbed", nullptr));
        isCurrentTabCheckBox->setText(QCoreApplication::translate("CStatusDialogClass", "is current tab", nullptr));
        flagsGroupBox->setTitle(QCoreApplication::translate("CStatusDialogClass", "Feature Flags", nullptr));
        closableCheckBox->setText(QCoreApplication::translate("CStatusDialogClass", "DockWidgetClosable", nullptr));
        movableCheckBox->setText(QCoreApplication::translate("CStatusDialogClass", "DockWidgetMovable", nullptr));
        floatableCheckBox->setText(QCoreApplication::translate("CStatusDialogClass", "DockWidgetFloatable", nullptr));
        deleteOnCloseCheckBox->setText(QCoreApplication::translate("CStatusDialogClass", "DockWidgetDeleteOnClose", nullptr));
        customCloseHandlingCheckBox->setText(QCoreApplication::translate("CStatusDialogClass", "CustomCloseHandling", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CStatusDialogClass: public Ui_CStatusDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

