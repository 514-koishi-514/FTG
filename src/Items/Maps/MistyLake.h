#ifndef MISTYLAKE_H
#define MISTYLAKE_H


#include "Map.h"

class MistyLake: public Map {
public:
    explicit MistyLake(QGraphicsItem *parent= nullptr);

    qreal getFloorHeight() override;
};


#endif // MISTYLAKE_H
