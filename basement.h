#ifndef BASEMENT_H
#define BASEMENT_H

#include <QPoint>
#include <QRect>
#include <QPainter>
#include <QImage>

class Basement
{
public:
    Basement();

    ~Basement() = default;

    void DrawBasement(QPainter* painter, QPoint point);

    void SetBasementPace(int pace);

public:
    QRect rect_for_basement;
    QImage image_for_basement;
    int basement_pace = -4;
};

#endif // BASEMENT_H
