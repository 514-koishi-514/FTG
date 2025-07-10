//
// 头文件OldShirt.h
// 用来定义OldShirt类，之后可能会通过配置文件来修改思路
//

#ifndef OLDSHIRT_H
#define OLDSHIRT_H


#include "Armor.h"

class OldShirt: public Armor {
public:
    explicit OldShirt(QGraphicsItem *parent);
};


#endif //OLDSHIRT_H
