#ifndef REIMU_H
#define REIMU_H

#include "Character.h"

class Reimu : public Character {
public:
    explicit Reimu(QGraphicsItem *parent, const QString& name = "Reimu");
};

#endif // REIMU_H
