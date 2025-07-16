#ifndef SPELLCARD_H
#define SPELLCARD_H

#include "Weapon.h"

class SpellCard : public Weapon { // 相当于要求中的狙击枪
public:
    explicit SpellCard(QGraphicsItem *parent = nullptr);

    int ammoCapacity = 0; // 弹药容量
};

#endif // SPELLCARD_H
