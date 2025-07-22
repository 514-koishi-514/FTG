#include "Melee.h"

Melee::Melee(QGraphicsItem *parent) : Weapon(parent, ":Weapons/Items/Weapons/1.png") {
    weaponID = 1;
    damage = 5; // 设置近战武器的默认伤害值
}
