//
// Character.cpp
// 实现角色的立绘、动作逻辑、装备系统等功能
//

#include <QTransform>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTimer>
#include <QDebug>
#include "Character.h"
#include "../HeadEquipments/CapOfTheHero.h"
#include "../Armors/OldShirt.h"
#include "../LegEquipments/WellWornTrousers.h"
#include "../Weapons/Melee.h"
#include "../Weapons/Ranged.h"
#include "../Weapons/Throw.h"


Character::Character(QGraphicsItem *parent, const QString& name, const int &playerID) : Item(parent, ""), name(name), playerID(playerID) {
    //    ellipseItem = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
    //    // Optionally, set some properties of the ellipse
    //    ellipseItem->setBrush(Qt::green);          // Fill color
    //    ellipseItem->setZValue(1);

    setTransformOriginPoint(boundingRect().center());  // 变换中心
    configFilePath = "../../../FTG/assets/Configs/Character.json"; // 假设配置文件在资源文件中

    pixmapItem = new QGraphicsPixmapItem(this); // 自动绘制动画

    if (loadFromJson(configFilePath))
    {
        if (!animationFrames[stand].isEmpty()) {
            pixmapItem->setPixmap(animationFrames[stand][0]);
        }
    }

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, [this]() {
        pixmapItem->setPixmap(animationFrames[currentState][currentFrame]);
        if(currentState == attack_1 || currentState == attack_2 || currentState == attack_3 || currentState == attack_4 || currentState == attack_5) {
            qint64 newInterval = attackDuration / (animationFrames[currentState].size() - 1); // 攻击动画帧间隔
            animationTimer->setInterval(newInterval);
            currentFrame = (currentFrame + 1) % animationFrames[currentState].size();

        }
        else if(currentState == down){
            animationTimer->setInterval(100); // 普通动画帧间隔
            currentFrame = (currentFrame == animationFrames[currentState].size() - 1) ? currentFrame : (currentFrame + 1);
        }
        else if(currentState == guard){
            animationTimer->setInterval(100); // 普通动画帧间隔
            currentFrame = (currentFrame + 1) % animationFrames[currentState].size();
        }
        else{
            animationTimer->setInterval(100); // 普通动画帧间隔
            currentFrame = (currentFrame + 1) % animationFrames[currentState].size();
        }
    });
    animationTimer->start(100); // 每100毫秒更新一次动画帧

    headEquipment = new CapOfTheHero(this);
    legEquipment = new WellWornTrousers(this);
    armor = new OldShirt(this);
    weapon = new Ranged(this);
    headEquipment->mountToParent();
    legEquipment->mountToParent();
    armor->mountToParent();
    weapon->mountToParent();
}

QPainterPath Character::shape() const {
    QPainterPath path;
    path.addRect(collisionRect); // 使用碰撞矩形作为形状
    return path;
}

Character::~Character() {
    delete animationTimer;
}

// 游戏过程：输入控制
bool Character::isLeftDown() const {
    return leftDown;
}

void Character::setLeftDown(bool leftDown) {
    Character::leftDown = leftDown;
}

bool Character::isRightDown() const {
    return rightDown;
}

void Character::setRightDown(bool rightDown) {
    Character::rightDown = rightDown;
}

bool Character::isAttackDown() const {
    return attackDown;
}

void Character::setAttackDown(bool attackDown) {
    Character::attackDown = attackDown;
}

bool Character::isJumpDown() const {
    return jumpDown;
}

void Character::setJumpDown(bool jumpDown) {
    Character::jumpDown = jumpDown;
}

bool Character::isPickDown() const {
    return pickDown;
}

void Character::setPickDown(bool pickDown) {
    Character::pickDown = pickDown;
}

bool Character::isGuardDown() const {
    return guardDown;
}

void Character::setGuardDown(bool guardDown) {
    Character::guardDown = guardDown;
}

// 游戏过程：状态与属性设置
const QPointF &Character::getVelocity() const {
    return velocity;
}

void Character::setVelocity(const QPointF &velocity) {
    Character::velocity = velocity;
}

// 游戏过程：动作逻辑
void Character::processInput() {

    // 镜像判断
    if(isOnTheRight)
    {
        qreal imgWidth = boundingRect().width();
        setTransform(QTransform().scale(-1, 1).translate(-imgWidth, 0));
    }
    else
    {
        setTransform(QTransform().scale(1, 1));
    }

    if(attacking) {
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        if (currentTime - attackStartTime >= attackDuration) {
            // 远程武器设计为一定时间的前摇，如果攻击动作结束，发射子弹
            if (weapon->weaponID >= 3 && weapon->weaponID <= 5) {
                // 计算发射位置（角色前方，避免与自身重叠）
                QPointF firePos = this->pos();
                if (isOnTheRight) {
                    firePos.setX(firePos.x());
                } else {
                    firePos.setX(firePos.x() + boundingRect().width());
                }
                firePos.setY(firePos.y() + boundingRect().height()/3);

                qDebug() << "Character发射子弹：weaponID=" << weapon->weaponID
                         << "，firePos=" << firePos
                         << "，isRight=" << isOnTheRight
                         << "，角色名=" << name; // 确认信号触发且参数有效

                // 发射信号，通知场景创建子弹
                emit fireBullet(weapon, firePos, isOnTheRight, name, playerID);
                weapon->ammoCapacity--; // 减少弹药数量
                qDebug() << "武器弹药剩余：" << weapon->ammoCapacity;
                if (weapon->ammoCapacity <= 0) {
                    qDebug() << "武器弹药用尽，自动切换武器为Melee";
                    delete weapon; // 删除当前武器
                    weapon = new Melee(this); // 自动切换为近战武器
                    weapon->mountToParent(); // 挂载新武器
                }
            }

            attacking = false; // 重置攻击状态
            attackLocked = false; // 解锁攻击操作
            if(lastState == guard)
            {
                setAnimationState(guard); // 如果之前是防守状态，切换回防守状态
            }
            else{
                setAnimationState(stand); // 切换回站立状态
            }
        }
        lastLeftDown = leftDown;
        lastRightDown = rightDown;
        lastAttackDown = attackDown;
        lastPickDown = pickDown;
        lastGuardDown = guardDown;
        return; // 如果还在攻击中，直接返回，不处理其他输入
    }



    if(isAttackDown() && !attackLocked && !lastAttackDown && !jumping){// 攻击操作
        attackLocked = true; // 锁定攻击操作，避免连击
        attacking = true; // 设置攻击状态
        attackStartTime = QDateTime::currentMSecsSinceEpoch(); // 记录攻击开始时间
        auto velocity = QPointF(0,0); // 速度两个分量重置为0
        lastState = currentState; // 记录上一个状态

        switch (weapon->weaponID) {
        case 1: // 拳头（无武器）
            attackDuration = 500;
            setAnimationState(attack_1);
            break;
        case 2: // 近战武器，要求中的小刀
            attackDuration = 500;
            setAnimationState(attack_2);
            break;
        case 3: // 远程A，要求中的实心球
            attackDuration = 800;
            setAnimationState(attack_3);
            break;
        case 4: // 远程B，要求中的步枪
            attackDuration = 300;
            setAnimationState(attack_4);
            break;
        case 5: // 远程C，要求中的狙击枪
            attackDuration = 800;
            setAnimationState(attack_5);
            break;
        default:
            break;
        }

        setVelocity(velocity); // 重置速度为0

        // 近战武器设计为一定的后摇
        if (weapon->weaponID <= 2 && isCollidingWithEachOther) { // 近战武器
            emit dealMeleeDamage(weapon->damage);
        }
    }
    else{
        auto velocity = QPointF(0,0); // 速度两个分量重置为0
        // 1.防守姿态判断
        if(guardDown && !guardLocked && !attacking && !jumping && !guarding){
            guarding = true; // 设置防守状态
            setAnimationState(guard);
        }

        if(!guardDown && guarding) { // 防守状态结束
            guarding = false; // 解除防守状态
            setAnimationState(stand); // 切换回站立状态
        }

        if(!guarding)
        {
            // 2.移动速度处理
            const auto slowSpeed = isOnIce ? 0.4 : 0.2; // 慢速移动速度
            const auto fastSpeed = isOnIce ? 0.8 : 0.4; // 快速移动速度
            const auto jumpSpeed = -1.4;

            // 2.1 竖直速度

            if(!isOnPlatform){
                jumping = true; // 处于跳跃状态
                if(currentState != jump && currentState != jumpFront && currentState != jumpBack) {\
                    qDebug() << "跳跃动画";
                    setAnimationState(jump); // 切换到跳跃动画
                }
                velocity.setY(getVelocity().y() + 0.03); // 模拟重力
            }
            else{
                velocity.setY(0);
                jumping = false; // 到达地面，跳跃状态结束
                if(currentState == jump || currentState == jumpFront || currentState == jumpBack){
                    qDebug() << "跳跃状态结束";
                    setAnimationState(stand); // 切换回站立状态
                }
            }

            if(isJumpDown() && !jumping){
                jumping =true;
                velocity.setY(jumpSpeed); // 设置竖直速度
            }

            // 2.2 水平速度
            // a.判断是否连按
            if(isLeftDown() && !lastLeftDown){
                qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
                if (currentTime - lastLeftTime < 200) { // 连按时间间隔小于200毫秒
                    isDoubleLeft = true; // 连按左键
                }
                else{
                    isDoubleLeft = false; // 重置连按状态
                }
                lastLeftTime = currentTime;
            }
            if(isRightDown() && !lastRightDown){
                qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
                if (currentTime - lastRightTime < 200) { // 连按时间间隔小于200毫秒
                    isDoubleRight = true; // 连按右键
                }
                else{
                    isDoubleRight = false; // 重置连按状态
                }
                lastRightTime = currentTime;
            }

            // b.移动动画与速度判断
            if (isLeftDown() && !leftLocked) {
                if(lastRightDown){
                    rightLocked = true; // 锁定右键
                }

                if(!isDoubleLeft){
                    if(!isOnTheRight){
                        if(jumping){
                            setAnimationState(jumpBack);
                        }
                        else {
                            setAnimationState(walkBack);
                        }
                        velocity.setX(-slowSpeed);
                    }
                    else{
                        if(jumping){
                            setAnimationState(jumpFront);
                        }
                        else {
                            setAnimationState(walkFront);
                        }
                        if(!isCollidingWithEachOther)
                        {
                            velocity.setX(-slowSpeed);
                        }
                        else{
                            velocity.setX(0); // 如果碰撞，速度为0
                        }
                    }
                }
                else{
                    if(!isOnTheRight){
                        if(jumping){
                            setAnimationState(jumpBack);
                        }
                        else {
                            setAnimationState(dashBack);
                        }
                        velocity.setX(-fastSpeed);
                    }
                    else{
                        if(jumping){
                            setAnimationState(jumpFront);
                        }
                        else {
                            setAnimationState(dashFront);
                        }
                        if(!isCollidingWithEachOther)
                        {
                            velocity.setX(-fastSpeed);
                        }
                        else{
                            velocity.setX(0); // 如果碰撞，速度为0
                        }
                    }
                }
            }


            if (isRightDown() && !rightLocked) {
                if(lastLeftDown){
                    leftLocked = true; // 锁定左键
                }

                // setTransform(QTransform().scale(1, 1));

                if(!isDoubleRight){
                    if(!isOnTheRight){
                        if(jumping){
                            setAnimationState(jumpFront);
                        }
                        else {
                            setAnimationState(walkFront);
                        }
                        if(!isCollidingWithEachOther)
                        {
                            velocity.setX(slowSpeed);
                        }
                        else{
                            velocity.setX(0); // 如果碰撞，速度为0
                        }
                    }
                    else{
                        if(jumping){
                            setAnimationState(jumpBack);
                        }
                        else {
                            setAnimationState(walkBack);
                        }
                        velocity.setX(slowSpeed);
                    }
                }
                else{
                    if(!isOnTheRight){
                        if(jumping){
                            setAnimationState(jumpFront);
                        }
                        else {
                            setAnimationState(dashFront);
                        }
                        if(!isCollidingWithEachOther)
                        {
                            velocity.setX(fastSpeed);
                        }
                        else{
                            velocity.setX(0); // 如果碰撞，速度为0
                        }
                    }
                    else{
                        if(jumping){
                            setAnimationState(jumpBack);
                        }
                        else {
                            setAnimationState(dashBack);
                        }
                        velocity.setX(fastSpeed);
                    }

                }
            }

            if (!isLeftDown() && !isRightDown() && !guarding) { // TODO:这里需要之后继续完善
                if(jumping){
                    setAnimationState(jump);
                }
                else{
                    setAnimationState(stand);
                }
            }

            // 判断是否可以解除锁定
            if(leftLocked && (!isLeftDown() || !isRightDown())) {
                leftLocked = false; // 解除左键锁定
            }
            if(rightLocked && (!isRightDown() || !isLeftDown())) {
                rightLocked = false; // 解除右键锁定
            }
        }

        setVelocity(velocity);

        // 3.拾取动作处理
        if (!lastPickDown && pickDown) { // first time pickDown
            picking = true;
        } else {
            picking = false;
        }
    }

    // 是否隐身判断
    if((guarding && isNearHighGrass) || (attacking && isNearHighGrass && lastState == guard)){
        setImageOpacity(0.0);
    }
    else{
        setImageOpacity(1.0);
    }

    lastLeftDown = leftDown;
    lastRightDown = rightDown;
    lastAttackDown = attackDown;
    lastPickDown = pickDown;
    lastGuardDown = guardDown;
}

bool Character::isPicking() const { // 发生拾取动作时后进行判断，TODO:和拾取动作处理进行耦合
    return picking;
}

void Character::setImageOpacity(qreal opacity) {
    if (pixmapItem) {
        pixmapItem->setOpacity(opacity);
    }
    if (headEquipment) {
        headEquipment->setOpacity(opacity);
    }
    if (legEquipment) {
        legEquipment->setOpacity(opacity);
    }
    if (armor) {
        armor->setOpacity(opacity);
    }
    if (weapon) {
        weapon->setOpacity(opacity);
    }
}

// 游戏过程：战斗系统
int Character::getHp() const {
    return hp;
}

int Character::getMaxHp() const {
    return maxHp;
}

QString Character::getName() const {
    return name;
}

QPixmap Character::getFacePixmap() const {
    return facePixmap;
}

void Character::changeHp(int delta) {
    hp += delta;
    if (hp <= 0) {
        hp = 0;
        setAnimationState(down); // 死亡状态
        // TODO:游戏的停止
    }
    else if (hp > 100) {
        hp = 100; // 限制最大生命值
    }
}

void Character::takeMeleeDamage(int damage) {
        changeHp(-damage); // 受到伤害
}

void Character::causeDamage(int damage, Character *target) {
    if (target) {
        target->changeHp(-damage); // 对目标造成伤害
        qDebug() << "对" << target->getName() << "造成了" << damage << "点伤害";
    }
}

// 游戏过程：护甲的拾取与丢弃
Armor *Character::pickupArmor(Armor *newArmor) {
    auto oldArmor = armor;
    // 移除旧护甲
    if (oldArmor != nullptr) {
        oldArmor->unmount();
        oldArmor->setPos(newArmor->pos());
        oldArmor->setParentItem(parentItem()); // 直接移到Scene中
    }
    // 装备新护甲
    newArmor->setParentItem(this);
    newArmor->mountToParent();
    armor = newArmor;
    return oldArmor;
}

// 游戏过程：武器的拾取与丢弃
Weapon *Character::pickupWeapon(Weapon *newWeapon){
    auto oldWeapon = weapon;
    // 移除旧武器
    if (oldWeapon != nullptr) {
        oldWeapon->unmount();
        oldWeapon->setPos(newWeapon->pos());
        oldWeapon->setParentItem(parentItem()); // 直接移到Scene中
    }
    // 装备新武器
    newWeapon->setParentItem(this);
    newWeapon->mountToParent();
    weapon = newWeapon;

    return oldWeapon;
}

// 游戏过程：动画渲染
void Character::setAnimationState(AnimationState state) {
    if(currentState == state) return;
    currentState = state;
    currentFrame = 0; // 重置当前帧索引
    return;
}

void Character::updateAnimationFrame() {
    currentFrame = (currentFrame + 1) % animationFrames[currentState].size();
    return;
}


// 非游戏过程：JSON接口
bool Character::loadFromJson(const QString &jsonPath) {
    try {
        // 1. 打开并读取文件
        QFile file(jsonPath);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "无法打开文件:" << jsonPath;
            return false;
        }

        // 2. 解析JSON
        QJsonParseError parseError;
        QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parseError);
        file.close();

        if (parseError.error != QJsonParseError::NoError) {
            qWarning() << "JSON解析错误:" << parseError.errorString()
                << "at offset:" << parseError.offset;
            return false;
        }

        if (document.isNull()) {
            qWarning() << "无效的JSON文档";
            return false;
        }

        // 3. 获取根对象
        QJsonObject jsonObject = document.object();
        if (jsonObject.isEmpty()) {
            qWarning() << "空的JSON对象";
            return false;
        }
        QJsonObject characterObject = jsonObject.value(name).toObject();
        if (characterObject.isEmpty()) {
            qWarning() << "角色" << name << "不存在于JSON中";
            return false;
        }

        // 4. 加载动画帧
        if (!characterObject.contains("animationFrames")) {
            qWarning() << "缺少animationFrames字段";
            return false;
        }

        const QJsonObject frames = characterObject["animationFrames"].toObject();
        for (auto it = frames.constBegin(); it != frames.constEnd(); ++it) {
            const AnimationState state = stringToAnimationState(it.key());
            const QJsonArray frameArray = it->toArray();

            for (const QJsonValue &frameValue : frameArray) {
                const QString framePath = frameValue.toString();
                QPixmap frame(framePath);
                if (frame.isNull()) {
                    qWarning() << "无法加载动画帧:" << framePath;
                    continue;
                }
                animationFrames[state].append(frame);
            }
        }


        // 5. 加载立绘
        if (!characterObject.contains("profilePixmap")) {
            qWarning() << "缺少profilePixmap字段";
            return false;
        }

        const QJsonObject profile = characterObject["profilePixmap"].toObject();

        // 加载面部立绘
        if (!profile.contains("face") || !facePixmap.load(profile["face"].toString())) {
            qWarning() << "无法加载面部立绘";
            return false;
        }

        // 加载小头像
        if (!profile.contains("smallProfile") || !smallPixmap.load(profile["smallProfile"].toString())) {
            qWarning() << "无法加载小头像";
            return false;
        }

        // 加载分组立绘
        if (!profile.contains("profileGroup")) {
            qWarning() << "缺少profileGroup字段";
            return false;
        }

        const QJsonObject groups = profile["profileGroup"].toObject();
        if (groups.size() != 3) {
            qWarning() << "profileGroup需要包含A/B/C三个键";
            return false;
        }

        auto loadGroup = [this](const QJsonValue &groupValue, ProfileType type) {
            const QJsonArray frameArray = groupValue.toArray();
            for (const QJsonValue &frameValue : frameArray) {
                QPixmap pixmap(frameValue.toString());
                if (pixmap.isNull()) {
                    qWarning() << "无法加载立绘帧:" << frameValue.toString();
                    continue;
                }
                profileGroup[type].append(pixmap);
            }
        };

        // 检查并加载每个组
        if (!groups.contains("A") || !groups["A"].isArray()) {
            qWarning() << "缺少或无效的A组数据";
            return false;
        }
        loadGroup(groups["A"], A);

        if (!groups.contains("B") || !groups["B"].isArray()) {
            qWarning() << "缺少或无效的B组数据";
            return false;
        }
        loadGroup(groups["B"], B);

        if (!groups.contains("C") || !groups["C"].isArray()) {
            qWarning() << "缺少或无效的C组数据";
            return false;
        }
        loadGroup(groups["C"], C);

        return true;
    }
    catch (const std::exception &e) {
        qCritical() << "加载JSON时发生异常:" << e.what();
        return false;
    }
    catch (...) {
        qCritical() << "加载JSON时发生未知异常";
        return false;
    }
}


Character::AnimationState Character::stringToAnimationState(const QString& qstr) const {
    if(qstr == "stand") return stand;
    else if(qstr == "walkFront") return walkFront;
    else if(qstr == "walkBack") return walkBack;
    else if(qstr == "dashFront") return dashFront;
    else if(qstr == "dashBack") return dashBack;
    else if(qstr == "attack_1") return attack_1;
    else if(qstr == "attack_2") return attack_2;
    else if(qstr == "attack_3") return attack_3;
    else if(qstr == "attack_4") return attack_4;
    else if(qstr == "attack_5") return attack_5;
    else if(qstr == "jump") return jump;
    else if(qstr == "jumpFront") return jumpFront;
    else if(qstr == "jumpBack") return jumpBack;
    else if(qstr == "guard") return guard;
    else if(qstr == "hit") return hit;
    else if(qstr == "down") return down;
    else return stand; // 默认返回站立状态
}
