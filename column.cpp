#include "column.h"

Column::Column(): distance(-50), column_pace(-4)
{
    QImage lower_image("C:/Users/Yuriy Kozlov/Documents/flappybird/lower-pipe-green.png");
    column_pictures.push_back(lower_image);
    QImage upper_image("C:/Users/Yuriy Kozlov/Documents/flappybird/pipe-green.png");
    column_pictures.push_back(upper_image);

    distance = -50;
    std::random_device rdGen;
    std::mt19937 gen(rdGen());
    std::uniform_int_distribution<> dis0_15(70, 410);
    for(int i = 0; i < 4; i++)
    {
        QPoint point(1600 + distance, dis0_15(gen));
        points_for_columns.push_back(point);
        distance += 300;
    }
}

void Column::DrawColumns(QPainter *painter)
{
    for(int i = 0; i < points_for_columns.size(); i++)
    {
        upper_column.setX(points_for_columns[i].x()-25);
        upper_column.setY(points_for_columns[i].y()-column_pictures[1].height());
        upper_column.setHeight(column_pictures[1].height()-50);
        upper_column.setWidth(70);

        lower_column.setX(points_for_columns[i].x()-25);
        lower_column.setY(points_for_columns[i].y()+70);
        lower_column.setHeight(column_pictures[0].height());
        lower_column.setWidth(70);

        painter->drawImage(upper_column, column_pictures[1]);
        painter->drawImage(lower_column, column_pictures[0]);
    }
}

void Column::SetColumnPace(int pace)
{
    column_pace = -pace;
}

void Column::MoveColumn()
{
    std::random_device rdGen;
    std::mt19937 gen1(rdGen());
    std::uniform_int_distribution<> dis0_15(70, 410);
    for(int i = 0; i < points_for_columns.size(); i++)
    {
        points_for_columns[i].setX(points_for_columns[i].x() + column_pace);
        if(points_for_columns[i].x() + 50 <= 0)
        {
            points_for_columns[i].setX(800 + 400);
            points_for_columns[i].setY(dis0_15(gen1));
        }
    }
}

void Column::SetStartingColumnCoordinates()
{
    distance = -50;
    std::random_device rdGen;
    std::mt19937 gen(rdGen());
    std::uniform_int_distribution<> dis0_15(70, 410);
    for(int i = 0; i < 4; i++)
    {
        points_for_columns[i].setX(1600 + distance);
        points_for_columns[i].setY(dis0_15(gen));
        distance += 300;
    }
}

bool Column::IntersectionHappened(const Bird &bird)
{
    for(int i = 0; i < points_for_columns.size(); i++)
    {
        if(bird.point_for_bird->x()+bird.radius >= points_for_columns[i].x()-25 &&
           bird.point_for_bird->x() <= points_for_columns[i].x()+45 &&
           (bird.point_for_bird->y()+bird.radius <= points_for_columns[i].y()-25 ||
            bird.point_for_bird->y()+bird.radius >= points_for_columns[i].y()+70))
        {
            return true;
        }
    }
    return false;
}

void Column::SetColumnPictures(const std::vector<QImage> &images)
{
    column_pictures = images;
}
