/********************************************************************************
** Form generated from reading UI file 'playerform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERFORM_H
#define UI_PLAYERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *tbFileNameForPlayer;
    QLabel *lbFileNameForPlayer;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbTimeMarkerIsOn;
    QRadioButton *rbSetPlaySpeed;
    QSlider *hsPlaySpeed;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pbStartStopPlayer;
    QPushButton *pbPausePlay;
    QProgressBar *progressPlayer;

    void setupUi(QWidget *PlayerForm)
    {
        if (PlayerForm->objectName().isEmpty())
            PlayerForm->setObjectName(QString::fromUtf8("PlayerForm"));
        PlayerForm->resize(262, 170);
        verticalLayout_2 = new QVBoxLayout(PlayerForm);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        tbFileNameForPlayer = new QToolButton(PlayerForm);
        tbFileNameForPlayer->setObjectName(QString::fromUtf8("tbFileNameForPlayer"));

        horizontalLayout_5->addWidget(tbFileNameForPlayer);

        lbFileNameForPlayer = new QLabel(PlayerForm);
        lbFileNameForPlayer->setObjectName(QString::fromUtf8("lbFileNameForPlayer"));

        horizontalLayout_5->addWidget(lbFileNameForPlayer);


        verticalLayout_2->addLayout(horizontalLayout_5);

        frame_2 = new QFrame(PlayerForm);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(217, 217, 217);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rbTimeMarkerIsOn = new QRadioButton(frame_2);
        rbTimeMarkerIsOn->setObjectName(QString::fromUtf8("rbTimeMarkerIsOn"));
        rbTimeMarkerIsOn->setEnabled(false);

        verticalLayout->addWidget(rbTimeMarkerIsOn);

        rbSetPlaySpeed = new QRadioButton(frame_2);
        rbSetPlaySpeed->setObjectName(QString::fromUtf8("rbSetPlaySpeed"));
        rbSetPlaySpeed->setChecked(true);

        verticalLayout->addWidget(rbSetPlaySpeed);

        hsPlaySpeed = new QSlider(frame_2);
        hsPlaySpeed->setObjectName(QString::fromUtf8("hsPlaySpeed"));
        hsPlaySpeed->setMinimum(1);
        hsPlaySpeed->setMaximum(20);
        hsPlaySpeed->setValue(10);
        hsPlaySpeed->setOrientation(Qt::Horizontal);
        hsPlaySpeed->setTickPosition(QSlider::TicksBelow);
        hsPlaySpeed->setTickInterval(1);

        verticalLayout->addWidget(hsPlaySpeed);


        verticalLayout_2->addWidget(frame_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pbStartStopPlayer = new QPushButton(PlayerForm);
        pbStartStopPlayer->setObjectName(QString::fromUtf8("pbStartStopPlayer"));
        pbStartStopPlayer->setMaximumSize(QSize(25, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Buttons/media-play-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/Buttons/media-stop-32.png"), QSize(), QIcon::Normal, QIcon::On);
        pbStartStopPlayer->setIcon(icon);

        horizontalLayout_6->addWidget(pbStartStopPlayer);

        pbPausePlay = new QPushButton(PlayerForm);
        pbPausePlay->setObjectName(QString::fromUtf8("pbPausePlay"));
        pbPausePlay->setMaximumSize(QSize(25, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Buttons/media-pause-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPausePlay->setIcon(icon1);

        horizontalLayout_6->addWidget(pbPausePlay);

        progressPlayer = new QProgressBar(PlayerForm);
        progressPlayer->setObjectName(QString::fromUtf8("progressPlayer"));
        progressPlayer->setValue(0);

        horizontalLayout_6->addWidget(progressPlayer);


        verticalLayout_2->addLayout(horizontalLayout_6);


        retranslateUi(PlayerForm);

        QMetaObject::connectSlotsByName(PlayerForm);
    } // setupUi

    void retranslateUi(QWidget *PlayerForm)
    {
        PlayerForm->setWindowTitle(QApplication::translate("PlayerForm", "Form", nullptr));
        tbFileNameForPlayer->setText(QApplication::translate("PlayerForm", "...", nullptr));
        lbFileNameForPlayer->setText(QApplication::translate("PlayerForm", "\320\230\320\274\321\217 \321\204\320\260\320\271\320\273\320\260.", nullptr));
        rbTimeMarkerIsOn->setText(QApplication::translate("PlayerForm", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\262\321\200\320\265\320\274\320\265\320\275\320\275\320\276\320\271 \320\274\320\260\321\200\320\272\320\265\321\200", nullptr));
        rbSetPlaySpeed->setText(QApplication::translate("PlayerForm", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\262\320\276\321\201\320\277\321\200\320\276\320\270\320\267\320\262\320\265\320\264\320\265\320\275\320\270\321\217", nullptr));
        pbStartStopPlayer->setText(QString());
        pbPausePlay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PlayerForm: public Ui_PlayerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERFORM_H
