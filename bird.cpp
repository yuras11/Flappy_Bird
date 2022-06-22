#include "bird.h"

Bird::Bird(): point_for_bird(200, 300)
{
    QString fileName("C:/Users/Yuriy Kozlov/Documents/flappybird/bird_pictures/yellow_bird/first.png");
    bird_images.push_back(fileName);
    fileName = "C:/Users/Yuriy Kozlov/Documents/flappybird/bird_pictures/yellow_bird/second.png";
    bird_images.push_back(fileName);
    fileName = "C:/Users/Yuriy Kozlov/Documents/flappybird/bird_pictures/yellow_bird/third.png";
    bird_images.push_back(fileName);
    fileName = "C:/Users/Yuriy Kozlov/Documents/flappybird/bird_pictures/yellow_bird/forth.png";
    bird_images.push_back(fileName);

    main_image = fileName;
}

void Bird::DrawBird(QPainter *painter)
{
    QImage main_image(this->main_image);
    painter->drawImage(point_for_bird, main_image);
}

void Bird::BirdAnimation()
{
    index = (index + 1) % bird_images.size();

    main_image = bird_images[index];
}

void Bird::SetBirdImages(std::vector<QString> &skins)
{
    bird_images = skins;
}

void Bird::SetBirdPaceOfFall(int pace)
{
   bird_pace_of_fall = pace;
}

void Bird::SetHeightOfJump(int height)
{
    height_of_jump = -height;
}

void Bird::MoveBird()
{
    point_for_bird.setY(point_for_bird.y() + bird_pace);
    bird_pace += bird_pace_of_fall;
}

void Bird::MoveBirdBeforeStartingTheGame()
{
    point_for_bird.setY(point_for_bird.y() + starting_bird_pace);
    if(point_for_bird.y() <= 285 || point_for_bird.y() >= 315)
    {
        starting_bird_pace = -starting_bird_pace;
    }
}
