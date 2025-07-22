#include "Bandage.h"

Bandage::Bandage(QGraphicsItem *parent)
    : Props(parent, ":/Items/Props/Bandage.png") {
    cureOnce = 20; // 每次使用治疗20点生命值
    cureTimes = 1; // 使用次数为1次
}
