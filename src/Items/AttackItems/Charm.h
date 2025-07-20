#ifndef CHARM_H
#define CHARM_H

#include "RangedItem.h"

class Charm : public RangedItem {
public:
    explicit Charm(QGraphicsItem *parent = nullptr, const QString &pixmapPath = ":/AttackItems/Items/AttackItems/Reimu/4.png"); // 默认为灵梦
};

#endif // CHARM_H
