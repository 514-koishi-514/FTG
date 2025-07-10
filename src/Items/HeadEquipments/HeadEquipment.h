//
// 头文件HeadEquipment.h
// 用于实现头装备类的基类HeadEquipment
//

#ifndef HEADEQUIPMENT_H
#define HEADEQUIPMENT_H


#include "../Item.h"
#include "../Mountable.h"

class HeadEquipment: public Item, public Mountable {
public:
    explicit HeadEquipment(QGraphicsItem *parent, const QString &pixmapPath);

    void mountToParent() override;
};


#endif //HEADEQUIPMENT_H
