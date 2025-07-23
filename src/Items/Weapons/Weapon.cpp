#include "Weapon.h"

Weapon::Weapon(QGraphicsItem *parent, const QString &pixmapPath)
    : Item(parent, pixmapPath) {
    setZValue(1);
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
        pixmapItem->setPos(0, 0);
    }
}
