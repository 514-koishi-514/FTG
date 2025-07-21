#include "HpBar.h"

HpBar::HpBar(int maxHp, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_maxHp(maxHp), m_hp(maxHp) {}

void HpBar::setHp(int hp) {
    m_hp = qBound(0, hp, m_maxHp);
    update();
}

void HpBar::setMaxHp(int maxHp) {
    m_maxHp = maxHp;
    m_hp = qMin(m_hp, m_maxHp);
    update();
}

QRectF HpBar::boundingRect() const {
    return QRectF(0, 0, m_width, m_height);
}

void HpBar::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    // Draw white background
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawRect(0, 0, m_width, m_height);

    // Draw green foreground
    if (m_maxHp > 0) {
        int barWidth = static_cast<int>(m_width * (double)m_hp / m_maxHp);
        painter->setBrush(Qt::green);
        painter->drawRect(0, 0, barWidth, m_height);
    }

    // Draw HP text
    painter->setPen(Qt::black);
    painter->setFont(QFont("Arial", 8));
    QString hpText = QString("%1/%2").arg(m_hp).arg(m_maxHp);
    painter->drawText(QRect(0, 0, m_width, m_height), Qt::AlignCenter, hpText);
}
