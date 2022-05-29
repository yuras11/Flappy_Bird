#include "basement.h"

Basement::Basement(QPoint point_for_basement)
{
    rect_for_basement.setX(point_for_basement.x());
    rect_for_basement.setY(550);
    rect_for_basement.setWidth(805);
    rect_for_basement.setHeight(100);
}

void Basement::DrawBasement(QPainter* painter, QImage image)
{
    painter->drawImage(rect_for_basement, image);
}
