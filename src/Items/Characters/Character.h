//
// 头文件Character.h
// 角色基类，用来管理角色的立绘、运动、装备、动画等
//

#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsEllipseItem>
#include <QFile>
#include <QJsonObject>
#include "../HeadEquipments/HeadEquipment.h"
#include "../Armors/Armor.h"
#include "../LegEquipments/LegEquipment.h"

class Character : public Item {
public:
    explicit Character(QGraphicsItem *parent, const QString& name);
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
    [[nodiscard]] const QPointF &getVelocity() const;
    [[nodiscard]] bool isPicking() const;

    void setVelocity(const QPointF &velocity);

    // 游戏过程：动作逻辑
    void processInput();

    Armor* pickupArmor(Armor* newArmor);

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
    QMap<AnimationState, QVector<QPixmap>> animationFrames; // 动画帧集合
    int currentFrame = 0; // 当前帧索引
    QTimer *animationTimer; // 动画定时器

    void setAnimationState(AnimationState state);

    // 游戏过程：状态与属性
    bool isOnIce = false; // 是否在冰上
    bool isOnPlatform = true; // 是否在平台上
    bool isOnTheRight = true; // 是否相对在右面
    bool isCollidingWithEachOther = false; // 是否与其他角色碰撞

    // 非游戏过程：JSON接口
    bool loadFromJson(const QString &json);

    // 辅助函数：QString转换AnimationState
    AnimationState stringToAnimationState(const QString &qstr) const;

protected:
    // 装备系统
    int weaponType = 5; // 武器类型，TODO:武器类型4是否可以连击？
    HeadEquipment *headEquipment{};
    LegEquipment *legEquipment{};
    Armor *armor{};
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
};


#endif //CHARACTER_H
