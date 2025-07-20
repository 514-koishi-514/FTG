#include "EnhancedCharm.h"

EnhancedCharm::EnhancedCharm(QGraphicsItem *parent)
    : RangedItem(parent, ":/images/enhanced_charm.png") {
    damage = 30;
    velocity = QPointF(2.0, 0);
}

