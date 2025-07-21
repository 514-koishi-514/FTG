#ifndef HPBAR_H
#define HPBAR_H

#include <QGraphicsItem>
#include <QPainter>

class HpBar : public QGraphicsItem {
public:
    HpBar(int maxHp, QGraphicsItem* parent = nullptr);

    void setHp(int hp);
    void setMaxHp(int maxHp);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    int m_maxHp;
    int m_hp;
    int m_width = 120;
    int m_height = 24;
};

#endif // HPBAR_H
