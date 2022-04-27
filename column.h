#ifndef COLUMN_H
#define COLUMN_H

#include <QRect>
#include <QPainter>
#include <QBrush>

class Column
{
public:
    Column(QPoint column_point);

    void DrawColumn(QPainter *painter, QPoint point, QImage lower_image, QImage upper_image);

    QRect higher_rect;
    QRect lower_rect;
};

#endif // COLUMN_H
