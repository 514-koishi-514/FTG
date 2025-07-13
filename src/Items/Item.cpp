//
// Item.cpp
// 游戏的（空）可见物基类实现
//

#include "Item.h"
#include <QGraphicsPixmapItem>

Item::Item(QGraphicsItem *parent, const QString &pixmapPath)
    : QGraphicsObject(parent) {
    if (!pixmapPath.isEmpty()) {
        pixmapItem = new QGraphicsPixmapItem(QPixmap(pixmapPath), this);
        pixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
    }

}
