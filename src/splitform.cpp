#include "splitform.h"
#include "ui_splitform.h"

SplitForm::SplitForm(QWidget *parent) :
    QWidget(parent),
    mp_ui(new Ui::SplitForm)
{
    mp_ui->setupUi(this);
}

SplitForm::~SplitForm()
{
    delete mp_ui;
}
