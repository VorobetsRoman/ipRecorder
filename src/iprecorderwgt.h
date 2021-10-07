/*!
  * @file Форма основного окна, содержит вкладки
  * с интерфейсами управления записью, воспроизведением, склеиванием файлов
  */
#ifndef IPRECORDERWGT_H
#define IPRECORDERWGT_H

#include <QWidget>
#include <QTimer>
#include <QFile>
#include "playerform.h"
#include "recorderform.h"


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

    void m_initSettings();
    void m_updateUi(bool isServer, bool started);
    void m_storeSettings();
};

#endif // IPRECORDERWGT_H
