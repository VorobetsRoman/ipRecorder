/********************************************************************************
** Form generated from reading UI file 'recorderform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDERFORM_H
#define UI_RECORDERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecorderForm
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *cbTimeMarker;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *tbFileNameForRecording;
    QLabel *lbFileNameForRecording;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pbStartStopRecord;
    QPushButton *pbPauseRecord;
    QLabel *lbRecorded;
    QLabel *lbRecordedCount;
    QLabel *lbRecordedSize;
    QLabel *lb;

    void setupUi(QWidget *RecorderForm)
    {
        if (RecorderForm->objectName().isEmpty())
            RecorderForm->setObjectName(QString::fromUtf8("RecorderForm"));
        RecorderForm->resize(311, 110);
        verticalLayout = new QVBoxLayout(RecorderForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cbTimeMarker = new QCheckBox(RecorderForm);
        cbTimeMarker->setObjectName(QString::fromUtf8("cbTimeMarker"));

        verticalLayout->addWidget(cbTimeMarker);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        tbFileNameForRecording = new QToolButton(RecorderForm);
        tbFileNameForRecording->setObjectName(QString::fromUtf8("tbFileNameForRecording"));

        horizontalLayout_4->addWidget(tbFileNameForRecording);

        lbFileNameForRecording = new QLabel(RecorderForm);
        lbFileNameForRecording->setObjectName(QString::fromUtf8("lbFileNameForRecording"));
        lbFileNameForRecording->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_4->addWidget(lbFileNameForRecording);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pbStartStopRecord = new QPushButton(RecorderForm);
        pbStartStopRecord->setObjectName(QString::fromUtf8("pbStartStopRecord"));
        pbStartStopRecord->setMaximumSize(QSize(25, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Buttons/media-record-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/Buttons/media-stop-32.png"), QSize(), QIcon::Normal, QIcon::On);
        pbStartStopRecord->setIcon(icon);

        horizontalLayout_7->addWidget(pbStartStopRecord);

        pbPauseRecord = new QPushButton(RecorderForm);
        pbPauseRecord->setObjectName(QString::fromUtf8("pbPauseRecord"));
        pbPauseRecord->setMaximumSize(QSize(25, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Buttons/media-pause-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPauseRecord->setIcon(icon1);
        pbPauseRecord->setFlat(false);

        horizontalLayout_7->addWidget(pbPauseRecord);

        lbRecorded = new QLabel(RecorderForm);
        lbRecorded->setObjectName(QString::fromUtf8("lbRecorded"));
        lbRecorded->setMaximumSize(QSize(16777215, 20));
        lbRecorded->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(lbRecorded);

        lbRecordedCount = new QLabel(RecorderForm);
        lbRecordedCount->setObjectName(QString::fromUtf8("lbRecordedCount"));
        lbRecordedCount->setMinimumSize(QSize(60, 0));
        lbRecordedCount->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_7->addWidget(lbRecordedCount);

        lbRecordedSize = new QLabel(RecorderForm);
        lbRecordedSize->setObjectName(QString::fromUtf8("lbRecordedSize"));
        lbRecordedSize->setMinimumSize(QSize(60, 0));
        lbRecordedSize->setMaximumSize(QSize(16777215, 20));
        lbRecordedSize->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(lbRecordedSize);

        lb = new QLabel(RecorderForm);
        lb->setObjectName(QString::fromUtf8("lb"));
        lb->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_7->addWidget(lb);


        verticalLayout->addLayout(horizontalLayout_7);


        retranslateUi(RecorderForm);

        QMetaObject::connectSlotsByName(RecorderForm);
    } // setupUi

    void retranslateUi(QWidget *RecorderForm)
    {
        RecorderForm->setWindowTitle(QApplication::translate("RecorderForm", "Form", nullptr));
        cbTimeMarker->setText(QApplication::translate("RecorderForm", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\262\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271 \320\274\320\260\321\200\320\272\320\265\321\200", nullptr));
        tbFileNameForRecording->setText(QApplication::translate("RecorderForm", "...", nullptr));
        lbFileNameForRecording->setText(QApplication::translate("RecorderForm", "\320\230\320\274\321\217 \321\204\320\260\320\271\320\273\320\260 \320\264\320\273\321\217 \320\267\320\260\320\277\320\270\321\201\320\270", nullptr));
        pbStartStopRecord->setText(QString());
        pbPauseRecord->setText(QString());
        lbRecorded->setText(QApplication::translate("RecorderForm", "\320\227\320\260\320\277\320\270\321\201\320\260\320\275\320\276:", nullptr));
        lbRecordedCount->setText(QApplication::translate("RecorderForm", "0", nullptr));
        lbRecordedSize->setText(QApplication::translate("RecorderForm", "0", nullptr));
        lb->setText(QApplication::translate("RecorderForm", "\320\234\320\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecorderForm: public Ui_RecorderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDERFORM_H
