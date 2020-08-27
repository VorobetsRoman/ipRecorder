#ifndef RECORDERFORM_H
#define RECORDERFORM_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>

namespace Ui {
class RecorderForm;
}

class RecorderForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecorderForm(QWidget *parent = nullptr);
        ~RecorderForm();

public slots:
    void sl_writeToFile();

private slots:
    void on_tbFileNameForRecording_released();
    void on_pbStartStopRecord_released();
    void on_pbPauseRecord_released();
    void on_cbTimeMarker_toggled(bool checked);
    void on_cd_compression_toggled(bool checked);

private:
    Ui::RecorderForm *mp_ui         {nullptr};
    QFile       *mp_workFile        {nullptr};
    bool        m_recordingIsOn     {false};
    bool        m_pauseOn           {false};
    bool        m_comressionIsOn    {false};
    bool        m_timeMarkerIsOn    {false};
    qint64      m_tickCount       {0};
    qint64      m_fileSize        {0};
    QTime       m_lastTime;
    QTimer      *mp_recordTimer     {nullptr};

    void m_writeHeader();
    void m_initRecordTimer();
};

#endif // RECORDERFORM_H
