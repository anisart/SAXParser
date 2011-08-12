#include "trackparser.h"
#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include "kmlreader.h"
#include "gpxreader.h"

TrackParser::TrackParser()
{
}

QList<CPoint> TrackParser::parse(const QString &fileName, bool *hasEle, bool *hasTime)
{
     QDomDocument doc("mydocument");
     QFile file(fileName);
     if (!file.open(QIODevice::ReadOnly))
         return points;
     if (!doc.setContent(&file)) {
         file.close();
         return points;
     }
     file.close();

     QDomElement docElem = doc.documentElement();
     if (docElem.tagName()=="kml")
     {
         KMLReader reader;
         reader.readFile(fileName);
         points = reader.getPoints();
         hasEle = &reader.has_ele;
     }
     else if (docElem.tagName()=="gpx")
     {
         GPXReader reader;
         reader.readFile(fileName);
         points = reader.getPoints();
         hasEle = &reader.has_ele;
         hasTime = &reader.has_time;
     }
     else return points; /////////////

     return points;
}
