#ifndef SPLITFORM_H
#define SPLITFORM_H

#include <QWidget>

namespace Ui {
class SplitForm;
}

class SplitForm : public QWidget
{
    Q_OBJECT

public:
    explicit SplitForm(QWidget *parent = 0);
    ~SplitForm();

private:
    Ui::SplitForm *ui;
};

#endif // SPLITFORM_H
