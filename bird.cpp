#include "bird.h"

Bird::Bird(): point_for_bird(200, 300)
{
    QImage first_image("C:/Users/Yuriy Kozlov/Documents/flappybird/bird_pictures/yellow_bird/first.png");
    bird_images.push_back(first_image);
    bird_images.push_back(first_image);
    bird_images.push_back(first_image);
    QImage second_image("C:/Users/Yuriy Kozlov/Documents/flappybird/bird_pictures/yellow_bird/second.png");
    bird_images.push_back(second_image);
    bird_images.push_back(second_image);
    bird_images.push_back(second_image);
    QImage third_image("C:/Users/Yuriy Kozlov/Documents/flappybird/bird_pictures/yellow_bird/third.png");
    bird_images.push_back(third_image);
    bird_images.push_back(third_image);
    bird_images.push_back(third_image);
    QImage forth_image("C:/Users/Yuriy Kozlov/Documents/flappybird/bird_pictures/yellow_bird/forth.png");
    bird_images.push_back(forth_image);
    bird_images.push_back(forth_image);
    bird_images.push_back(third_image);

    main_image = bird_images[0];
}

void Bird::DrawBird(QPainter *painter)
{
    painter->drawImage(point_for_bird, main_image);
}

void Bird::BirdAnimation()
{
    index = (index + 1) % 12;
    main_image = bird_images[index];
}

void Bird::SetBirdImages(std::vector<QImage> &skins)
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
