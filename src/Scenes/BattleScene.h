//
// 头文件 BattleScene.h
// 战斗场景类，具体的战斗场景
//

#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include <QKeyEvent>
#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/Maps/Bridge.h"
#include "../Items/Maps/HighGrass.h"

class BattleScene : public Scene {
    Q_OBJECT

public:
    explicit BattleScene(QObject *parent);

    void processInput() override;

    void processMovement() override;

    void processPicking() override;

    void processCollision() override;

protected slots:

    void update() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

private:

    Mountable *findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());

    static Mountable * pickupMountable(Character *character, Mountable *mountable);

    Map *map;
    Character *character_1p;
    Character *character_2p;
    Armor *spareArmor;
    Weapon *spareWeapon;
    Bridge *bridge;
    HighGrass *highGrassLeft;
    HighGrass *highGrassRight;
};


#endif //BATTLESCENE_H
