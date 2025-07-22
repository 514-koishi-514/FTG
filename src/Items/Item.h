//
// 头文件Item.h
// 游戏的（空）可见物基类
//

#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsObject>
#include <QPainter>

class Item : public QGraphicsObject{
    Q_OBJECT
public:
    explicit Item(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] QRectF boundingRect() const override {
        if (pixmapItem != nullptr) {
            return this->pixmapItem->boundingRect();
        }
        return {};
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override {
        // 不会绘制，因为为空
        // 具体由子类实现
    }

    QPointF getVelocity() const {
        return velocity;
    }

    QPointF setVelocity(const QPointF &newVelocity) {
        velocity = newVelocity;
        return velocity;
    }

protected:
    QPointF velocity{};

    QGraphicsPixmapItem *pixmapItem{};
};


#endif //ITEM_H
