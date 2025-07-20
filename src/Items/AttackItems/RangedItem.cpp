#include "RangedItem.h"
#include "../Maps/Bridge.h"

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

QPointF RangedItem::getVelocity() const {
    return velocity;
}

void RangedItem::toDamageOrVanish() {
    // 判断是否碰到人物（造成伤害并消失），碰到桥（直接消失）
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    for (QGraphicsItem* item : collidingItems) {
        if (Character* character = dynamic_cast<Character*>(item)) {
            causeDamage(character);
            this->deleteLater();
            return;
        }
        if (Bridge* bridge = dynamic_cast<Bridge*>(item)) {
            // 如果碰到桥，直接消失
            this->deleteLater();
            return;
        }
    }

    // 判断是否碰到边界如地板、左右墙壁（直接消失）
    if (this->pos().y() >= 600 - this->boundingRect().height() || this->pos().x() <= 0 || this->pos().x() >= 1280 - this->boundingRect().width()) {
        this->deleteLater();
        return;
    }
}
