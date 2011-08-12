#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QList>
#include "cpoint.h"
#include <trackparser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);/*
    KMLReader c;
    c.readFile("/home/anisart/GPS/doc.kml");
    GPXReader g;
    g.readFile("/home/anisart/GPS/Track201108050930.gpx");
    QList<CPoint> points=g.getPoints();
    foreach (CPoint point, points)
    {
        qDebug()<<"lat = "<<point.getLat()<<", lon = "<<point.getLon()<<", ele = "<<point.getEle()<<" "<<point.getTime().toString(Qt::DefaultLocaleLongDate);
    }*/

    TrackParser parser;
    bool hasEle = 0, hasTime = 0;
    QList<CPoint> points = parser.parse("/home/anisart/GPS/doc.kml",&hasEle,&hasTime);
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
