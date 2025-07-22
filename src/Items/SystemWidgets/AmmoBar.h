#ifndef AMMOBAR_H
#define AMMOBAR_H

#include <QGraphicsItem>
#include <QPainter>

class AmmoBar : public QGraphicsItem {
public:
    AmmoBar(int maxQuantity, QGraphicsItem* parent = nullptr);

    void setQuantity(int quantity);
    void setMaxQuantity(int maxQuantity);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    int m_maxQuantity;
    int m_quantity;
    int m_width = 120;
    int m_height = 24;
};

#endif // AMMOBAR_H
