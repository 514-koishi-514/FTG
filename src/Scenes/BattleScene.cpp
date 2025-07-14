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
    character = new Character(nullptr, "Reimu");
    spareArmor = new FlamebreakerArmor(); // TODO:这里目前是实现了一个一开始就放置在场景中的备用护甲，之后我会进行实际的修改

    // 将地图、角色和备用护甲添加到场景中
    addItem(map);
    addItem(bridge);
    addItem(highGrassLeft);
    addItem(highGrassRight);
    addItem(character);
    addItem(spareArmor);

    // 设置初始位置
    map->scaleToFitScene(this);
    bridge->setPos(QPointF(390, 280));
    highGrassLeft->setPos(QPointF(232, 442));
    highGrassRight->setPos(QPointF(1048, 442));

    character->setPos(QPointF(100, 600- character->boundingRect().height()));
    spareArmor->unmount();
    spareArmor->setPos(sceneRect().left() + (sceneRect().right() - sceneRect().left()) * 0.75, map->getFloorHeight() - spareArmor->boundingRect().height());
}

// 这个函数用来处理角色输入事件
void BattleScene::processInput() {
    Scene::processInput();
    if (character != nullptr) {
        character->processInput();
    }
}

// 这个函数用来处理角色的按键事件
void BattleScene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A:
        if (character != nullptr) {
            character->setLeftDown(true);
        }
        break;
    case Qt::Key_D:
        if (character != nullptr) {
            character->setRightDown(true);
        }
        break;
    case Qt::Key_S:
        if (character != nullptr) {
            if(findNearestUnmountedMountable(character->pos(), 100.) != nullptr) {
                character->setPickDown(true);
            } else {
                character->setGuardDown(true);
            }
        }
        break;
    case Qt::Key_J:
        if (character != nullptr) {
            character->setAttackDown(true);
        }
        break;
    case Qt::Key_K:
        if (character != nullptr) {
            character->setJumpDown(true);
        }
        break;
    default:
        Scene::keyPressEvent(event);
    }
}

// 这个函数用来处理角色的按键释放事件
void BattleScene::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A:
        if (character != nullptr) {
            character->setLeftDown(false);
        }
        break;
    case Qt::Key_D:
        if (character != nullptr) {
            character->setRightDown(false);
        }
        break;
    case Qt::Key_S:
        if (character != nullptr) {
            if (character->isGuardDown()) {
                character->setGuardDown(false);
            } else {
                character->setPickDown(false);
            }
        }
        break;
    case Qt::Key_J:
        if (character != nullptr) {
            character->setAttackDown(false);
        }
        break;
    case Qt::Key_K:
        if (character != nullptr) {
            character->setJumpDown(false);
        }
        break;
    default:
        Scene::keyReleaseEvent(event);
    }
}

// 更新场景状态
void BattleScene::update() {
    Scene::update();
}

// 处理角色的移动逻辑
void BattleScene::processMovement() {
    Scene::processMovement();
    if (character != nullptr) {
        character->setPos(character->pos() + character->getVelocity() * (double) deltaTime);
    }
}

// 碰撞检测
void BattleScene::processCollision() {
    Scene::processCollision();
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
            qreal bridgeTop = bridge->pos().y();
            if(characterBottom >= bridgeTop - 10 &&
                characterBottom <= bridgeTop + 10 &&
                character->getVelocity().y() >= 0) {
                character->setPos(character->pos().x(), bridgeTop - character->boundingRect().height());
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

// 处理拾取逻辑
void BattleScene::processPicking() {
    Scene::processPicking();
    if (character->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character->pos(), 100.0);
        if (mountable != nullptr) {
            spareArmor = dynamic_cast<Armor *>(pickupMountable(character, mountable));
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
