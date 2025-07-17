#ifndef WEAPON_H
#define WEAPON_H

#include "../Item.h"
#include "../Mountable.h"

class Weapon : public Item, public Mountable{
public:
    explicit Weapon(QGraphicsItem *parent, const QString &pixmapPath);

    void mountToParent() override;

    void unmount() override;

    int weaponID = 0; // 武器ID
};

#endif // WEAPON_H
