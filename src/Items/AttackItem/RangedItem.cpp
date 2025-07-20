#include "RangedItem.h"

RangedItem::RangedItem(QGraphicsItem *parent, const QString &pixmapPath)
    : Item(parent, pixmapPath) {
    // 默认伤害值为0，可以在子类中设置具体的伤害值
}

void RangedItem::causeDamage(Character *target) {
    if (target) {
        target->changeHp(-damage);
        return;
    }
}

Item* RangedItem::collisionWith() {
    QList<QGraphicsItem *> collidingItems = this->collidingItems();
    for (QGraphicsItem *item : collidingItems) {
        if (Character *character = dynamic_cast<Character *>(item)) {
            return character;
        }
    }
    return nullptr; // 如果没有碰撞到任何角色，返回nullptr
}
