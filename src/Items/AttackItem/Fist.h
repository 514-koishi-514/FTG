#ifndef FIST_H
#define FIST_H

#include "MeleeItem.h"

class Fist : public MeleeItem {
public:
    explicit Fist(QGraphicsItem *parent, const QString &pixmapPath);
};

#endif // FIST_H
