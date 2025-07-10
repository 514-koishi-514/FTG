//
// 头文件Armor.h
// 护甲类
//

#ifndef ARMOR_H
#define ARMOR_H

#include "../Item.h"
#include "../Mountable.h"

class Armor : public Item, public Mountable {
public:
    explicit Armor(QGraphicsItem *parent, const QString &pixmapPath);

    void mountToParent() override;

    void unmount() override;
};


#endif //ARMOR_H
