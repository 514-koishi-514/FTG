//
// MyGame.cpp
// 实现游戏主窗口和场景、视图的初始化
//
#include "MyGame.h"
#include "Scenes/BattleScene.h"

MyGame::MyGame(QWidget *parent) : QMainWindow(parent) {
    battleScene = new BattleScene(this);
    view = new QGraphicsView(this);
    view->setScene(battleScene);
    // 设置窗口尺寸为场景的大小
    view->setFixedSize((int) view->scene()->width(), (int) view->scene()->height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    setCentralWidget(view);
    // 调整窗口大小来涵盖视图
    setFixedSize(view->sizeHint());
    battleScene->startLoop(); // 开始游戏循环
}
