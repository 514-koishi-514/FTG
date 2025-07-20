#ifndef BALL_H
#define BALL_H

#include "RangedItem.h"

class Ball : public RangedItem {
public:
    explicit Ball(QGraphicsItem *parent = nullptr);

    void changeVelocity();
};

#endif // BALL_H
