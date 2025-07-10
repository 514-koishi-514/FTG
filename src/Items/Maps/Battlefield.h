//
// 头文件 Battlefield.h
// 战场类，用来表示具体的战场地图
//

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H


#include "Map.h"

class Battlefield: public Map {
public:
    explicit Battlefield(QGraphicsItem *parent= nullptr);

    qreal getFloorHeight() override;
};


#endif //BATTLEFIELD_H
