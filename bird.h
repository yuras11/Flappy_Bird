#ifndef BIRD_H
#define BIRD_H

#include <QPoint>
#include <QPainter>
#include <QBrush>
#include <QRect>
#include <QImage>
#include <vector>

class Bird
{
public:
    Bird();

    ~Bird() = default;

    void DrawBird(QPainter *painter);

    void BirdAnimation();

    void SetBirdImages(std::vector<QImage> &skins);

    void SetBirdPaceOfFall(int pace);

    void SetHeightOfJump(int height);

public:
    std::vector<QImage> bird_images;
    QPoint point_for_bird;
    QImage main_image;
    int radius = 25;
    int index = 0;
    int height_of_jump = -10;
    int bird_pace = -10;
    int bird_pace_of_fall = 1;
    int starting_bird_pace = -2;
};

#endif // BIRD_H
