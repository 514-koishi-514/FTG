#include "Weapon.h"

Weapon::Weapon(QGraphicsItem *parent, const QString &pixmapPath, int weaponID)
    : Item(parent, pixmapPath), weaponID(weaponID) {
}

void Weapon::mountToParent() {
    Mountable::mountToParent();
    setPos(-59, -176);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Weapon::unmount() {
    Mountable::unmount();
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, -120);
    }
}
