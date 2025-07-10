//
// 头文件MyGame.h
// 用来定义游戏的主窗口和场景、视图
//

#ifndef MYGAME_H
#define MYGAME_H

#include <QGraphicsView>
#include <QMainWindow>
#include "Scenes/Scene.h"

class MyGame : public QMainWindow {
Q_OBJECT

public:
    // 初始化
    explicit MyGame(QWidget *parent = nullptr);

private:
    Scene *battleScene;
    QGraphicsView *view;
};


#endif //MYGAME_H
