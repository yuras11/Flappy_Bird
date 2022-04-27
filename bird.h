#ifndef BIRD_H
#define BIRD_H

#include <QPoint>
#include <QPainter>
#include <QBrush>
#include <QRect>
class Bird
{
public:
    Bird(QPoint point_for_bird);

    void DrawBird(QPainter *painter, QPoint point, QImage image);

    QRect rect;

    int radius = 25;
};

#endif // BIRD_H
