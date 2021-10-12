/*! @file Форма основного окна,
  * содержит вкладки с интерфейсами
  * управления записью, воспроизведением, склеиванием файлов
  */
#ifndef IPRECORDERWGT_H
#define IPRECORDERWGT_H

#include <QWidget>
#include <QTimer>
#include <QFile>
#include "playerform.h"
#include "recorderform.h"
#include "Common/socketpeer.h"
#include "Common/serverpeer.h"
//#include "peeruifacade.h"


namespace Ui {
class IpRecorderWgt;
}

class IpRecorderWgt : public QWidget
{
    Q_OBJECT

public:
    explicit IpRecorderWgt(QWidget *parent = nullptr);
        ~IpRecorderWgt();

private slots:
    void on_pbStartServer_released();
    void on_pbConnectToServer_released();

private:
    Ui::IpRecorderWgt   *mp_ui             {nullptr}; ///< Форма окна
    PlayerForm          *mp_playerForm     {nullptr}; ///< Форма управления воспроизведением
    RecorderForm        *mp_recorderForm   {nullptr}; ///< Форма управления записью
    QSharedPointer <Peer> m_peer;

    void m_initSettings();
    void m_storeSettings();
    void m_updateUi();
};

#endif // IPRECORDERWGT_H
