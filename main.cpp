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
    QList<CPoint> points = t.getPoints();
    bool hasEle=t.hasEle;
    bool hasTime=t.hasTime;
    qDebug()<<hasEle<<hasTime;
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
