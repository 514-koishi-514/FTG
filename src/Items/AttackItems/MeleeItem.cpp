#include "MeleeItem.h"

MeleeItem::MeleeItem(QGraphicsItem *parent, const QString &pixmapPath)
    : Item(parent, pixmapPath) {
    // 默认伤害值为0，可以在子类中设置具体的伤害值
}

void MeleeItem::causeDamage(Character *target) {
    if (target) {
        target->changeHp(-damage);
        return;
    }
}
