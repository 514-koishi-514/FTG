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
    spareArmor = new class HeavyArmor(); // TODO:这里目前是实现了一个一开始就放置在场景中的备用护甲，之后我会进行实际的修改
    spareWeapon = new EnhancedMelee(); // TODO:这里目前是实现了一个一开始就放置在场景中的备用武器，之后我会进行实际的修改

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

    addItem(spareArmor);
    addItem(spareWeapon);


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

    // TODO:以下两个都需要改
    spareArmor->unmount();
    spareArmor->setPos(sceneRect().left() + (sceneRect().right() - sceneRect().left()) * 0.75, map->getFloorHeight() - spareArmor->boundingRect().height());

    spareWeapon->unmount();
    spareWeapon->setPos(640, map->getFloorHeight() - spareWeapon->boundingRect().height());
    qDebug() << "空武器的位置" << spareWeapon->pos();

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

    dropTimer = new QTimer(this);
    connect(dropTimer, &QTimer::timeout, this, &BattleScene::spawnRandomDrop);
    allTimers.append(dropTimer); // 将定时器添加到所有定时器列表中
    dropTimer->start(10000); // 每30秒
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
        }
        else if(item->collidesWithItem(bridge)) {
            qreal characterBottom = item->pos().y() + item->boundingRect().height();
            if (characterBottom <= bridge->getCollisionLine().y2() + 10 && item->getVelocity().y() >= 0) {
                item->setVelocity(QPointF(0, 0)); // 停止下落
                onGroundMountables.push_back(item);
                floatingMountables.removeOne(item); // 从浮动列表中移除
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
            spareArmor = dynamic_cast<Armor *>(pickupMountable(character_1p, mountable));
            spareWeapon = dynamic_cast<Weapon *>(pickupMountable(character_1p, mountable));
        }
        Props *props = findNearestProps(character_1p->pos(), 100.0);
        if (props != nullptr) {
            pickupProp(character_1p, props);
        }
    }
    if (character_2p->isPicking()) {
        auto mountable = findNearestUnmountedMountable(character_2p->pos(), 100.0);
        if (mountable != nullptr) {
            spareArmor = dynamic_cast<Armor *>(pickupMountable(character_2p, mountable));
            spareWeapon = dynamic_cast<Weapon *>(pickupMountable(character_2p, mountable));
        }
        auto props = findNearestProps(character_1p->pos(), 100.0);
        if (props != nullptr) {
            pickupProp(character_1p, props);
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
    // Limitation: currently only supports armor
    if (auto armor = dynamic_cast<Armor *>(mountable)) {
        return character->pickupArmor(armor);
    }
    if (auto weapon = dynamic_cast<Weapon *>(mountable)) {
        return character->pickupWeapon(weapon);
    }
    return nullptr;
}

void *BattleScene::pickupProp(Character *character, Props *props) {
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
    int type = rand() % 6;
    Item* drop = nullptr;
    switch(type) {
    case 0: drop = new EnhancedMelee(); break;
    case 1: drop = new Throw(); break;
    case 2: drop = new Ranged(); break;
    case 3: drop = new SpellCard(); break;
    case 4: drop = new LightArmor(); break;
    case 5: drop = new HeavyArmor(); break;
//    case 6: drop = new Bandage(); break;
//    case 7: drop = new Medkit(); break;
//   case 8: drop = new Adrenaline(); break;
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
        connect(restartButton, &QPushButton::clicked, this, &BattleScene::restartGame);
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

// 重启游戏
void BattleScene::restartGame() {
    if (winnerLabelProxy) winnerLabelProxy->hide();
    if (restartButtonProxy) restartButtonProxy->hide();
    // 推荐 emit 一个信号让主窗口重启场景
    // emit requestRestart();
    qApp->exit(0); // 或换成你的重启方式
}
