#include "Adrenaline.h"

Adrenaline::Adrenaline(QGraphicsItem *parent)
    : Props(parent, ":/Items/Props/Adrenaline.png") {
    cureOnce = 2; // 每次使用治疗30点生命值
    cureTimes = 15; // 使用次数为15次
    isLastingEffect = true; // 有持续效果
}
