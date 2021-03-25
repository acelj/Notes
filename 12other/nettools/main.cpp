#include "mainwindow.h"
#include <QApplication>
#include <algorithm>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QMap<int, QString> map;
//    map[0] = "000";
//    map[1] = "111";
//    map[3] = "333";
//    qDebug() << map[1];
//    QString s = "333";
//    for(auto it = map.begin(); it != map.end(); it ++)
//    {
//        if(it.value() == s)
//            qDebug() << it.key();
//    }

    return a.exec();
}
