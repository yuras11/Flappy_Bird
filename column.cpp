#include "column.h"

void Column::DrawColumn(QPainter *painter, QPoint point, QImage lower_image, QImage upper_image)
{
     upper_column.setX(point.x()-25);
     upper_column.setY(point.y()-upper_image.height());
     upper_column.setHeight(upper_image.height()-50);
     upper_column.setWidth(70);

     lower_column.setX(point.x()-25);
     lower_column.setY(point.y()+70);
     lower_column.setHeight(lower_image.height());
     lower_column.setWidth(70);

     painter->drawImage(upper_column, upper_image);
     painter->drawImage(lower_column, lower_image);
}

void Column::SetColumnPace(int pace)
{
    column_pace = -pace;
}
