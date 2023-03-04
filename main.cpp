#include "battleboxmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BattleBoxMainWindow w;
    w.show();
    return a.exec();
}
