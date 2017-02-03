#ifndef RECORDERFORM_H
#define RECORDERFORM_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>

namespace Ui {
class RecorderForm;
}

class RecorderForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecorderForm(QWidget *parent = 0);
    ~RecorderForm();

public slots:
    void writeToFile                        ();

private slots:
    void on_tbFileNameForRecording_released ();
    void on_pbStartStopRecord_released      ();
    void on_pbPauseRecord_released          ();

private:
    Ui::RecorderForm *ui{NULL};
    QFile *workFile     {NULL};
    bool recordingOn    {false};
    bool pauseOn        {false};
};

#endif // RECORDERFORM_H
