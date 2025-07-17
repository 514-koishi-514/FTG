#include "Throw.h"

Throw::Throw(QGraphicsItem *parent) : Weapon(parent, ":Weapons/Items/Weapons/3.png") {
    weaponID = 3; // 设置投掷武器的ID
    damage = 15; // 设置投掷武器的伤害值
    ammoCapacity = 3; // 设置弹药容量
    throwSpeed = 15; // 设置投掷速度
}
