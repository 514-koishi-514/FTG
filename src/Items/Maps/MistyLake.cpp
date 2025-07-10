#include "MistyLake.h"

MistyLake::MistyLake(QGraphicsItem *parent) : Map(parent, ":/Maps/Items/Maps/MistyLake/background/mistyLake.png") {}

// 重写getFloorHeight方法以适应多种高度
qreal MistyLake::getFloorHeight() {
    auto sceneRect = sceneBoundingRect();
    return (sceneRect.top() + sceneRect.bottom()) * 0.63;
}
