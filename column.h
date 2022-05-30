#ifndef COLUMN_H
#define COLUMN_H

#include <QRect>
#include <QPainter>

class Column
{
public:
    Column() = default;

    ~Column() = default;

    void DrawColumn(QPainter *painter, QPoint point, QImage lower_image, QImage upper_image);

    void SetColumnPace(int pace);

public:
    QRect upper_column, lower_column;
    int column_pace = -4;
};

#endif // COLUMN_H
