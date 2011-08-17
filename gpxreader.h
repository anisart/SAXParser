#ifndef GPXREADER_H
#define GPXREADER_H

#include <QXmlDefaultHandler>
#include "cpoint.h"

class GPXReader : public QXmlDefaultHandler
{
public:
    GPXReader();
    bool readFile(const QString &fileName);
    bool has_ele;
    bool has_time;
    QList<CPoint> getPoints() {return points;}
protected:
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &ch);
    bool fatalError(const QXmlParseException &exception);
private:
    QList<CPoint> points;
    bool is_point;
    bool is_segment;
    bool is_ele;
    bool is_time;
    double x1,y1,z1;
    QDateTime date;
};

#endif // GPXREADER_H
