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

    void SetBirdImages(std::vector<QString> &skins);

    void SetBirdPaceOfFall(int pace);

    void SetHeightOfJump(int height);

    void SetStartingBirdCoordinates();

    void MoveBird();

    void MoveBirdBeforeStartingTheGame();

public:
    std::vector<QString> bird_images;
    QPoint point_for_bird;
    QString main_image;
    int radius;
    int index;
    int height_of_jump;
    int bird_pace;
    int bird_pace_of_fall;
    int starting_bird_pace;
};

#endif // BIRD_H
