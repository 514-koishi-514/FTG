#ifndef MELEEITEM_H
#define MELEEITEM_H

#include "../Item.h"
#include "../Characters/Character.h"

class MeleeItem : public Item{
public:
    explicit MeleeItem(QGraphicsItem *parent, const QString &pixmapPath);

    void causeDamage(Character *target);

    int damage = 0;

    Item* collisionWith();
};

#endif // MELEEITEM_H
