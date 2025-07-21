#ifndef SPELLCARD_H
#define SPELLCARD_H

#include "Weapon.h"

class SpellCard : public Weapon { // 相当于要求中的狙击枪
public:
    explicit SpellCard(QGraphicsItem *parent = nullptr);
};

#endif // SPELLCARD_H
