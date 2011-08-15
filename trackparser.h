#ifndef TRACKPARSER_H
#define TRACKPARSER_H

#include <QList>
#include "cpoint.h"
#include "track.h"

class TrackParser
{
    Track track;
    enum trackType {KML, GPX, OTHER};
    trackType idTrack(const QString &fileName);
public:
    TrackParser();
    Track parse(const QString &fileName);
};

#endif // TRACKPARSER_H
