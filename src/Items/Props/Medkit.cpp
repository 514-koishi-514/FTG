#include "Medkit.h"

Medkit::Medkit(QGraphicsItem *parent)
    : Props(parent, ":/Items/Props/Medkit.png") {
    cureOnce = 100; // 每次使用回复满（100不会超额回复）
    cureTimes = 1; // 使用次数为1次
}
