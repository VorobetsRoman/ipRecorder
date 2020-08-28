/********************************************************************************
** Form generated from reading UI file 'iprecorderwgt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPRECORDERWGT_H
#define UI_IPRECORDERWGT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <playerform.h>
#include <recorderform.h>
#include <splitform.h>

QT_BEGIN_NAMESPACE

class Ui_IpRecorderWgt
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label;
    QLineEdit *lePortName;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QLineEdit *leServerName;
    QSpacerItem *horizontalSpacer_5;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbStartServer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbConnectToServer;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLabel *lbConnectionStatus;
    QTabWidget *splitWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    RecorderForm *recorderWgt;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    PlayerForm *playerWgt;
    QWidget *tab_3;
    QGridLayout *gridLayout;
    SplitForm *widget;

    void setupUi(QWidget *IpRecorderWgt)
    {
        if (IpRecorderWgt->objectName().isEmpty())
            IpRecorderWgt->setObjectName(QString::fromUtf8("IpRecorderWgt"));
        IpRecorderWgt->resize(400, 400);
        verticalLayout = new QVBoxLayout(IpRecorderWgt);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(IpRecorderWgt);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 84));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(40, 0));
        label->setMaximumSize(QSize(60, 16777215));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        lePortName = new QLineEdit(frame);
        lePortName->setObjectName(QString::fromUtf8("lePortName"));
        lePortName->setMinimumSize(QSize(51, 0));
        lePortName->setMaximumSize(QSize(60, 16777215));
        lePortName->setMaxLength(5);

        horizontalLayout->addWidget(lePortName);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        leServerName = new QLineEdit(frame);
        leServerName->setObjectName(QString::fromUtf8("leServerName"));
        leServerName->setEnabled(true);
        leServerName->setMinimumSize(QSize(91, 0));
        leServerName->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(leServerName);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pbStartServer = new QPushButton(frame);
        pbStartServer->setObjectName(QString::fromUtf8("pbStartServer"));
        pbStartServer->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Buttons/media-play-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbStartServer->setIcon(icon);

        horizontalLayout_2->addWidget(pbStartServer);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pbConnectToServer = new QPushButton(frame);
        pbConnectToServer->setObjectName(QString::fromUtf8("pbConnectToServer"));
        pbConnectToServer->setEnabled(true);
        pbConnectToServer->setMaximumSize(QSize(80, 16777215));
        pbConnectToServer->setIcon(icon);

        horizontalLayout_2->addWidget(pbConnectToServer);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(frame);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_4 = new QLabel(IpRecorderWgt);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_4);

        lbConnectionStatus = new QLabel(IpRecorderWgt);
        lbConnectionStatus->setObjectName(QString::fromUtf8("lbConnectionStatus"));

        horizontalLayout_8->addWidget(lbConnectionStatus);


        verticalLayout->addLayout(horizontalLayout_8);

        splitWidget = new QTabWidget(IpRecorderWgt);
        splitWidget->setObjectName(QString::fromUtf8("splitWidget"));
        splitWidget->setDocumentMode(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        recorderWgt = new RecorderForm(tab);
        recorderWgt->setObjectName(QString::fromUtf8("recorderWgt"));

        verticalLayout_3->addWidget(recorderWgt);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Buttons/media-record-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        splitWidget->addTab(tab, icon1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        playerWgt = new PlayerForm(tab_2);
        playerWgt->setObjectName(QString::fromUtf8("playerWgt"));

        verticalLayout_4->addWidget(playerWgt);

        splitWidget->addTab(tab_2, icon, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout = new QGridLayout(tab_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new SplitForm(tab_3);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        splitWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(splitWidget);


        retranslateUi(IpRecorderWgt);

        splitWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(IpRecorderWgt);
    } // setupUi

    void retranslateUi(QWidget *IpRecorderWgt)
    {
        IpRecorderWgt->setWindowTitle(QApplication::translate("IpRecorderWgt", "IpRecorderWgt", nullptr));
        label->setText(QApplication::translate("IpRecorderWgt", "\320\237\320\276\321\200\321\202:", nullptr));
        lePortName->setInputMask(QApplication::translate("IpRecorderWgt", "00000", nullptr));
        lePortName->setText(QApplication::translate("IpRecorderWgt", "5000", nullptr));
        label_2->setText(QApplication::translate("IpRecorderWgt", "\320\220\320\264\321\200\320\265\321\201:", nullptr));
        leServerName->setInputMask(QApplication::translate("IpRecorderWgt", "000.000.000.000", nullptr));
        leServerName->setText(QApplication::translate("IpRecorderWgt", "127.0.0.1", nullptr));
        pbStartServer->setText(QApplication::translate("IpRecorderWgt", "\320\241\320\265\321\200\320\262\320\265\321\200", nullptr));
        pbConnectToServer->setText(QApplication::translate("IpRecorderWgt", "\320\232\320\273\320\270\320\265\320\275\321\202", nullptr));
        label_4->setText(QApplication::translate("IpRecorderWgt", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\321\217:", nullptr));
        lbConnectionStatus->setText(QString());
        splitWidget->setTabText(splitWidget->indexOf(tab), QString());
        splitWidget->setTabText(splitWidget->indexOf(tab_2), QString());
        splitWidget->setTabText(splitWidget->indexOf(tab_3), QApplication::translate("IpRecorderWgt", "\320\241\321\200\320\260\321\211\320\270\320\262\320\260\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IpRecorderWgt: public Ui_IpRecorderWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPRECORDERWGT_H
