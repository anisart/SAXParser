#ifndef CPOINT_H
#define CPOINT_H

#include <QDateTime>

class CPoint
{
    double lat, lon, ele;
    QDateTime time;
public:
    CPoint() {}
    void setData(const double &x=0, const double &y=0, const double &z=0, const QDateTime &d=QDateTime::currentDateTime())
    {
        lat=x; lon=y; ele=z; time=d;
    }

    double getLat(){return lat;}
    double getLon(){return lon;}
    double getEle(){return ele;}
    QDateTime getTime(){return time;}
};

#endif // CPOINT_H
