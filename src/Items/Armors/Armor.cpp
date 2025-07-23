//
// Armor.cpp
// 用于实现护甲类
//

#include "Armor.h"

Armor::Armor(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {
    setScale(0.8);
}

void Armor::mountToParent() {
    Mountable::mountToParent();
    setZValue(-5); // 设置Z值
    setPos(0, 0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Armor::unmount() {
    Mountable::unmount();
    setZValue(-5); // 设置Z值
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Armor::changeArmorValue(int delta) {
    armorValue += delta;
    if (armorValue < 0) {
        armorValue = 0;
    }
}

