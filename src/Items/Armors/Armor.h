//
// 头文件Armor.h
// 护甲类
//

#ifndef ARMOR_H
#define ARMOR_H

#include "../Item.h"
#include "../Mountable.h"

enum ArmorType {
    Default,
    Light,
    Heavy
};

class Armor : public Item, public Mountable {
public:
    explicit Armor(QGraphicsItem *parent, const QString &pixmapPath);

    void mountToParent() override;

    void unmount() override;

    int armorValue = 0;

    int maxArmorValue = 0;

    ArmorType armorType = Default;

    void changeArmorValue(int delta);
};


#endif //ARMOR_H
