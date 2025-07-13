#ifndef HIGHGRASS_H
#define HIGHGRASS_H

#include "Map.h"

class HighGrass : public Map {
public:
    explicit HighGrass(QGraphicsItem *parent = nullptr, const QString &pixmapPath = "");
};

#endif // HIGHGRASS_H
