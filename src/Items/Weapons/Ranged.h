#ifndef RANGED_H
#define RANGED_H

#include "Weapon.h"

class Ranged : public Weapon { // 相当于要求中的步枪
public:
    explicit Ranged(QGraphicsItem *parent = nullptr);
};

#endif // RANGED_H
