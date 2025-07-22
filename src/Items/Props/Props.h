#ifndef PROPS_H
#define PROPS_H

#include "../Item.h"

enum class PropsType {
    BandageHeal,
    MedkitHeal,
    AdrenalineHeal
};

class Props : public Item {
    Q_OBJECT
public:
    explicit Props(QGraphicsItem *parent, const QString &pixmapPath);

    int cureOnce = 0;

    int cureTimes = 0;

    bool isLastingEffect = false;

signals:
    void cure(int cureOnce, int cureTimes);
};

#endif // PROPS_H
