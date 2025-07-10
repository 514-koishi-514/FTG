//
// LegEquipment.cpp
// 用于实现腿部装备类LegEquipment
//

#include "LegEquipment.h"

LegEquipment::LegEquipment(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {
}

void LegEquipment::mountToParent() {
    Mountable::mountToParent();
    setScale(0.8);
    setPos(-60, -110);
}
