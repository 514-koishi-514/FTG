#ifndef MARISA_H
#define MARISA_H

#include "Character.h"

class Marisa : public Character {
public:
    explicit Marisa(QGraphicsItem *parent, const QString& name = "Marisa");
};

#endif // MARISA_H
