#include "EnhancedMelee.h"

EnhancedMelee::EnhancedMelee(QGraphicsItem *parent) : Weapon(parent, ":Weapons/Items/Weapons/2.png") {
    weaponID = 2; // 设置增强近战武器的ID
    damage = 8; // 设置增强近战武器的默认伤害值
}
