#ifndef PLAYERFORM_H
#define PLAYERFORM_H

#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QTcpSocket>

namespace Ui {
class PlayerForm;
}

class PlayerForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerForm(QWidget *parent = nullptr);
        ~PlayerForm();
    void setSocket(QTcpSocket* newSocket);

private slots:
    void on_tbFileNameForPlayer_released();
    void on_rbSetPlaySpeed_toggled(bool checked);
    void on_rbTimeMarkerIsOn_toggled(bool checked);
    void on_hsPlaySpeed_sliderMoved(int position);
    void on_pbStartStopPlayer_released();
    void on_pbPausePlay_released();

    void sl_playTimerTimeout();

private:
    Ui::PlayerForm *mp_ui           {nullptr};

    bool        m_playingIsOn       {false};
    bool        m_pauseIsOn         {false};
    QTimer      *mp_playTimer       {nullptr};
    qint64      m_playDelay         {2000};
    QFile       *mp_workFile        {nullptr};
    QTcpSocket  *mp_socket          {nullptr};
    bool        m_timeMarkerExist   {false};
    bool        m_compressionExist  {false};

    void m_workFileAtEnd();
};

#endif // PLAYERFORM_H
