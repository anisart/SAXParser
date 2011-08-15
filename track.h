#ifndef TRACK_H
#define TRACK_H

#include <QList>
#include "cpoint.h"

class Track
{
private:
    QList<CPoint> points;
    QString title;
public:
    Track(){isValid = false; hasEle = false; hasTime = false;}
    QList<CPoint> getPoints(){return points;}
    QString getTitle(){return title;}
    bool hasEle,hasTime,isValid;
    void setPoints(QList<CPoint> a){points=a;}
    void setTitle(QString b){title=b;}
};

#endif // TRACK_H
