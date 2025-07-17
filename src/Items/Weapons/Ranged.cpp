#include "Ranged.h"

Ranged::Ranged(QGraphicsItem *parent) : Weapon(parent, ":Weapons/Items/Weapons/4.png") {
    weaponID = 4; // 设置远程武器的ID
    damage = 8; // 设置远程武器的伤害值
    ammoCapacity = 25; // 设置弹药容量
}
