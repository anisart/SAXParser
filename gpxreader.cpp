#include "gpxreader.h"
#include <QDebug>
#include <string>
#include <QVector>
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
//        qDebug()<<"lat = "<<atts.value("lat")<<", lon = "<<atts.value("lon");
        x1=atts.value("lat").toDouble();
        y1=atts.value("lon").toDouble();
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
        z1=ch.toDouble();
    }

    if (is_time&&is_point&&is_segment)
    {
        date = QDateTime::fromString(ch,Qt::ISODate);
//        qDebug()<<date.toString(Qt::DefaultLocaleLongDate);
    }

    return true;
}

bool GPXReader::fatalError(const QXmlParseException &exception)
{
    qDebug()<<"error";
    return false;
}
