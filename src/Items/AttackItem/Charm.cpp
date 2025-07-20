#include "Charm.h"

Charm::Charm(QGraphicsItem *parent)
    : RangedItem(parent, ":/images/charm.png") {
    damage = 20;
    velocity = QPointF(1.6, 0);
}
