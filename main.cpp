#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QList>
#include "cpoint.h"
#include <trackparser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TrackParser parser;
    Track t=parser.parse("/home/anisart/GPS/doc.kml");
//    qDebug()<<t.deletePoint(1);
    CPoint c; c.setData();
    qDebug()<<t.insertPoint(2,c);
    qDebug()<<t.getListIds();
    QList<CPoint> points;
    int i = 0;
    while(i<t.getListIds().count())
    {
        points.append(t.getPoint(t.getListIds().at(i)));
        i++;
    }
    bool hasEle=t.hasEle;
    bool hasTime=t.hasTime;
    qDebug()<<hasEle<<hasTime;
    qDebug()<<t.title;
    if (hasEle && hasTime)
        foreach (CPoint point, points)
            qDebug()<<"lat = "<<point.getLat()<<", lon = "<<point.getLon()<<", ele = "<<point.getEle()<<" "<<point.getTime().toString(Qt::DefaultLocaleLongDate);
    else if (hasEle)
        foreach (CPoint point, points)
            qDebug()<<"lat = "<<point.getLat()<<", lon = "<<point.getLon()<<", ele = "<<point.getEle();
    else
        foreach (CPoint point, points)
            qDebug()<<"lat = "<<point.getLat()<<", lon = "<<point.getLon();

    return a.exec();
}
