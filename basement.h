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

    void DrawBasement(QPainter* painter);

    void MoveBasement();

    void SetBasementPace(int pace);

public:
    std::vector<QPoint> points_for_basement;
    QRect rect_for_basement;
    QImage* image_for_basement;
    int basement_pace;
};

#endif // BASEMENT_H
