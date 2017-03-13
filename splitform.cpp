#include "splitform.h"
#include "ui_splitform.h"

SplitForm::SplitForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SplitForm)
{
    ui->setupUi(this);
}

SplitForm::~SplitForm()
{
    delete ui;
}
