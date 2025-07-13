#ifndef BRIDGE_H
#define BRIDGE_H

#include "Map.h"

class Bridge : public Map{
public:
    explicit Bridge(QGraphicsItem *parent = nullptr, const QString &pixmapPath = "");

    // 计算桥的高度
    qreal getFloorHeight() override;

    // 获取桥的生成位置
    QPointF getSpawnPos(const QRectF &itemBoundingRect) override;
};

#endif // BRIDGE_H
