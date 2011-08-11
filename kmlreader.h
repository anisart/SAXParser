#ifndef KMLREADER_H
#define KMLREADER_H

#include <QXmlDefaultHandler>
#include <QList>
#include "cpoint.h"
class KMLReader : public QXmlDefaultHandler
{
public:
    KMLReader();
    bool readFile(const QString &fileName);
    bool has_ele;
    QList<CPoint> getPoints() {return points;}
protected:
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &ch);
    bool fatalError(const QXmlParseException &exception);

private:
    QList<CPoint> points;
    bool is_point;
    bool is_LineString;
};

#endif // KMLREADER_H
