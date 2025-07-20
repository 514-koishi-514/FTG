#include "Ball.h"

Ball::Ball(QGraphicsItem *parent, const QString &pixmapPath)
    : RangedItem(parent, pixmapPath) {
    damage = 16;
    velocity = QPointF(1.0, 0);
}

void Ball::changeVelocity() {
    velocity.setY(velocity.y() + 0.03); // 模拟重力
}
