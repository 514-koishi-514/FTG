#include "Throw.h"

Throw::Throw(QGraphicsItem *parent) : Weapon(parent, ":Weapons/Items/Weapons/3.png") {
    weaponID = 3; // 设置投掷武器的IDS
    ammoCapacity = 3; // 设置弹药容量
}
