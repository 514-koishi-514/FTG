#include "Melee.h"

Melee::Melee(QGraphicsItem *parent) : Weapon(parent, ":Weapons/Items/Weapons/1.png") {
    weaponID = 1;
    damage = 2; // 设置近战武器的伤害值
}
