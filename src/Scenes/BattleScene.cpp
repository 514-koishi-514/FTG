//
// BattleScene.cpp
// 实现战斗场景的输入处理、角色动作、拾取等功能
//

#include <QDebug>
#include "BattleScene.h"
#include "../Items/Maps/MistyLake.h"
#include "../Items/Armors/FlamebreakerArmor.h"

BattleScene::BattleScene(QObject *parent) : Scene(parent) {// 现在只有一个地图
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);
    // 在这里实现各种资源的初始化与加入
    map = new MistyLake();
    bridge = new Bridge();
    highGrassLeft = new HighGrass();
    highGrassRight = new HighGrass();
    character_1p = new Character(nullptr, "Reimu");
    character_2p = new Character(nullptr, "Marisa");
    spareArmor = new FlamebreakerArmor(); // TODO:这里目前是实现了一个一开始就放置在场景中的备用护甲，之后我会进行实际的修改

    qDebug() << "初始化";

    // 将地图、角色和备用护甲添加到场景中
    addItem(map);
    addItem(bridge);
    addItem(highGrassLeft);
    addItem(highGrassRight);
    qDebug() << "添加地图、桥和高草到场景中";
    if(character_1p != nullptr) {
        addItem(character_1p);
    }
    qDebug() << "添加角色1到场景中";
    if(character_2p != nullptr) {
        addItem(character_2p);
    }
    character_1p->isOnTheRight = false; // 1P角色在左边
    character_2p->isOnTheRight = true; // 2P角色在右边
    qDebug() << "添加角色2到场景中";
    addItem(spareArmor);

    qDebug() << "添加地图、角色和备用护甲到场景中";

    // 设置初始位置
    map->scaleToFitScene(this);
    bridge->setPos(QPointF(390, 280));
    highGrassLeft->setPos(QPointF(232, 442));
    highGrassRight->setPos(QPointF(1048, 442));

    if(character_1p != nullptr){
        character_1p->setPos(QPointF(100, 600 - character_1p->boundingRect().height()));
    }
    if(character_2p != nullptr){
        character_2p->setPos(QPointF(1000, 600 - character_2p->boundingRect().height()));
    }
    spareArmor->unmount();
    spareArmor->setPos(sceneRect().left() + (sceneRect().right() - sceneRect().left()) * 0.75, map->getFloorHeight() - spareArmor->boundingRect().height());

    qDebug() << "设置地图、角色和备用护甲的位置";
}

// 这个函数用来处理角色输入事件
void BattleScene::processInput() {
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
            if(findNearestUnmountedMountable(character_1p->pos(), 100.0) != nullptr) {
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
            if(findNearestUnmountedMountable(character_2p->pos(), 100.0) != nullptr) {
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
}

// 更新场景状态
void BattleScene::update() {
    Scene::update();
}

// 处理角色的移动逻辑
void BattleScene::processMovement() {
    Scene::processMovement();
    if (character_1p != nullptr) {
        character_1p->setPos(character_1p->pos() + character_1p->getVelocity() * (double) deltaTime);
    }
    if (character_2p != nullptr) {
        character_2p->setPos(character_2p->pos() + character_2p->getVelocity() * (double) deltaTime);
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

            // 是否在平台判断
            if ((character->pos().y() >= map->getFloorHeight() - character->boundingRect().height())
                ) {
                if (!character->isOnPlatform) {
                    qDebug() << "角色站在平台上";
                }
                character->isOnPlatform = true;
            }
            else if(character->collidesWithItem(bridge)) {
                qreal characterBottom = character->pos().y() + character->boundingRect().height();
                if (characterBottom <= bridge->getCollisionLine().y2() + 10 && character->getVelocity().y() >= 0) {
                    qDebug() << "角色站在桥上";
                    character->setPos(character->pos().x(), bridge->getCollisionLine().y2() - character->boundingRect().height());
                    character->isOnPlatform = true;
                }
                else{
                    if (character->isOnPlatform) {
                        qDebug() << "角色离开桥";
                    }
                    character->isOnPlatform = false;
                }
            }
            else {
                if (character->isOnPlatform) {
                    qDebug() << "角色离开平台";
                }
                character->isOnPlatform = false;
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
}

// 处理拾取逻辑
void BattleScene::processPicking() {
    Scene::processPicking();
    if (character_1p->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character_1p->pos(), 100.0);
        if (mountable != nullptr) {
            spareArmor = dynamic_cast<Armor *>(pickupMountable(character_1p, mountable));
        }
    }
    if (character_2p->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character_2p->pos(), 100.0);
        if (mountable != nullptr) {
            spareArmor = dynamic_cast<Armor *>(pickupMountable(character_2p, mountable));
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

// 拾取指定的Mountable对象
Mountable *BattleScene::pickupMountable(Character *character, Mountable *mountable) {
    // Limitation: currently only supports armor
    if (auto armor = dynamic_cast<Armor *>(mountable)) {
        return character->pickupArmor(armor);
    }
    return nullptr;
}
