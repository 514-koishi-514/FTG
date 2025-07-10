//
// 头文件LegEquipment.h
// 用于定义腿部装备基类LegEquipment
//

#ifndef LEGEQUIPMENT_H
#define LEGEQUIPMENT_H


#include "../Item.h"
#include "../Mountable.h"

class LegEquipment: public Item, public Mountable {
public:
    explicit LegEquipment(QGraphicsItem *parent, const QString &pixmapPath);

    void mountToParent() override;
};


#endif //LEGEQUIPMENT_H
