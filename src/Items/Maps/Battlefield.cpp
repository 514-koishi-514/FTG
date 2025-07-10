//
// Battlefield.cpp
// 实现战场地图的具体属性和行为
//

#include "Battlefield.h"

Battlefield::Battlefield(QGraphicsItem *parent) : Map(parent, ":/Maps/Items/Maps/MistyLake/background/mistyLake.png") {}

// 重写getFloorHeight方法以适应多种高度
qreal Battlefield::getFloorHeight() {
    auto sceneRect = sceneBoundingRect();
    return (sceneRect.top() + sceneRect.bottom()) * 0.63;
}
