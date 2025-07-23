//
// 头文件Character.h
// 角色基类，用来管理角色的立绘、运动、装备、动画等
//

#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsEllipseItem>
#include <QFile>
#include <QJsonObject>
#include "../Armors/Armor.h"
#include "../Weapons/Weapon.h"
#include "../Props/Props.h"

class Character : public Item {
    Q_OBJECT

public:
    explicit Character(QGraphicsItem *parent, const QString& name, const int &playerID);
    ~Character();

    // 游戏过程：输入控制
    [[nodiscard]] bool isLeftDown() const;
    void setLeftDown(bool leftDown);


    [[nodiscard]] bool isRightDown() const;
    void setRightDown(bool rightDown);


    [[nodiscard]] bool isAttackDown() const;
    void setAttackDown(bool attackDown);


    [[nodiscard]] bool isJumpDown() const;
    void setJumpDown(bool jumpDown);


    [[nodiscard]] bool isPickDown() const;
    void setPickDown(bool SDown);

    [[nodiscard]] bool isGuardDown() const;
    void setGuardDown(bool guardDown);

    // 游戏过程：状态与属性设置
    [[nodiscard]] bool isPicking() const;

    // 游戏过程：动作逻辑
    void processInput();

    Armor* pickupArmor(Armor* newArmor);
    Weapon* pickupWeapon(Weapon* newWeapon);
    void pickupProps(Props *newProps);

    // 游戏过程：动画与渲染

    enum ProfileType {
        A,B,C
    };
    enum AnimationState {
        stand,
        walkFront, walkBack,
        dashFront, dashBack,
        attack_1, attack_2, attack_3, attack_4, attack_5,
        jump, jumpFront, jumpBack,
        guard,
        hit,
        down
    };
    AnimationState currentState = stand; // 当前动画状态
    AnimationState lastState = stand; // 上一个动画状态
    QMap<AnimationState, QVector<QPixmap>> animationFrames; // 动画帧集合
    int currentFrame = 0; // 当前帧索引
    QTimer *animationTimer; // 动画定时器

    void setAnimationState(AnimationState state);

    // 游戏过程：状态与属性
    bool isOnIce = false; // 是否在冰上
    bool isNearHighGrass = false; // 是否在高草丛附近
    bool isOnPlatform = true; // 是否在平台上
    bool isOnTheRight = true; // 是否相对在右面
    bool isCollidingWithEachOther = false; // 是否与其他角色碰撞

    const QRectF collisionRect = QRectF(35, 15, 50, 105); // 碰撞矩形
    QPainterPath shape() const override;

    void setImageOpacity(qreal opacity);

    // 游戏过程：战斗系统

    int getHp() const;

    int getMaxHp() const;

    ArmorType getArmorType() const;

    int getArmor() const;

    int getMaxArmor() const;

    int getAmmoQuantity() const;

    int getMaxAmmoQuantity() const;

    QString getName() const;

    void changeHp(int delta);

    void changeArmorHp(int delta);

    void causeDamage(int damage, Character *target = nullptr);

    int remainingHealTimes = 0;
    int currentHealAmount = 0;

    // 非游戏过程：JSON接口
    bool loadFromJson(const QString &json);

    // 辅助函数：QString转换AnimeationState
    AnimationState stringToAnimationState(const QString &qstr) const;

    // 非游戏过程：获取角色立绘
    QPixmap getFacePixmap() const;

protected:
    int playerID; // 玩家ID，1或2
    // 装备系统
    Armor *armor{};
    Weapon *weapon{};
    // 运动系统protected
    QPointF velocity{};

    // 自身属性
    QString name; // 角色名称
    QPixmap facePixmap; //角色形象立绘
    QPixmap smallPixmap; //角色小立绘
    QMap<ProfileType, QVector<QPixmap>> profileGroup; //静态立绘组

    // 配置文件
    QString configFilePath; // JSON配置文件路径


    //    QGraphicsEllipseItem *ellipseItem; // for debugging

    // 游戏过程：更新动画状态槽函数
protected slots:
    void updateAnimationFrame();

    // 运动系统private
private:
    bool leftDown{}, rightDown{}, attackDown{}, jumpDown{}, pickDown{}, guardDown{}; // 按键状态
    bool leftLocked{}, rightLocked{}, attackLocked{}, jumpLocked{}, pickLocked{}, guardLocked{};   // 锁定状态，保证优先级
    bool lastLeftDown{}, lastRightDown{}, lastAttackDown{}, lastPickDown{}, lastGuardDown{};   // 上一按键状态
    bool leftMoving{}, rightMoving{}, attacking{}, jumping{}, picking{}, guarding{};    // 动作状态

    qint64 lastLeftTime{}, lastRightTime{}; // 上一次按键按下时间
    bool isDoubleLeft{}, isDoubleRight{}; // 是否双击状态

    qint64 attackStartTime{}; // 攻击开始时间;
    qint64 attackDuration = 500; // 攻击持续时间(ms)

    QTimer* healingTimer; // 治疗定时器

    // 战斗相关
    int hp = 100; // 生命值
    int maxHp = 100; // 最大生命值

signals:
    // 发射信号：武器类型、发射位置、角色朝向
    void fireBullet(Weapon* weapon, const QPointF& firePos, bool isRight, const QString &fromCharacterName = QString(), const int &playerID = 1);

    void dealMeleeDamage(int damage, int weaponID);

public slots:
    void takeMeleeDamage(int damage, int attackWeaponID);

    void onHealTimerTimeout();
};


#endif //CHARACTER_H
