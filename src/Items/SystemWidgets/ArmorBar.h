#ifndef ARMORBAR_H
#define ARMORBAR_H

#include <QGraphicsItem>
#include <QPainter>

class ArmorBar : public QGraphicsItem {
public:
    ArmorBar(int maxHp, QGraphicsItem* parent = nullptr);

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


#endif // ARMORBAR_H
