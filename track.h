#ifndef TRACK_H
#define TRACK_H

#include <QList>
#include "cpoint.h"

struct Track
{
public:
    bool hasEle,hasTime,isValid;
    QList<CPoint> points;
    QString title;
    Track(){isValid = false; hasEle = false; hasTime = false;}
};

#endif // TRACK_H
