//
// 头文件CapOfTheHero.cpp
// 这些我后续会改为使用配置文件来读取装备信息，而不是硬编码，腿部同理
//

#ifndef CAPOFTHEHERO_H
#define CAPOFTHEHERO_H


#include "HeadEquipment.h"

class CapOfTheHero: public HeadEquipment {
public:
    explicit CapOfTheHero(QGraphicsItem *parent);
};


#endif //CAPOFTHEHERO_H
