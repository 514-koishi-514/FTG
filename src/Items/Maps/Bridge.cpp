#include "Bridge.h"

Bridge::Bridge(QGraphicsItem *parent, const QString &pixmapPath)
    : Map(parent, ":Maps/Items/Maps/MistyLake/terrain/bridge.png") {}

qreal Bridge::getFloorHeight() {
    return 280;
}

QPointF Bridge::getSpawnPos(const QRectF &itemBoundingRect) {
    // 计算生成位置，假设桥的中心为生成点
    qreal x = itemBoundingRect.center().x();
    qreal y = itemBoundingRect.top() - getFloorHeight();
    return QPointF(x, y);
}
