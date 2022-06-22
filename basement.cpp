#include "basement.h"

Basement::Basement(): image_for_basement("C:/Users/Yuriy Kozlov/Documents/flappybird/basement.png"), basement_pace(-4)
{
    for(int i = 0; i < 2; i++)
    {
         QPoint point(i*800, 550);
         points_for_basement.push_back(point);
    }
}

void Basement::DrawBasement(QPainter* painter)
{
    for(int i = 0; i < points_for_basement.size(); i++)
    {
        rect_for_basement.setX(points_for_basement[i].x());
        rect_for_basement.setY(550);
        rect_for_basement.setWidth(810);
        rect_for_basement.setHeight(100);

        painter->drawImage(rect_for_basement, image_for_basement);
    }
}

void Basement::MoveBasement()
{
    for(int i = 0; i < points_for_basement.size(); i++)
    {
        points_for_basement[i].setX(points_for_basement[i].x() + basement_pace);
        if(points_for_basement[i].x()+800 <= 0)
        {
            points_for_basement[i].setX(790);
        }
    }
}

void Basement::SetBasementPace(int pace)
{
    basement_pace = -pace;
}
