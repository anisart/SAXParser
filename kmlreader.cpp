#include "kmlreader.h"
#include <QDebug>
#include <string>
#include <QVector>
#include "cpoint.h"
KMLReader::KMLReader()
{
    is_point=false;
    is_LineString=false;
    has_ele=false;
}

bool KMLReader::readFile(const QString &fileName)
{
    QFile file(fileName);
    QXmlInputSource inputSource(&file);
    QXmlSimpleReader reader;
    reader.setContentHandler(this);
    reader.setErrorHandler(this);
    return reader.parse(inputSource);
}

bool KMLReader::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName=="LineString") is_LineString=true;
    else
        if
            (qName=="coordinates") is_point=true;
        //else {is_point=false; is_LineString=false;}
    return true;
}

bool KMLReader::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (qName=="LineString") is_LineString=false;
    else
        if
            (qName=="coordinates") is_point=false;
    return true;
}

bool KMLReader::characters(const QString &ch)
{
    if (is_point&&is_LineString)
    {
//        qDebug()<<"point";
        QStringList list1, list2;
        list1 = ch.split(QRegExp("[ ]"), QString::SkipEmptyParts);
//        qDebug()<<list1;
        QStringListIterator iterator1(list1);
        while (iterator1.hasNext())
        {
            CPoint f;
            list2 = iterator1.next().split(QRegExp("[,]"), QString::SkipEmptyParts);
//            qDebug()<<list2;
            QStringListIterator iterator2(list2);
            double y = iterator2.next().toDouble(), x = iterator2.next().toDouble();
            if (iterator2.hasNext())
            {
                double z = iterator2.next().toDouble();
                f.setData(x,y,z);
                has_ele=true;
            }
            else
            {
                f.setData(x,y);
                if (has_ele==true) has_ele=false;
            }
            points.insert(points.size(),f);
//            qDebug()<<has_ele;
        }
    }
    return true;
}

bool KMLReader::fatalError(const QXmlParseException &exception)
{
    qDebug()<<"error";
    return false;
}
