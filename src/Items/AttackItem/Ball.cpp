#include "Ball.h"

Ball::Ball(QGraphicsItem *parent)
    : RangedItem(parent, ":/images/ball.png") {
    damage = 12;
    velocity = QPointF(1.0, 0);
}

void Ball::changeVelocity() {
    velocity.setY(velocity.y()+0.03); // 模拟重力
}
