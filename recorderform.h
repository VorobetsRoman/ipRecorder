#ifndef RECORDERFORM_H
#define RECORDERFORM_H

#include <QWidget>

namespace Ui {
class RecorderForm;
}

class RecorderForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecorderForm(QWidget *parent = 0);
    ~RecorderForm();

private slots:
    void on_tbFileNameForRecording_released();

    void on_pbStartStopRecord_released();

    void on_pbPauseRecord_released();

private:
    Ui::RecorderForm *ui;
};

#endif // RECORDERFORM_H
