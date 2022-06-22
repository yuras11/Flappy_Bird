#ifndef COLUMN_H
#define COLUMN_H

#include "bird.h"

#include <QRect>
#include <QPainter>
#include <random>

class Column
{
public:
    Column();

    ~Column() = default;

    void DrawColumns(QPainter *painter);

    void SetColumnPace(int pace);

    void MoveColumn();

    bool IntersectionHappened(Bird &bird);

public:
    std::vector<QPoint> points_for_columns;
    std::vector<QImage> column_pictures;
    QRect upper_column, lower_column;
    int column_pace;
    int distance;
};

#endif // COLUMN_H
