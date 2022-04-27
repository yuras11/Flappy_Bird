#include "column.h"

Column::Column(QPoint column_point)
{
    higher_rect.setX(column_point.x() - 25);
    higher_rect.setY(0);
    higher_rect.setWidth(70);
    higher_rect.setHeight(column_point.y()-50);

    lower_rect.setX(column_point.x()-25);
    lower_rect.setY(column_point.y() + 70);
    lower_rect.setWidth(70);
    lower_rect.setHeight(1000);
}

void Column::DrawColumn(QPainter *painter, QPoint point, QImage lower_image, QImage upper_image)
{
     painter->drawImage(this->higher_rect, upper_image);
     painter->drawImage(this->lower_rect, lower_image);
}
