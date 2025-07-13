#include "MistyLake.h"

MistyLake::MistyLake(QGraphicsItem *parent) : Map(parent, ":/Maps/Items/Maps/MistyLake/background/mistyLake.png") {}

// 重写getFloorHeight方法以适应多种高度
qreal MistyLake::getFloorHeight() {
    return 600.0;
}

// 获取生成位置,TODO:Player 2
QPointF MistyLake::getSpawnPos(const QRectF &itemBoundingRect) {
    return QPointF(472,600);
}
