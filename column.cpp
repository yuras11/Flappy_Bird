#include "column.h"

Column::Column(QPoint column_point)
{
    higher_rect.setX(column_point.x()-25);
    higher_rect.setY(column_point.y()-747);
    higher_rect.setWidth(70);
    higher_rect.setHeight(697);

    lower_rect.setX(column_point.x()-25);
    lower_rect.setY(column_point.y()+70);
    lower_rect.setWidth(70);
    lower_rect.setHeight(547);
}

void Column::DrawColumn(QPainter *painter, QImage lower_image, QImage upper_image)
{
     painter->drawImage(higher_rect, upper_image);
     painter->drawImage(lower_rect, lower_image);
}
