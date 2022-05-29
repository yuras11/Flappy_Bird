#ifndef COLUMN_H
#define COLUMN_H

#include <QRect>
#include <QPainter>

class Column
{
public:
    Column(QPoint column_point);

    ~Column() = default;

    void DrawColumn(QPainter *painter, QImage lower_image, QImage upper_image);

private:
    QRect higher_rect;
    QRect lower_rect;
};

#endif // COLUMN_H
