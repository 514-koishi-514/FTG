#ifndef THROW_H
#define THROW_H

#include "Weapon.h"

class Throw : public Weapon { // 相当于要求中的实心球
public:
    explicit Throw(QGraphicsItem *parent = nullptr);
};

#endif // THROW_H
