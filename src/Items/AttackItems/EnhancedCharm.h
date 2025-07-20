#ifndef ENHANCEDCHARM_H
#define ENHANCEDCHARM_H

#include "RangedItem.h"

class EnhancedCharm : public RangedItem {
public:
    explicit EnhancedCharm(QGraphicsItem *parent = nullptr, const QString &pixmapPath = ":/AttackItems/Items/AttackItems/Reimu/5.png"); // 默认为灵梦
};

#endif // ENHANCEDCHARM_H
