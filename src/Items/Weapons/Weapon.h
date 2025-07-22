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

    int ammoCapacity = 0; // 弹药容量

    int maxAmmoCapacity = 0; // 最大弹药数

    int damage = 0; // 武器伤害值
};

#endif // WEAPON_H
