#include "iprecorderwgt.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IpRecorderWgt w;
    w.show();

    return a.exec();
}
