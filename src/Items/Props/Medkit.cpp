#include "Medkit.h"

Medkit::Medkit(QGraphicsItem *parent)
    : Props(parent, ":/Items/Props/Medkit.png") {
    cureOnce = 50; // 每次使用治疗50点生命值
    cureTimes = 1; // 使用次数为1次
}
