#include "Weapon.h"

Weapon::Weapon(QGraphicsItem *parent, const QString &pixmapPath, int weaponID)
    : Item(parent, pixmapPath), weaponID(weaponID) {
}

void Weapon::mountToParent() {
    Mountable::mountToParent();
    setScale(0.8);
    setPos(-59, -176); // TODO:这里的坐标位置死板，应该根据父节点的大小来动态计算
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Weapon::unmount() {
    Mountable::unmount();
    setScale(0.8);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, -120);
    }
}
