#include "gpxreader.h"
#include <QDebug>
#include "cpoint.h"

GPXReader::GPXReader()
{
    is_point=false;
    is_segment=false;
    has_ele=false;
    is_ele=false;
    is_time=false;
    has_time=false;
}

bool GPXReader::readFile(const QString &fileName)
{
    QFile file(fileName);
    QXmlInputSource inputSource(&file);
    QXmlSimpleReader reader;
    reader.setContentHandler(this);
    reader.setErrorHandler(this);
    x1=0;y1=0;z1=0;
    return reader.parse(inputSource);
}

bool GPXReader::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName=="trkseg") is_segment=true;
    else if (qName=="trkpt")
    {
        is_point=true;
        bool ok;
        x1=atts.value("lat").toDouble(&ok);
        if (!ok||x1>90||x1<-90) return true;
        y1=atts.value("lon").toDouble(&ok);
        if (!ok||y1<-180||y1>180) return true;
    }
    else if (qName=="ele")
    {
        is_ele=true;
        has_ele=true;
    }
    else if (qName=="time")
    {
        is_time=true;
        has_time=true;
    }
    return true;
}

bool GPXReader::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    CPoint f;
    if (qName=="trkseg")
    {
    is_segment=false;
    }
    else if (qName=="trkpt")
    {
        if (has_time) f.setData(x1,y1,z1,date);
        else if (has_ele) f.setData(x1,y1,z1);
        else f.setData(x1,y1);
    points.insert(points.size(),f);
    is_point=false;
    }
    else if (qName=="ele") is_ele=false;
    else if (qName=="time") is_time=false;

    return true;
}

bool GPXReader::characters(const QString &ch)
{
    if (is_ele&&is_point&&is_segment)
    {
        bool ok;
        z1=ch.toDouble(&ok);
        if (!ok) return true;
    }
    if (is_time&&is_point&&is_segment)
    {
        date = QDateTime::fromString(ch,Qt::ISODate);
    }
    return true;
}

bool GPXReader::fatalError(const QXmlParseException &exception)
{
    qDebug()<<"error";
    return false;
}
