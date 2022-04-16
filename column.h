#ifndef COLUMN_H
#define COLUMN_H

#include <QRect>
#include <QPainter>
#include <QBrush>

class Column
{
public:
    Column(QPoint column_point);

    void DrawColumn(QPainter *painter, QBrush upper_brush, QBrush lower_brush);

    QRect higher_rect;
    QRect lower_rect;
    
private:
    QPoint column_point;
};

#endif // COLUMN_H
