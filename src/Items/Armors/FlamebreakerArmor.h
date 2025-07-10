//
// 头文件FlamebreakerArmor.h
// 具体的护甲类FlamebreakerArmor，之后可能会通过配置文件来修改思路
//

#ifndef FLAMEBREAKERARMOR_H
#define FLAMEBREAKERARMOR_H


#include "Armor.h"

class FlamebreakerArmor : public Armor {
public:
    explicit FlamebreakerArmor(QGraphicsItem *parent = nullptr);
};


#endif //FLAMEBREAKERARMOR_H
