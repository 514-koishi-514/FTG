#include "LightArmor.h"

LightArmor::LightArmor(QGraphicsItem *parent) : Armor(parent,
                                                       ":/Items/Armors/LightArmor/LightArmor.png") {
    armorValue = 0; // 设置轻型护甲值
    maxArmorValue = 0; // 设置轻型护甲的最大值
    armorType = Light; // 设置护甲类型为轻型护甲
}
