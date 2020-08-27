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
    explicit SplitForm(QWidget *parent = nullptr);
    ~SplitForm();

private:
    Ui::SplitForm *mp_ui;
};

#endif // SPLITFORM_H
