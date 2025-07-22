#ifndef ENHANCEDMELEE_H
#define ENHANCEDMELEE_H

#include "Weapon.h"

class EnhancedMelee : public Weapon { // 相当于要求中的小刀
public:
    explicit EnhancedMelee(QGraphicsItem *parent = nullptr);
};

#endif // ENHANCEDMELEE_H
