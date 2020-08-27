/********************************************************************************
** Form generated from reading UI file 'splitform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPLITFORM_H
#define UI_SPLITFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SplitForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QListView *listView;
    QVBoxLayout *verticalLayout;
    QPushButton *pbAdd;
    QPushButton *pbSkip;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pbSplit;

    void setupUi(QWidget *SplitForm)
    {
        if (SplitForm->objectName().isEmpty())
            SplitForm->setObjectName(QString::fromUtf8("SplitForm"));
        SplitForm->resize(262, 170);
        verticalLayout_2 = new QVBoxLayout(SplitForm);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        listView = new QListView(SplitForm);
        listView->setObjectName(QString::fromUtf8("listView"));

        horizontalLayout_2->addWidget(listView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pbAdd = new QPushButton(SplitForm);
        pbAdd->setObjectName(QString::fromUtf8("pbAdd"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pbAdd->sizePolicy().hasHeightForWidth());
        pbAdd->setSizePolicy(sizePolicy);
        pbAdd->setMaximumSize(QSize(23, 23));

        verticalLayout->addWidget(pbAdd);

        pbSkip = new QPushButton(SplitForm);
        pbSkip->setObjectName(QString::fromUtf8("pbSkip"));
        sizePolicy.setHeightForWidth(pbSkip->sizePolicy().hasHeightForWidth());
        pbSkip->setSizePolicy(sizePolicy);
        pbSkip->setMaximumSize(QSize(23, 23));

        verticalLayout->addWidget(pbSkip);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        label = new QLabel(SplitForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(SplitForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pbSplit = new QPushButton(SplitForm);
        pbSplit->setObjectName(QString::fromUtf8("pbSplit"));
        sizePolicy.setHeightForWidth(pbSplit->sizePolicy().hasHeightForWidth());
        pbSplit->setSizePolicy(sizePolicy);
        pbSplit->setMinimumSize(QSize(23, 23));
        pbSplit->setMaximumSize(QSize(23, 23));

        horizontalLayout->addWidget(pbSplit);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(SplitForm);

        QMetaObject::connectSlotsByName(SplitForm);
    } // setupUi

    void retranslateUi(QWidget *SplitForm)
    {
        SplitForm->setWindowTitle(QApplication::translate("SplitForm", "Form", nullptr));
        pbAdd->setText(QString());
        pbSkip->setText(QString());
        label->setText(QApplication::translate("SplitForm", "Split to:", nullptr));
        pbSplit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SplitForm: public Ui_SplitForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPLITFORM_H
