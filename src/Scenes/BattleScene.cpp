//
// BattleScene.cpp
// 实现战斗场景的输入处理、角色动作、拾取等功能
//

#include <QDebug>
#include "BattleScene.h"
#include "../Items/Maps/Battlefield.h"
#include "../Items/Armors/FlamebreakerArmor.h"

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);
    // 在这里实现各种资源的初始化与加入
    map = new Battlefield();
    character = new Character(nullptr, "Reimu");
    spareArmor = new FlamebreakerArmor(); // 这里目前是实现了一个一开始就放置在场景中的备用护甲，之后我会进行实际的修改
    addItem(map);
    addItem(character);
    addItem(spareArmor);
    map->scaleToFitScene(this);
    character->setPos(map->getSpawnPos());
    spareArmor->unmount();
    spareArmor->setPos(sceneRect().left() + (sceneRect().right() - sceneRect().left()) * 0.75, map->getFloorHeight());
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
            character->setGuardDown(false);
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

// 处理拾取逻辑
void BattleScene::processPicking() {
    Scene::processPicking();
    if (character->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character->pos(), 100.);
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
