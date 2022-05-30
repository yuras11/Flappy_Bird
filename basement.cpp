#include "basement.h"

Basement::Basement(): image_for_basement("C:/Users/Yuriy Kozlov/Documents/flappybird/basement.png"){}

void Basement::DrawBasement(QPainter* painter, QPoint point)
{
    rect_for_basement.setX(point.x());
    rect_for_basement.setY(550);
    rect_for_basement.setWidth(810);
    rect_for_basement.setHeight(100);

    painter->drawImage(rect_for_basement, image_for_basement);
}

void Basement::SetBasementPace(int pace)
{
    basement_pace = -pace;
}
