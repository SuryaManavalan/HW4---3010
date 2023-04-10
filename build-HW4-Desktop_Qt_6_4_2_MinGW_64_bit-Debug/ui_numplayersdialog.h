/********************************************************************************
** Form generated from reading UI file 'numplayersdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMPLAYERSDIALOG_H
#define UI_NUMPLAYERSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_NumPlayersDialog
{
public:
    QSpinBox *NumSpin;
    QPushButton *submitButton;
    QLabel *label;

    void setupUi(QDialog *NumPlayersDialog)
    {
        if (NumPlayersDialog->objectName().isEmpty())
            NumPlayersDialog->setObjectName("NumPlayersDialog");
        NumPlayersDialog->resize(400, 187);
        NumSpin = new QSpinBox(NumPlayersDialog);
        NumSpin->setObjectName("NumSpin");
        NumSpin->setGeometry(QRect(140, 70, 71, 41));
        NumSpin->setMinimum(2);
        NumSpin->setMaximum(4);
        submitButton = new QPushButton(NumPlayersDialog);
        submitButton->setObjectName("submitButton");
        submitButton->setGeometry(QRect(260, 130, 80, 27));
        label = new QLabel(NumPlayersDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 381, 61));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 24pt \"Segoe UI\";"));

        retranslateUi(NumPlayersDialog);

        QMetaObject::connectSlotsByName(NumPlayersDialog);
    } // setupUi

    void retranslateUi(QDialog *NumPlayersDialog)
    {
        NumPlayersDialog->setWindowTitle(QCoreApplication::translate("NumPlayersDialog", "Dialog", nullptr));
        submitButton->setText(QCoreApplication::translate("NumPlayersDialog", "Submit", nullptr));
        label->setText(QCoreApplication::translate("NumPlayersDialog", "Enter number of players", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NumPlayersDialog: public Ui_NumPlayersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMPLAYERSDIALOG_H
