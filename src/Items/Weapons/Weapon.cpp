#include "Weapon.h"

Weapon::Weapon(QGraphicsItem *parent, const QString &pixmapPath)
    : Item(parent, pixmapPath) {
}

void Weapon::mountToParent() {
    Mountable::mountToParent();
    if (parentItem() != nullptr) {
        setPos(0, 48);
    }
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Weapon::unmount() {
    Mountable::unmount();
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0); // TODO:后续需要确定位置
    }
}
