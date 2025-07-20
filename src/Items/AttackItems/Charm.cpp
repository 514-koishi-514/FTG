#include "Charm.h"

Charm::Charm(QGraphicsItem *parent, const QString &pixmapPath) : RangedItem(parent, pixmapPath) {
    damage = 10;
    velocity = QPointF(1.6, 0);
}
