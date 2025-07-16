#ifndef MELEE_H
#define MELEE_H

#include "Weapon.h"

class Melee : public Weapon { // 相当于要求中的拳头
public:
    explicit Melee(QGraphicsItem *parent = nullptr);
};

#endif // MELEE_H
