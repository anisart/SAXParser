#ifndef TRACK_H
#define TRACK_H

#include <QMap>
#include "cpoint.h"

struct Track
{
private:
    QMap<qint32,CPoint> points;
    QList<qint32> listIds;
public:
    bool hasEle,hasTime,isValid;
    QString title;
    QList<qint32> getListIds() { return listIds; }
    CPoint getPoint(qint32 id) { return points.value(id); }
    Track() { isValid = false; hasEle = false; hasTime = false; }
    qint32 insertPoint(qint32 id,CPoint point)
    {
        qint32 i = 0;
        if (!listIds.isEmpty()) i = points.keys().last()+1;
        points.insert(i,point);
        listIds.insert(listIds.indexOf(id),i);
        return i;
    }

    bool deletePoint(qint32 id)
    {
        if (points.remove(id))
        {
            listIds.removeOne(id);
            return true;
        }
        else return false;
    }

    void setPoints(QList<CPoint> list)
    {
        points.clear();
        for (qint32 i=0; i<list.size(); i++)
        {
            points.insert(i,list.at(i));
            listIds.insert(i,i);
        }
    }
};

#endif // TRACK_H
