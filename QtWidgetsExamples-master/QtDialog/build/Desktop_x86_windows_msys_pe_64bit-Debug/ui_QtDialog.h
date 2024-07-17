/********************************************************************************
** Form generated from reading UI file 'QtDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDIALOG_H
#define UI_QTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_QtDialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonMin;
    QToolButton *toolButtonMax;
    QToolButton *toolButtonClose;

    void setupUi(QDialog *QtDialog)
    {
        if (QtDialog->objectName().isEmpty())
            QtDialog->setObjectName("QtDialog");
        QtDialog->resize(540, 320);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QtDialog->sizePolicy().hasHeightForWidth());
        QtDialog->setSizePolicy(sizePolicy);
        QtDialog->setMinimumSize(QSize(540, 320));
        QtDialog->setMaximumSize(QSize(540, 320));
        gridLayout_2 = new QGridLayout(QtDialog);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(10);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(10, 10, 10, 10);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, 10, 10, 10);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButtonMin = new QToolButton(QtDialog);
        toolButtonMin->setObjectName("toolButtonMin");
        toolButtonMin->setMinimumSize(QSize(24, 24));
        toolButtonMin->setMaximumSize(QSize(24, 24));
        toolButtonMin->setStyleSheet(QString::fromUtf8("QToolButton#toolButtonMin{  \n"
"border-image: url(:/images/min(1).png);\n"
"}\n"
"\n"
"QToolButton#toolButtonMin:hover{  \n"
"border-image: url(:/images/min(3).png);\n"
"}\n"
"\n"
"QToolButton#toolButtonMin:pressed{  \n"
"border-image: url(:/images/min.png);\n"
"}\n"
""));

        horizontalLayout->addWidget(toolButtonMin);

        toolButtonMax = new QToolButton(QtDialog);
        toolButtonMax->setObjectName("toolButtonMax");
        toolButtonMax->setMinimumSize(QSize(24, 24));
        toolButtonMax->setMaximumSize(QSize(24, 24));
        toolButtonMax->setStyleSheet(QString::fromUtf8("QToolButton#toolButtonMax[maximizeProperty=\"maximize\"]{  \n"
"border-image: url(:/images/max(1).png);\n"
"}\n"
"\n"
"QToolButton#toolButtonMax[maximizeProperty=\"maximize\"]:hover{  \n"
"border-image: url(:/images/max(3).png);\n"
"}\n"
"\n"
"QToolButton#toolButtonMax[maximizeProperty=\"maximize\"]:pressed{  \n"
"border-image: url(:/images/max.png);\n"
"}\n"
"\n"
"QToolButton#toolButtonMax[maximizeProperty=\"restore\"]{  \n"
"border-image: url(:/images/restore(1).png);\n"
"}\n"
"\n"
"QToolButton#toolButtonMax[maximizeProperty=\"restore\"]:hover{  \n"
"border-image: url(:/images/restore(3).png);\n"
"}\n"
"\n"
"QToolButton#toolButtonMax[maximizeProperty=\"restore\"]:pressed{  \n"
"border-image: url(:/images/restore.png);\n"
"}"));

        horizontalLayout->addWidget(toolButtonMax);

        toolButtonClose = new QToolButton(QtDialog);
        toolButtonClose->setObjectName("toolButtonClose");
        sizePolicy.setHeightForWidth(toolButtonClose->sizePolicy().hasHeightForWidth());
        toolButtonClose->setSizePolicy(sizePolicy);
        toolButtonClose->setMinimumSize(QSize(24, 24));
        toolButtonClose->setMaximumSize(QSize(24, 24));
        toolButtonClose->setAutoFillBackground(false);
        toolButtonClose->setStyleSheet(QString::fromUtf8("QToolButton#toolButtonClose{  \n"
"border-image: url(:/images/close(1).png);\n"
"}\n"
"\n"
"QToolButton#toolButtonClose:hover{  \n"
"border-image: url(:/images/close(3).png);\n"
"}\n"
"\n"
"QToolButton#toolButtonClose:pressed{  \n"
"border-image: url(:/images/close.png);\n"
"}\n"
""));

        horizontalLayout->addWidget(toolButtonClose);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(QtDialog);

        QMetaObject::connectSlotsByName(QtDialog);
    } // setupUi

    void retranslateUi(QDialog *QtDialog)
    {
        QtDialog->setWindowTitle(QCoreApplication::translate("QtDialog", "QtDialog", nullptr));
        toolButtonMin->setText(QString());
        toolButtonMax->setText(QString());
        toolButtonClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtDialog: public Ui_QtDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDIALOG_H
