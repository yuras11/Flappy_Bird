#ifndef BASEMENT_H
#define BASEMENT_H

#include <QPoint>
#include <QRect>
#include <QPainter>
#include <QImage>

class Basement
{
public:

    Basement(QPoint point_for_basement);

    ~Basement() = default;

    void DrawBasement(QPainter* painter, QImage image);

public:
    QRect rect_for_basement;
};

#endif // BASEMENT_H
