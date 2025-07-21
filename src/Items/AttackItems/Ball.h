#ifndef BALL_H
#define BALL_H

#include "RangedItem.h"

class Ball : public RangedItem {
public:
    explicit Ball(QGraphicsItem *parent = nullptr, const QString &pixmapPath = ":/AttackItems/Items/AttackItems/Reimu/3.png"); // 默认为灵梦

    void changeVelocity() override;
};

#endif // BALL_H
