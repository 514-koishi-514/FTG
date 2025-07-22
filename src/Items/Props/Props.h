#ifndef PROPS_H
#define PROPS_H

#include "../Item.h"

class Props : public Item {
    Q_OBJECT
public:
    explicit Props(QGraphicsItem *parent, const QString &pixmapPath);

    int cureOnce = 0;

    int cureTimes = 0;

signals:
    void cure(int cureOnce, int cureTimes);
};

#endif // PROPS_H
