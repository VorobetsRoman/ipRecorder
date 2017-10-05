#ifndef RECORDERFORM_H
#define RECORDERFORM_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>
#include <QTime>

namespace Ui {
class RecorderForm;
}

class RecorderForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecorderForm                   (QWidget *parent = 0);
        ~RecorderForm                       ();

public slots:
    void slWriteToFile                        ();

private slots:
    void on_tbFileNameForRecording_released ();
    void on_pbStartStopRecord_released      ();
    void on_pbPauseRecord_released          ();

    void on_cbTimeMarker_toggled            (bool checked);

private:
    Ui::RecorderForm *ui        {NULL};
    QFile       *workFile       {NULL};
    bool        recordingOn     {false};
    bool        pauseOn         {false};
    qint64      tickCount       {0};
    qint64      fileSize        {0};
    QTime       lastTime;

    void writeHeader                        ();
};

#endif // RECORDERFORM_H
