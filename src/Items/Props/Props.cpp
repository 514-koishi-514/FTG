#include "Props.h"

Props::Props(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {
    cureOnce = 0;
    cureTimes = 0;
}
