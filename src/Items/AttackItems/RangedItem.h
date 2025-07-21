#ifndef RANGEDITEM_H
#define RANGEDITEM_H

#include "../Item.h"
#include "../Characters/Character.h"

class RangedItem : public Item {
    Q_OBJECT
public:
    explicit RangedItem(QGraphicsItem *parent, const QString &pixmapPath);

    QPointF getVelocity() const;

    void setVelocity(const QPointF &newVelocity);

    virtual void changeVelocity();

    void causeDamage(Character *target);

    void toDamageOrVanish(); // 判断是否碰到人物（造成伤害并消失），或者碰到边界如地板、左右墙壁、桥（消失）

    int fromCharacterID;

protected:
    int damage = 0; // 默认伤害值为0，可以在子类中设置具体的伤害值

    QPointF velocity = QPointF(0, 0); // 子弹的速度，默认值为0;

private:
    QPixmap pixmap; // 用于存储子弹的图片

signals:
    void requestRemoval(RangedItem* self);
};


#endif // RANGEDITEM_H
