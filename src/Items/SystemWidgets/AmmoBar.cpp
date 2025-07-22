#include "AmmoBar.h"

AmmoBar::AmmoBar(int maxQuantity, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_maxQuantity(maxQuantity), m_quantity(maxQuantity) {}

void AmmoBar::setQuantity(int Quantity) {
    m_quantity = qBound(0, Quantity, m_maxQuantity);
    update();
}

void AmmoBar::setMaxQuantity(int maxQuantity) {
    m_maxQuantity = maxQuantity;
    m_quantity = qMin(m_quantity, m_maxQuantity);
    update();
}

QRectF AmmoBar::boundingRect() const {
    return QRectF(0, 0, m_width, m_height);
}

void AmmoBar::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    // Draw white background
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::gray);
    painter->drawRect(0, 0, m_width, m_height);

    // Draw green foreground
    if (m_maxQuantity > 0) {
        int barWidth = static_cast<int>(m_width * (double)m_quantity / m_maxQuantity);
        painter->setBrush(QColor(255, 165, 0));
        painter->drawRect(0, 0, barWidth, m_height);
    }

    // Draw Quantity text
    painter->setPen(Qt::black);
    painter->setFont(QFont("Arial", 8));
    QString QuantityText = QString("%1/%2").arg(m_quantity).arg(m_maxQuantity);
    painter->drawText(QRect(0, 0, m_width, m_height), Qt::AlignCenter, QuantityText);
}
