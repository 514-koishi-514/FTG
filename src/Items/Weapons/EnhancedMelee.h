#ifndef ENHANCEDMELEE_H
#define ENHANCEDMELEE_H

#include "Weapon.h"
#include "../AttackItems/Stick.h"

class EnhancedMelee : public Weapon { // 相当于要求中的小刀
public:
    explicit EnhancedMelee(QGraphicsItem *parent = nullptr);

    Stick stick; // 使用Stick类作为增强近战武器的攻击方式
};

#endif // ENHANCEDMELEE_H
