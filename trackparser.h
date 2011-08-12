#ifndef TRACKPARSER_H
#define TRACKPARSER_H

#include <QList>
#include "cpoint.h"

class TrackParser
{
    QList<CPoint> points;
public:
    TrackParser();
    QList<CPoint> parse(const QString &fileName, bool *hasEle = 0, bool *hasTime = 0);
//    QList<CPoint> getPoints() {return points;}
};

#endif // TRACKPARSER_H
