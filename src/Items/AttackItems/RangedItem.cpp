#include "RangedItem.h"
#include "../Maps/Bridge.h"

RangedItem::RangedItem(QGraphicsItem *parent, const QString &pixmapPath)
    : Item(parent, pixmapPath) {
    // 默认伤害值为0，可以在子类中设置具体的伤害值
}

void RangedItem::causeDamage(Character *target) {
    if (target) {
        if(target->getArmorType() == Heavy)
        {
            target->changeHp(-damage / 2); // 角色承担一半
            target->changeArmorHp(-damage / 2); // 重甲承担一半护甲伤害
            return;
        }
        else{
            target->changeHp(-damage);
            return;
        }
    }
}

QPointF RangedItem::getVelocity() const {
    return velocity;
}

void RangedItem::setVelocity(const QPointF &newVelocity) {
    velocity = newVelocity;
}

void RangedItem::changeVelocity() {
    // 默认不改变速度，子类可以重写此方法来实现特定的速度变化逻辑
}

void RangedItem::toDamageOrVanish() {
    // 判断是否碰到人物（造成伤害并消失），碰到桥（直接消失）
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    for (QGraphicsItem* item : std::as_const(collidingItems)) {
        if (Character* character = dynamic_cast<Character*>(item)) {
            qDebug() << "子弹碰到角色，造成伤害并调用delete";
            causeDamage(character);
            qDebug() << "子弹造成伤害，伤害值：" << damage << ", 角色名：" << character->getName() << ", 当前血量：" << character->getHp();
            isToRemove = true; // 设置为需要删除
            return;
        }
        if (Bridge* bridge = dynamic_cast<Bridge*>(item)) {
            // 如果碰到桥，直接消失
            qDebug() << "子弹碰到桥，调用delete";
            isToRemove = true; // 设置为需要删除
            return;
        }
    }

    // 判断是否碰到边界如地板、左右墙壁（直接消失）
    if (this->pos().y() >= 600 - this->boundingRect().height() || this->pos().x() <= 0 || this->pos().x() >= 1280 - this->boundingRect().width()) {
        qDebug() << "子弹超出边界，调用delete";
        isToRemove = true; // 设置为需要删除
        return;
    }
}
