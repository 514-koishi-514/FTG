//
// 头文件Scene.h
// 游戏场景的抽象基类
//

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>

class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit Scene(QObject *parent);

    void startLoop();

    virtual void processInput();

    virtual void processMovement();

    virtual void processPicking();

    virtual void processCollision();

protected slots:

    // 在每帧更新时计算时间差
    virtual void update();

protected:
    qint64 deltaTime{};

private:
    QTimer *timer;
    qint64 lastTime{-1};
};


#endif //SCENE_H
