#include "SpellCard.h"

SpellCard::SpellCard(QGraphicsItem *parent) : Weapon(parent, ":/Items/Weapons/SpellCard.png") {
    weaponID = 5; // 设置符卡的ID
    damage = 18; // 设置符卡的伤害值
    ammoCapacity = 5; // 设置弹药容量
}
