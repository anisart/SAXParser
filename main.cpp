#include <QtCore/QCoreApplication>
#include "kmlreader.h"
#include "gpxreader.h"
#include <QDebug>
#include <QFile>
#include <QList>
#include "cpoint.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    KMLReader c;
    c.readFile("/home/anisart/GPS/doc.kml");
    GPXReader g;
    g.readFile("/home/anisart/GPS/Track201108050930.gpx");
    QList<CPoint> points=g.getPoints();
    foreach (CPoint point, points)
    {
        qDebug()<<"lat = "<<point.getLat()<<", lon = "<<point.getLon()<<", ele = "<<point.getEle()<<" "<<point.getTime().toString(Qt::DefaultLocaleLongDate);
    }
    return a.exec();
}
