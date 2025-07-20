#ifndef RANGED_H
#define RANGED_H

#include "Weapon.h"
#include "../AttackItems/Charm.h"

class Ranged : public Weapon { // 相当于要求中的步枪
public:
    explicit Ranged(QGraphicsItem *parent = nullptr);

    int ammoCapacity = 0; // 弹药容量


};

#endif // RANGED_H
