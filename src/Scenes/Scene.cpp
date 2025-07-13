//
// Scene.cpp
// 游戏场景的抽象基类实现
//

#include <QDateTime>
#include "Scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent), timer(new QTimer(this)) {
    connect(timer, &QTimer::timeout, this, &Scene::update);
}

// 在每帧更新时计算时间差
void Scene::update() {
    auto currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if (lastTime == -1) { // first frame
        deltaTime = 0;
    } else {
        deltaTime = currentTime - lastTime;
    }
    lastTime = currentTime;

    processInput();
    processMovement();
    processCollision();
    processPicking();
}

void Scene::startLoop() {
    timer->start(1000 / 90); // 90FPS
}

// 下面是虚函数，在派生类中被重写
void Scene::processInput() {

}

void Scene::processMovement() {

}

void Scene::processPicking() {

}

void Scene::processCollision(){

}
