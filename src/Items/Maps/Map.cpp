//
// Map.cpp
// 实现地图类的基本属性和行为
//

#include "Map.h"

Map::Map(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {}

void Map::scaleToFitScene(QGraphicsScene *scene) {
    // 计算缩放因子以使项目适合整个场景
    QRectF sceneRect = scene->sceneRect();
    QRectF itemRect = boundingRect();

    qreal scaleX = sceneRect.width() / itemRect.width();
    qreal scaleY = sceneRect.height() / itemRect.height();

    // 选择较小的缩放因子以保持纵横比
    qreal scaleFactor = qMin(scaleX, scaleY);

    // 将缩放应用到item
    setTransform(QTransform::fromScale(scaleFactor, scaleFactor), true);

    // 在场景中居中项目（可选）
    setPos((sceneRect.width() - boundingRect().width() * scaleFactor) / 2,
           (sceneRect.height() - boundingRect().height() * scaleFactor) / 2);

}

// 获取生成位置
QPointF Map::getSpawnPos() {
    auto boundingRect = sceneBoundingRect();
    auto midX = (boundingRect.left() + boundingRect.right()) * 0.5;
    return {midX, getFloorHeight()};
}

// 获取地板高度（需要重写以支持多个平台）
qreal Map::getFloorHeight() {
    auto sceneRect = sceneBoundingRect();
    return sceneRect.top() + (sceneRect.top() - sceneRect.bottom()) * 0.5;
}
