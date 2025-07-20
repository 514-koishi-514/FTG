#include "EnhancedCharm.h"

EnhancedCharm::EnhancedCharm(QGraphicsItem *parent, const QString &pixmapPath)
    : RangedItem(parent, pixmapPath) {
    damage = 18;
    velocity = QPointF(2.0, 0);
}

