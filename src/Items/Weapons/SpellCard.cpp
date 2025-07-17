#include "SpellCard.h"

SpellCard::SpellCard(QGraphicsItem *parent) : Weapon(parent, ":/Items/Weapons/5.png") {
    weaponID = 5; // 设置符卡的ID
    ammoCapacity = 5; // 设置弹药容量
}
