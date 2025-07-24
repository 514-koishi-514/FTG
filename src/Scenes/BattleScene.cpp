//
// BattleScene.cpp
// 实现战斗场景的输入处理、角色动作、拾取等功能
//

#include <QDebug>
#include "BattleScene.h"
#include "../Items/Maps/MistyLake.h"
#include "../Items/Armors/LightArmor.h"
#include "../Items/Armors/HeavyArmor.h"
#include "../Items/Weapons/EnhancedMelee.h"
#include "../Items/Weapons/Throw.h"
#include "../Items/Weapons/Ranged.h"
#include "../Items/Weapons/SpellCard.h"
#include "../Items/AttackItems/Ball.h"
#include "../Items/AttackItems/Charm.h"
#include "../Items/AttackItems/EnhancedCharm.h"
#include "../Items/Props/Bandage.h"
#include "../Items/Props/Medkit.h"
#include "../Items/Props/Adrenaline.h"

BattleScene::BattleScene(QObject *parent) : Scene(parent) {// 现在只有一个地图
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);
    // 在这里实现各种资源的初始化与加入
    map = new MistyLake();
    bridge = new Bridge();
    highGrassLeft = new HighGrass();
    highGrassRight = new HighGrass();
    character_1p = new Character(nullptr, "Reimu", 1);
    character_2p = new Character(nullptr, "Marisa", 2);

    // 将地图、角色和备用护甲添加到场景中
    addItem(map);
    addItem(bridge);
    addItem(highGrassLeft);
    addItem(highGrassRight);

    if(character_1p != nullptr) {
        addItem(character_1p);
    }

    if(character_2p != nullptr) {
        addItem(character_2p);
    }
    character_1p->isOnTheRight = false; // 1P角色在左边
    character_2p->isOnTheRight = true; // 2P角色在右边

    // 设置初始位置
    map->scaleToFitScene(this);
    bridge->setPos(QPointF(390, 280));
    highGrassLeft->setPos(QPointF(232, 442));
    highGrassRight->setPos(QPointF(792, 442));

    if(character_1p != nullptr){
        character_1p->setPos(QPointF(100, 600 - character_1p->boundingRect().height()));
    }
    if(character_2p != nullptr){
        character_2p->setPos(QPointF(1000, 600 - character_2p->boundingRect().height()));
    }

    connect(character_1p, &Character::fireBullet, this, &BattleScene::onBulletFired);
    connect(character_2p, &Character::fireBullet, this, &BattleScene::onBulletFired);

    connect(character_1p, &Character::dealMeleeDamage, character_2p, &Character::takeMeleeDamage);
    connect(character_2p, &Character::dealMeleeDamage, character_1p, &Character::takeMeleeDamage);

    // 创建血条
    hpBar_1p = new HpBar(character_1p->getMaxHp(), nullptr);
    hpBar_1p->setPos(150, 50); // 设置1P血条位置
    addItem(hpBar_1p);
    hpBar_2p = new HpBar(character_2p->getMaxHp(), nullptr);
    hpBar_2p->setPos(1030, 50); // 设置2P血条位置
    addItem(hpBar_2p);

    // 创建护甲条
    armorBar_1p = new ArmorBar(character_1p->getMaxArmor(), nullptr);
    armorBar_1p->setPos(150, 80); // 设置1P护甲条位置
    addItem(armorBar_1p);
    armorBar_2p = new ArmorBar(character_2p->getMaxArmor(), nullptr);
    armorBar_2p->setPos(1030, 80); // 设置2P护甲条位置
    addItem(armorBar_2p);

    // 创建子弹条
    ammoBar_1p = new AmmoBar(character_1p->getMaxAmmoQuantity(), nullptr);
    ammoBar_1p->setPos(150, 110); // 设置1P子弹条位置
    addItem(ammoBar_1p);
    ammoBar_2p = new AmmoBar(character_2p->getMaxAmmoQuantity(), nullptr);
    ammoBar_2p->setPos(1030, 110); // 设置2P子弹条位置
    addItem(ammoBar_2p);

    // 创建肾上腺素文本
    adrenalineText_1p = new QGraphicsTextItem();
    adrenalineText_1p->setDefaultTextColor(Qt::red);
    adrenalineText_1p->setFont(QFont("微软雅黑", 10));
    adrenalineText_1p->setPlainText("正在处于肾上腺素治疗");
    adrenalineText_1p->setVisible(false);
    adrenalineText_1p->setPos(ammoBar_1p->pos() + QPointF(0, ammoBar_1p->boundingRect().height() + 12));
    addItem(adrenalineText_1p);

    adrenalineText_2p = new QGraphicsTextItem();
    adrenalineText_2p->setDefaultTextColor(Qt::red);
    adrenalineText_2p->setFont(QFont("微软雅黑", 10));
    adrenalineText_2p->setPlainText("正在处于肾上腺素治疗");
    adrenalineText_2p->setVisible(false);
    adrenalineText_2p->setPos(ammoBar_2p->pos() + QPointF(0, ammoBar_2p->boundingRect().height() + 12));
    addItem(adrenalineText_2p);

    dropTimer = new QTimer(this);
    connect(dropTimer, &QTimer::timeout, this, &BattleScene::spawnRandomDrop);
    allTimers.append(dropTimer); // 将定时器添加到所有定时器列表中
    dropTimer->start(20000);
}

// 这个函数用来处理角色输入事件
void BattleScene::processInput() {
    if (gameOver) return;
    Scene::processInput();
    if (character_1p != nullptr && character_2p != nullptr)
    {
        if(character_1p->pos().x() <= character_2p->pos().x()) {
            character_1p->isOnTheRight = false; // 1P角色在左边
            character_2p->isOnTheRight = true; // 2P角色在右边
        }
        else {
            character_1p->isOnTheRight = true; // 1P角色在右边
            character_2p->isOnTheRight = false; // 2P角色在左边
        }
    }
    if (character_1p != nullptr) {
        character_1p->processInput();
    }
    if (character_2p != nullptr) {
        character_2p->processInput();
    }

    // 更新血条
    if (hpBar_1p != nullptr && character_1p != nullptr) {
        hpBar_1p->setHp(character_1p->getHp());
    }
    if (hpBar_2p != nullptr && character_2p != nullptr) {
        hpBar_2p->setHp(character_2p->getHp());
    }

    // 更新护甲条
    if (armorBar_1p != nullptr && character_1p != nullptr) {
        armorBar_1p->setMaxHp(character_1p->getMaxArmor());
        armorBar_1p->setHp(character_1p->getArmor());
    }
    if (armorBar_2p != nullptr && character_2p != nullptr) {
        armorBar_2p->setMaxHp(character_2p->getMaxArmor());
        armorBar_2p->setHp(character_2p->getArmor());
    }

    // 更新子弹条
    if (ammoBar_1p != nullptr && character_1p != nullptr) {
        ammoBar_1p->setMaxQuantity(character_1p->getMaxAmmoQuantity());
        ammoBar_1p->setQuantity(character_1p->getAmmoQuantity());
    }
    if (ammoBar_2p != nullptr && character_2p != nullptr) {
        ammoBar_2p->setMaxQuantity(character_2p->getMaxAmmoQuantity());
        ammoBar_2p->setQuantity(character_2p->getAmmoQuantity());
    }

    // 更新肾上腺素文本
    if (character_1p->isAdrenaline) {
        adrenalineText_1p->setVisible(true);
    } else {
        adrenalineText_1p->setVisible(false);
    }
    if (character_2p->isAdrenaline) {
        adrenalineText_2p->setVisible(true);
    } else {
        adrenalineText_2p->setVisible(false);
    }

    // 检查游戏是否结束
    if (!gameOver) {
        if (character_1p && character_1p->getHp() <= 0) {
            character_1p->setAnimationState(Character::down);
            character_2p->setAnimationState(Character::stand);
            winnerName = character_2p ? character_2p->getName() : "???";
            gameOver = true;
            showGameOverScreen();
            stopAllTimers();
        } else if (character_2p && character_2p->getHp() <= 0) {
            character_2p->setAnimationState(Character::down);
            character_1p->setAnimationState(Character::stand);
            winnerName = character_1p ? character_1p->getName() : "???";
            gameOver = true;
            showGameOverScreen();
            stopAllTimers();
        }
    }

}

// 这个函数用来处理角色的按键事件
void BattleScene::keyPressEvent(QKeyEvent *event) {
    if(character_1p != nullptr){
        switch (event->key()) {
        case Qt::Key_A:
            character_1p->setLeftDown(true);
            break;
        case Qt::Key_D:
            character_1p->setRightDown(true);
            break;
        case Qt::Key_S:
            if(findNearestUnmountedMountable(character_1p->pos(), 100.0) != nullptr || findNearestProps(character_1p->pos(), 100.0) != nullptr) {
                character_1p->setPickDown(true);
            } else {
                character_1p->setGuardDown(true);
            }
            break;
        case Qt::Key_F:
            character_1p->setAttackDown(true);
            break;
        case Qt::Key_G:
            character_1p->setJumpDown(true);
            break;
        default:
            Scene::keyPressEvent(event);
        }
    }
    if(character_2p != nullptr){
        switch (event->key()) {
        case Qt::Key_H:
            character_2p->setLeftDown(true);
            break;
        case Qt::Key_K:
            character_2p->setRightDown(true);
            break;
        case Qt::Key_J:
            if(findNearestUnmountedMountable(character_2p->pos(), 100.0 ) != nullptr || findNearestProps(character_2p->pos(), 100.0) != nullptr) {
                character_2p->setPickDown(true);
            } else {
                character_2p->setGuardDown(true);
            }
            break;
        case Qt::Key_L:
            character_2p->setAttackDown(true);
            break;
        case Qt::Key_Semicolon:
            character_2p->setJumpDown(true);
            break;
        default:
            Scene::keyPressEvent(event);
        }
    }
}

// 这个函数用来处理角色的按键释放事件
void BattleScene::keyReleaseEvent(QKeyEvent *event) {
    if(character_1p != nullptr){
        switch (event->key()) {
        case Qt::Key_A:
            if (character_1p != nullptr) {
                character_1p->setLeftDown(false);
            }
            break;
        case Qt::Key_D:
            if (character_1p != nullptr) {
                character_1p->setRightDown(false);
            }
            break;
        case Qt::Key_S:
            if (character_1p != nullptr) {
                if (character_1p->isGuardDown()) {
                    character_1p->setGuardDown(false);
                } else {
                    character_1p->setPickDown(false);
                }
            }
            break;
        case Qt::Key_F:
            if (character_1p != nullptr) {
                character_1p->setAttackDown(false);
            }
            break;
        case Qt::Key_G:
            if (character_1p != nullptr) {
                character_1p->setJumpDown(false);
            }
            break;
        default:
            Scene::keyReleaseEvent(event);
        }
    }
    if(character_2p != nullptr){
        switch (event->key()) {
        case Qt::Key_H:
            if (character_2p != nullptr) {
                character_2p->setLeftDown(false);
            }
            break;
        case Qt::Key_K:
            if (character_2p != nullptr) {
                character_2p->setRightDown(false);
            }
            break;
        case Qt::Key_J:
            if (character_2p != nullptr) {
                if (character_2p->isGuardDown()) {
                    character_2p->setGuardDown(false);
                } else {
                    character_2p->setPickDown(false);
                }
            }
            break;
        case Qt::Key_L:
            if (character_2p != nullptr) {
                character_2p->setAttackDown(false);
            }
            break;
        case Qt::Key_Semicolon:
            if (character_2p != nullptr) {
                character_2p->setJumpDown(false);
            }
            break;
        default:
            Scene::keyReleaseEvent(event);
        }
    }
    // 以下为测试时添加的掉落物品代码，在游戏中会被注释掉
    // 1.随机掉落
    switch (event->key()){
    case Qt::Key_Z:
    {
        Item *drop1 = new EnhancedMelee();
        // 2. 随机X坐标，y=0
        QRectF area = sceneRect();
        qreal x = area.left() + rand() % (int)(area.width() - drop1->boundingRect().width());
        drop1->setPos(x, 0);
        addItem(drop1);
        floatingMountables.append(drop1);
    }
        break;
    case Qt::Key_X:
    {
        Item *drop2 = new Throw();
        // 2. 随机X坐标，y=0
        QRectF area2 = sceneRect();
        qreal x2 = area2.left() + rand() % (int)(area2.width() - drop2->boundingRect().width());
        drop2->setPos(x2, 0);
        addItem(drop2);
        floatingMountables.append(drop2);
    }
        break;
    case Qt::Key_C:
    {
        Item *drop3 = new Ranged();
        // 2. 随机X坐标，y=0
        QRectF area3 = sceneRect();
        qreal x3 = area3.left() + rand() % (int)(area3.width() - drop3->boundingRect().width());
        drop3->setPos(x3, 0);
        addItem(drop3);
        floatingMountables.append(drop3);
    }
        break;
    case Qt::Key_V:
    {
        Item *drop4 = new SpellCard();
        // 2. 随机X坐标，y=0
        QRectF area4 = sceneRect();
        qreal x4 = area4.left() + rand() % (int)(area4.width() - drop4->boundingRect().width());
        drop4->setPos(x4, 0);
        addItem(drop4);
        floatingMountables.append(drop4);
    }
        break;
    case Qt::Key_B:
    {
        Item *drop5 = new LightArmor();
        // 2. 随机X坐标，y=0
        QRectF area5 = sceneRect();
        qreal x5 = area5.left() + rand() % (int)(area5.width() - drop5->boundingRect().width());
        drop5->setPos(x5, 0);
        addItem(drop5);
        floatingMountables.append(drop5);
    }
        break;
    case Qt::Key_N:
    {
        Item *drop6 = new HeavyArmor();
        // 2. 随机X坐标，y=0
        QRectF area6 = sceneRect();
        qreal x6 = area6.left() + rand() % (int)(area6.width() - drop6->boundingRect().width());
        drop6->setPos(x6, 0);
        addItem(drop6);
        floatingMountables.append(drop6);
    }
        break;
    case Qt::Key_M:
    {
        Item *drop7 = new Bandage();
        // 2. 随机X坐标，y=0
        QRectF area7 = sceneRect();
        qreal x7 = area7.left() + rand() % (int)(area7.width() - drop7->boundingRect().width());
        drop7->setPos(x7, 0);
        addItem(drop7);
        floatingMountables.append(drop7);
    }
        break;
    case Qt::Key_Comma:
    {
        Item *drop8 = new Medkit();
        // 2. 随机X坐标，y=0
        QRectF area8 = sceneRect();
        qreal x8 = area8.left() + rand() % (int)(area8.width() - drop8->boundingRect().width());
        drop8->setPos(x8, 0);
        addItem(drop8);
        floatingMountables.append(drop8);
    }
        break;
    case Qt::Key_Period:
    {
        Item *drop9 = new Adrenaline();
        // 2. 随机X坐标，y=0
        QRectF area9 = sceneRect();
        qreal x9 = area9.left() + rand() % (int)(area9.width() - drop9->boundingRect().width());
        drop9->setPos(x9, 0);
        addItem(drop9);
        floatingMountables.append(drop9);
    }
        break;
    // 2.在地面中央生成
    case Qt::Key_0:
    {
        Item *create1 = new EnhancedMelee();
        create1->setPos(QPointF(sceneRect().width() / 2 - create1->boundingRect().width() / 2, map->getFloorHeight() - create1->boundingRect().height()));
        addItem(create1);
        onGroundMountables.append(create1);
    }
        break;
    case Qt::Key_1:
    {
        Item *create2 = new Throw();
        create2->setPos(QPointF(sceneRect().width() / 2 - create2->boundingRect().width() / 2, map->getFloorHeight() - create2->boundingRect().height()));
        addItem(create2);
        onGroundMountables.append(create2);
    }
        break;
    case Qt::Key_2:
    {
        Item *create3 = new Ranged();
        create3->setPos(QPointF(sceneRect().width() / 2 - create3->boundingRect().width() / 2, map->getFloorHeight() - create3->boundingRect().height()));
        addItem(create3);
        onGroundMountables.append(create3);
    }
        break;
    case Qt::Key_3:
    {
        Item *create4 = new SpellCard();
        create4->setPos(QPointF(sceneRect().width() / 2 - create4->boundingRect().width() / 2, map->getFloorHeight() - create4->boundingRect().height()));
        addItem(create4);
        onGroundMountables.append(create4);
    }
        break;
    case Qt::Key_4:
    {
        Item *create5 = new LightArmor();
        create5->setPos(QPointF(sceneRect().width() / 2 - create5->boundingRect().width() / 2, map->getFloorHeight() - create5->boundingRect().height()));
        addItem(create5);
        onGroundMountables.append(create5);
    }
        break;
    case Qt::Key_5:
    {
        Item *create6 = new HeavyArmor();
        create6->setPos(QPointF(sceneRect().width() / 2 - create6->boundingRect().width() / 2, map->getFloorHeight() - create6->boundingRect().height()));
        addItem(create6);
        onGroundMountables.append(create6);
    }
        break;
    case Qt::Key_6:
    {
        Item *create7 = new Bandage();
        create7->setPos(QPointF(sceneRect().width() / 2 - create7->boundingRect().width() / 2, map->getFloorHeight() - create7->boundingRect().height()));
        addItem(create7);
        onGroundMountables.append(create7);
    }
        break;
    case Qt::Key_7:
    {
        Item *create8 = new Medkit();
        create8->setPos(QPointF(sceneRect().width() / 2 - create8->boundingRect().width() / 2, map->getFloorHeight() - create8->boundingRect().height()));
        addItem(create8);
        onGroundMountables.append(create8);
    }
        break;
    case Qt::Key_8:
    {
        Item *create9 = new Adrenaline();
        create9->setPos(QPointF(sceneRect().width() / 2 - create9->boundingRect().width() / 2, map->getFloorHeight() - create9->boundingRect().height()));
        addItem(create9);
        onGroundMountables.append(create9);
    }
        break;
    case Qt::Key_Escape:
    {
        for (Item* item : onGroundMountables) {
            removeItem(item); // 从场景移除
            delete item;      // 释放内存
        }
        onGroundMountables.clear();
        qDebug() << "已删除并清空地面道具";
        break;
    }
    default:
        break;
    }
}

// 更新场景状态
void BattleScene::update() {
    Scene::update();
}

// 处理移动逻辑
void BattleScene::processMovement() {
    Scene::processMovement();
    if (character_1p != nullptr) {
        character_1p->setPos(character_1p->pos() + character_1p->getVelocity() * (double) deltaTime);
    }
    if (character_2p != nullptr) {
        character_2p->setPos(character_2p->pos() + character_2p->getVelocity() * (double) deltaTime);
    }

    // 更新所有子弹位置
    for (auto it = bullets.begin(); it != bullets.end(); it ++) {
        if(it == nullptr)
        {
            continue; // 跳过空指针
        }
        RangedItem* bullet = *it;

        // 更新子弹位置（基于速度和时间差）
        bullet->setPos(bullet->pos() + bullet->getVelocity() * (double)deltaTime);
        // 处理子弹物理效果（如重力，以Ball为例）
        bullet->changeVelocity();

        // 处理子弹碰撞和消失
        bullet->toDamageOrVanish();
    }

    // 移除需要删除的子弹
    for (auto it = bullets.begin(); it != bullets.end();) {
        RangedItem* bullet = *it;
        if (bullet->isToRemove) {
            delete bullet; // 删除子弹对象
            it = bullets.erase(it); // 从容器中移除
        } else {
            ++it; // 继续下一个子弹
        }
    }
}


// 碰撞检测
void BattleScene::processCollision() {
    Scene::processCollision();
    QVector<Character *> characterVec;
    if (character_1p != nullptr) {
        characterVec.append(character_1p);
    }
    if (character_2p != nullptr) {
        characterVec.append(character_2p);
    }
    for(auto &character : characterVec)
    {
        if (character != nullptr) {
            // 检查角色与地图的碰撞
            if (character->collidesWithItem(map)) {
                if(character->pos().y() <= 0){
                    character->setPos(character->pos().x(), 0); // 防止角色掉出场景上边界
                    character->setVelocity(QPointF(character->getVelocity().x(), 0)); // 停止角色上升
                }

                if (character->pos().x() < 0) {
                    character->setPos(0, character->pos().y()); // 防止角色掉出场景左边界
                }
                else if (character->pos().x() > sceneRect().width() - character->boundingRect().width()) {
                    character->setPos(sceneRect().width() - character->boundingRect().width(), character->pos().y()); // 防止角色掉出场景右边界
                }
            }

            // 检查角色与地板的碰撞
            if(character->pos().y() >= map->getFloorHeight() - character->boundingRect().height()) {
                character->setPos(character->pos().x(), map->getFloorHeight() - character->boundingRect().height());
            }

            // 是否在地面判断
            if ((character->pos().y() >= map->getFloorHeight() - character->boundingRect().height())) {
                character->isOnPlatform = true;
            }
            else if(character->collidesWithItem(bridge)) {
                qreal characterBottom = character->pos().y() + character->boundingRect().height();
                if (characterBottom <= bridge->getCollisionLine().y2() + 10 && character->getVelocity().y() >= 0) {
                    character->setPos(character->pos().x(), bridge->getCollisionLine().y2() - character->boundingRect().height());
                    character->isOnPlatform = true;
                }
                else{
                    character->isOnPlatform = false;
                }
            }
            else {
                character->isOnPlatform = false;
            }

            // 是否在冰面判断（由于图片问题，这里直接使用硬编码）
            if (character->pos().x() >= 472 && character->pos().x() <= 728 && (character->pos().y() >= map->getFloorHeight() - character->boundingRect().height())) {
                character->isOnIce = true;
            }
            else {
                character->isOnIce = false;
            }

            // 是否和草丛碰撞
            if (character->collidesWithItem(highGrassLeft) &&
                (character->pos().x() + character->collisionRect.left()) >= highGrassLeft->pos().x() &&
                (character->pos().x() + character->collisionRect.right()) <= highGrassLeft->pos().x() + highGrassLeft->boundingRect().width()) {
                character->isNearHighGrass = true;
            }
            else if(character->collidesWithItem(highGrassRight) &&
                    (character->pos().x() + character->collisionRect.left()) >= highGrassRight->pos().x() &&
                    (character->pos().x() + character->collisionRect.right()) <= highGrassRight->pos().x() + highGrassRight->boundingRect().width()) {
                character->isNearHighGrass = true;
            }
            else if(character->isNearHighGrass) {
                character->isNearHighGrass = false;
            }
        }


    }
    // 是否与另一角色碰撞
    if(character_1p->collidesWithItem(character_2p)){
        character_1p->isCollidingWithEachOther = true;
        character_2p->isCollidingWithEachOther = true;
    }
    else{
        character_1p->isCollidingWithEachOther = false;
        character_2p->isCollidingWithEachOther = false;
    }

    // 掉落道具判断
    for (auto item : floatingMountables) {
        item->setVelocity(QPointF(0, item->getVelocity().y() + 0.03));
        if (item->pos().y() >= map->getFloorHeight() - item->boundingRect().height()) {
            item->setPos(item->pos().x(), map->getFloorHeight() - item->boundingRect().height());
            item->setVelocity(QPointF(0, 0)); // 停止下落
            onGroundMountables.push_back(item);
            floatingMountables.removeOne(item); // 从浮动列表中移除
            qDebug() << "当前浮动道具列表大小：" << floatingMountables.size();
            qDebug() << "当前平台上道具列表大小：" << onGroundMountables.size();
            qDebug() << "道具掉落到地面，位置：" << item->pos();
        }
        else if(item->collidesWithItem(bridge)) {
            qreal itemBottom = item->pos().y() + item->boundingRect().height();
            if (itemBottom <= bridge->getCollisionLine().y2() + 10 && item->getVelocity().y() >= 0) {
                item->setPos(item->pos().x(), bridge->getCollisionLine().y2() - item->boundingRect().height());
                item->setVelocity(QPointF(0, 0)); // 停止下落
                qDebug() << "道具掉落到桥上，位置：" << item->pos();
                onGroundMountables.push_back(item);
                floatingMountables.removeOne(item); // 从浮动列表中移除
                qDebug() << "当前浮动道具列表大小：" << floatingMountables.size();
                qDebug() << "当前平台上道具列表大小：" << onGroundMountables.size();
                qDebug() << "道具掉落到桥上，位置：" << item->pos();
            }
        }
        else {
            item->setPos(item->pos() + item->getVelocity() * (double) deltaTime);
        }
    }
}


// 处理拾取逻辑
void BattleScene::processPicking() {
    Scene::processPicking();
    if (character_1p->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character_1p->pos(), 100.0);
        if (mountable != nullptr) {
            if(onGroundMountables.contains(dynamic_cast<Item *>(mountable))) {
                onGroundMountables.removeOne(dynamic_cast<Item *>(mountable)); // 从已放置装备列表中移除
                qDebug() << "从地面装备列表中移除，当前大小为：" << onGroundMountables.size();
            }
            if(dynamic_cast<Armor *>(mountable) != nullptr) {
                Armor *spareArmor = dynamic_cast<Armor *>(pickupMountable(character_1p, mountable));
                if (spareArmor != nullptr) {
                    qDebug() << "旧护甲放置位置为" << spareArmor->pos();
                    onGroundMountables.append(spareArmor); // 将旧护甲添加到已放置装备列表
                }
            }
            else if(dynamic_cast<Weapon *>(mountable) != nullptr){
                Weapon *spareWeapon = dynamic_cast<Weapon *>(pickupMountable(character_1p, mountable));
                if (spareWeapon != nullptr) {
                    qDebug() << "旧武器放置位置为" << spareWeapon->pos();
                    onGroundMountables.append(spareWeapon); // 将旧武器添加到已放置装备列表
                }
            }
        }

        Props *props = findNearestProps(character_1p->pos(), 100.0);
        if (props != nullptr) {
            onGroundMountables.removeOne(props); // 从已放置装备列表中移除
            qDebug() << "准备调用pickupProp，props=" << props << ", character=" << character_1p;
            qDebug() << "props typeid=" << typeid(*props).name();
            qDebug() << "character typeid=" << typeid(*character_1p).name();
            pickupProp(character_1p, props);
            qDebug() << "拾取道具";
        }
    }
    if (character_2p->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character_2p->pos(), 100.0);
        if (mountable != nullptr) {
            if(onGroundMountables.contains(dynamic_cast<Item *>(mountable))) {
                onGroundMountables.removeOne(dynamic_cast<Item *>(mountable)); // 从已放置装备列表中移除
                qDebug() << "从地面装备列表中移除，当前大小为：" << onGroundMountables.size();
            }
            if(dynamic_cast<Armor *>(mountable) != nullptr) {
                Armor *spareArmor = dynamic_cast<Armor *>(pickupMountable(character_2p, mountable));
                if (spareArmor != nullptr) {
                    qDebug() << "旧护甲放置位置为" << spareArmor->pos();
                    onGroundMountables.append(spareArmor); // 将旧护甲添加到已放置装备列表
                }
            }
            else if(dynamic_cast<Weapon *>(mountable) != nullptr){
                Weapon *spareWeapon = dynamic_cast<Weapon *>(pickupMountable(character_2p, mountable));
                if (spareWeapon != nullptr) {
                    qDebug() << "旧武器放置位置为" << spareWeapon->pos();
                    onGroundMountables.append(spareWeapon); // 将旧武器添加到已放置装备列表
                }
            }
        }
        auto props = findNearestProps(character_2p->pos(), 100.0);
        if (props != nullptr) {
            onGroundMountables.removeOne(props); // 从已放置装备列表中移除
            pickupProp(character_2p, props);
        }
    }
}

// 查找距离指定位置最近的未被挂载的Mountable对象
Mountable *BattleScene::findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold) {
    Mountable *nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (QGraphicsItem *item: items()) {
        if (auto mountable = dynamic_cast<Mountable *>(item)) {
            if (!mountable->isMounted()) {
                qreal distance = QLineF(pos, item->pos()).length();
                if (distance < minDistance) {
                    minDistance = distance;
                    nearest = mountable;
                }
            }
        }
    }

    return nearest;
}

Props *BattleScene::findNearestProps(const QPointF &pos, qreal distance_threshold) {
    Props *nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (QGraphicsItem *item: items()) {
        if (auto props = dynamic_cast<Props *>(item)) {
            qreal distance = QLineF(pos, item->pos()).length();
            if (distance < minDistance) {
                minDistance = distance;
                nearest = props;
            }
        }
    }

    return nearest;
}

// 拾取指定的Mountable对象
Mountable *BattleScene::pickupMountable(Character *character, Mountable *mountable) {
    if (auto armor = dynamic_cast<Armor *>(mountable)) {
        qDebug() << "拾取的护甲位置为" << armor->pos();
        return character->pickupArmor(armor);
    }
    if (auto weapon = dynamic_cast<Weapon *>(mountable)) {
        return character->pickupWeapon(weapon);
    }
    return nullptr;
}

void BattleScene::pickupProp(Character *character, Props *props) {
    if (props != nullptr && character != nullptr) {
        character->pickupProps(props);
    }
}

void BattleScene::onBulletFired(Weapon* weapon, const QPointF& firePos, bool isRight, const QString &fromCharacterName, const int &fromPlayerID) {
    RangedItem* bullet = nullptr;

    qDebug() << "收到子弹信号：weaponID=" << weapon->weaponID
             << "，发射者=" << fromCharacterName; // 确认信号正确传递

    // 根据武器类型创建对应子弹
    switch (weapon->weaponID) {
    case 3:
        bullet = new Ball(nullptr, ":/AttackItems/Items/AttackItems/" + fromCharacterName + "/3.png");
        qDebug() << "创建了一个Ball子弹";
        break;
    case 4:
        bullet = new Charm(nullptr, ":/AttackItems/Items/AttackItems/" + fromCharacterName + "/4.png");
        bullet->fromCharacterID = fromPlayerID; // 设置发射者ID
        break;
    case 5:
        bullet = new EnhancedCharm(nullptr, ":/AttackItems/Items/AttackItems/" + fromCharacterName + "/5.png");
        bullet->fromCharacterID = fromPlayerID; // 设置发射者ID
        break;
    default:
        return; // 非远程武器不处理
    }

    if (bullet) {
        bullet->fromCharacterID = fromPlayerID; // 设置发射者ID
        // 设置子弹初始位置
        bullet->setPos(firePos);
        qDebug() << "子弹初始位置：" << firePos;

        // 根据角色朝向设置子弹速度方向
        QPointF bulletVel = bullet->getVelocity();
        bulletVel.setX(isRight ? -bulletVel.x() : bulletVel.x()); // 右侧角色朝左发射，速度为负
        bullet->setVelocity(bulletVel);

        addItem(bullet);
        bullets.push_back(bullet);
        qDebug() << "子弹添加到场景，容器大小=" << bullets.size();
    }
}


void BattleScene::spawnRandomDrop(){
    int type = rand() % 9;
    qDebug() << "生成掉落物，类型：" << type;
    Item* drop = nullptr;
    switch(type) {
    case 0: drop = new EnhancedMelee(); break;
    case 1: drop = new Throw(); break;
    case 2: drop = new Ranged(); break;
    case 3: drop = new SpellCard(); break;
    case 4: drop = new LightArmor(); break;
    case 5: drop = new HeavyArmor(); break;
    case 6: drop = new Bandage(); break;
    case 7: drop = new Medkit(); break;
    case 8: drop = new Adrenaline(); break;
    default: return; // 如果类型不在范围内则不生成
    }
    // 2. 随机X坐标，y=0
    QRectF area = sceneRect();
    qreal x = area.left() + rand() % (int)(area.width() - drop->boundingRect().width());
    drop->setPos(x, 0);

    addItem(drop);
    floatingMountables.append(drop);
}



// 游戏结束

void BattleScene::showGameOverScreen() {
    if (!winnerLabel) {
        winnerLabel = new QLabel;
        winnerLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        winnerLabel->setStyleSheet("font-size: 32px; color: red; background: rgba(255,255,255,0.8);");
        winnerLabelProxy = addWidget(winnerLabel);
        winnerLabelProxy->setZValue(10);
        winnerLabelProxy->setPos(0, 0);
        winnerLabelProxy->resize(sceneRect().width(), 60);
    }
    winnerLabel->setText(QString("%1 获胜！").arg(winnerName));
    winnerLabelProxy->show();

    if (!restartButton) {
        restartButton = new QPushButton("退出");
        restartButtonProxy = addWidget(restartButton);
        restartButtonProxy->setZValue(10);
        restartButtonProxy->setPos(sceneRect().width()/2-60, sceneRect().height()/2);
        restartButtonProxy->resize(120, 40);
        connect(restartButton, &QPushButton::clicked, this, &BattleScene::exitGame);
    }
    restartButtonProxy->show();
}

// 停止所有定时器（如有多个定时器都可以放进 allTimers）
void BattleScene::stopAllTimers() {
    for (QTimer* timer : allTimers) {
        if (timer) timer->stop();
    }
    // 如有其它要停止的东西，也可以加在这里
}

// 退出游戏
void BattleScene::exitGame() {
    if (winnerLabelProxy) winnerLabelProxy->hide();
    if (restartButtonProxy) restartButtonProxy->hide();
    qApp->exit(0);
}
