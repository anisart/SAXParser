#include "trackparser.h"
#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include "kmlreader.h"
#include "gpxreader.h"

TrackParser::TrackParser(){}

TrackParser::trackType TrackParser::idTrack(const QString &fileName)
{
    QDomDocument doc("mydocument");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return OTHER;
    if (!doc.setContent(&file))
    {
        file.close();
        return OTHER;
    }
    file.close();
    QDomElement docElem = doc.documentElement();
    if (docElem.tagName()=="kml")
    {
        QString title = docElem.firstChild().firstChild().toElement().text();
        track.title=title;
        return KML;
    }
    else if (docElem.tagName()=="gpx")
    {
        QDomNode domNode = docElem.firstChild().nextSibling().firstChild();
        while (!domNode.isNull())
        {
            if (domNode.toElement().tagName()=="name")
                track.title=domNode.toElement().text();
            domNode=domNode.nextSibling();
        }
        return GPX;
    }
    else return OTHER;
}

Track TrackParser::parse(const QString &fileName)
{
    TrackParser::trackType type = idTrack(fileName);
    if (type==OTHER) return track;
    else if (type==KML)
    {
        qDebug()<<"kml";
        KMLReader reader;
        reader.readFile(fileName);
        track.setPoints(reader.getPoints());
        track.hasEle = reader.has_ele;
        track.isValid = true;
        return track;
    }
    else if (type==GPX)
    {
        qDebug()<<"gpx";
        GPXReader reader;
        reader.readFile(fileName);
        track.setPoints(reader.getPoints());
        track.hasEle = reader.has_ele;
        track.hasTime = reader.has_time;
        track.isValid = true;
        return track;
    }
}
