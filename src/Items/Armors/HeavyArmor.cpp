#include "HeavyArmor.h"

HeavyArmor::HeavyArmor(QGraphicsItem *parent) : Armor(parent,
                                                       ":/Items/Armors/HeavyArmor/HeavyArmor.png") {
    // 重型护甲的构造函数
    armorValue = 50; // 设置重型护甲值
    maxArmorValue = 50; // 设置重型护甲的最大值
    armorType = Heavy; // 设置护甲类型为重型护甲
}
