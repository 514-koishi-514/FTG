#include "EnhancedMelee.h"

EnhancedMelee::EnhancedMelee(QGraphicsItem *parent) : Weapon(parent, ":/Items/Weapons/EnhancedMelee.png") {
    weaponID = 2; // 设置增强近战武器的ID
    damage = 5; // 设置增强近战武器的伤害值
}
