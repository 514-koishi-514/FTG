#include "Ranged.h"

Ranged::Ranged(QGraphicsItem *parent) : Weapon(parent, ":Weapons/Items/Weapons/4.png") {
    weaponID = 4; // 设置远程武器的ID
    ammoCapacity = 25; // 设置弹药容量
    maxAmmoCapacity = 25; // 设置最大弹药数
}
