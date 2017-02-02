#include "iprecorderwgt.h"
#include "ui_iprecorderwgt.h"
#include <QTextCodec>



//===================================
IpRecorderWgt::IpRecorderWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IpRecorderWgt)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
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




