#include "column.h"

Column::Column(QPoint column_point)
{
    higher_rect.setX(column_point.x() - 25);
    higher_rect.setY(0);
    higher_rect.setWidth(70);
    higher_rect.setHeight(column_point.y()-50);

    lower_rect.setX(column_point.x()-25);
    lower_rect.setY(column_point.y() + 50);
    lower_rect.setWidth(70);
    lower_rect.setHeight(1000);
}

void Column::DrawColumn(QPainter *painter, QBrush upper_brush, QBrush lower_brush)
{
    painter->drawRect(this->higher_rect);
    painter->fillRect(this->higher_rect, upper_brush);
    painter->drawRect(this->lower_rect);
    painter->fillRect(this->lower_rect, lower_brush);
}
