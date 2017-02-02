#include "iprecorderwgt.h"
#include "ui_iprecorderwgt.h"



//===================================
IpRecorderWgt::IpRecorderWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IpRecorderWgt)
{
    ui->setupUi(this);
}




//===================================
IpRecorderWgt::~IpRecorderWgt()
{
    delete ui;
}



//===================================
void IpRecorderWgt::on_lePortName_editingFinished()
{

}



//===================================
void IpRecorderWgt::on_rbServerChoice_toggled(bool checked)
{

}



//===================================
void IpRecorderWgt::on_pbStartServer_released()
{

}



//===================================
void IpRecorderWgt::on_rbClientChoice_toggled(bool checked)
{

}



//===================================
void IpRecorderWgt::on_leServerName_editingFinished()
{

}



//===================================
void IpRecorderWgt::on_pbConnectToServer_released()
{

}



//===================================
void IpRecorderWgt::on_rbTimeMarkerIsOn_toggled(bool checked)
{

}



//===================================
void IpRecorderWgt::on_rbSetPlaySpeed_toggled(bool checked)
{

}



//===================================
void IpRecorderWgt::on_hsPlaySpeed_sliderMoved(int position)
{

}



//===================================
void IpRecorderWgt::on_tbFileNameForRecording_released()
{

}



//===================================
void IpRecorderWgt::on_pbStartStopRecord_released()
{

}



//===================================
void IpRecorderWgt::on_pbPauseRecord_released()
{

}



//===================================
void IpRecorderWgt::on_tbFileNameForPlayer_released()
{

}



//===================================
void IpRecorderWgt::on_pbStartStopPlayer_released()
{

}



//===================================
void IpRecorderWgt::on_pbPauseRecord_2_released()
{

}
