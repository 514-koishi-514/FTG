#include "DefaultArmor.h"

DefaultArmor::DefaultArmor(QGraphicsItem *parent) : Armor(parent,
                                                           ":/Items/Armors/DefaultArmor/DefaultArmor.png") {
    // 默认护甲的构造函数
    armorValue = 0; // 设置默认护甲值
    maxArmorValue = 0; // 设置最大护甲值
    armorType = DefaultArmor; // 设置护甲类型为默认护甲
}
