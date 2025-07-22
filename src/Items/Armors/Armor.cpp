//
// Armor.cpp
// 用于实现护甲类
//

#include "Armor.h"

Armor::Armor(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {

}

void Armor::mountToParent() {
    Mountable::mountToParent();
    setScale(0.8);
    setZValue(-5); // 设置Z值
    setPos(0, 0);// TODO:这里的坐标位置死板，应该根据父节点的大小来动态计算
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Armor::unmount() {
    Mountable::unmount();
    setScale(0.8);
    setZValue(-5); // 设置Z值
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

int Armor::getArmorValue() const {
    return armorValue;
}
