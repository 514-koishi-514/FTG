#include "HeavyArmor.h"

HeavyArmor::HeavyArmor(QGraphicsItem *parent) : Armor(parent,
                                                       ":/Items/Armors/HeavyArmor/HeavyArmor.png") {
    // 重型护甲的构造函数
    armorValue = 100; // 设置重型护甲值
    maxArmorValue = 100; // 设置重型护甲的最大值
}
