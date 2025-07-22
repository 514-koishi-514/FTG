//
// 头文件 BattleScene.h
// 战斗场景类，具体的战斗场景
//

#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include <QKeyEvent>
#include <QPointer>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/Maps/Bridge.h"
#include "../Items/Maps/HighGrass.h"
#include "../Items/AttackItems/RangedItem.h"
#include "../Items/SystemWidgets/HpBar.h"
#include "../Items/SystemWidgets/ArmorBar.h"
#include "../Items/SystemWidgets/AmmoBar.h"

class BattleScene : public Scene {
    Q_OBJECT

public:
    explicit BattleScene(QObject *parent);

    void processInput() override;

    // 处理移动逻辑
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

    HpBar *hpBar_1p;
    HpBar *hpBar_2p;

    ArmorBar *armorBar_1p;
    ArmorBar *armorBar_2p;

    AmmoBar *ammoBar_1p;
    AmmoBar *ammoBar_2p;

    QVector<RangedItem *> bullets;

    bool gameOver = false;
    QString winnerName;
    QGraphicsProxyWidget* winnerLabelProxy = nullptr;
    QGraphicsProxyWidget* restartButtonProxy = nullptr;
    QLabel* winnerLabel = nullptr;
    QPushButton* restartButton = nullptr;
    QList<QTimer*> allTimers; // 用于保存所有需要停止的timer指针

    QTimer* dropTimer = nullptr;
    QVector<Item*> floatingMountables; // 当前场景中所有自由掉落装备
    QVector<Item*> onGroundMountables; // 当前场景中所有已放置装备
    void spawnRandomDrop();

    void showGameOverScreen();
    void restartGame();
    void stopAllTimers(); // 停止所有游戏相关timer


private slots:
    void onBulletFired(Weapon* weapon, const QPointF& firePos, bool isRight, const QString &fromCharacterName = QString(), const int &fromPlayerID = 1);
};


#endif //BATTLESCENE_H
