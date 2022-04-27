#include "flappybird.h"
#include "./ui_flappybird.h"

#include <bird.h>

FlappyBird::FlappyBird(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlappyBird)
    , point_for_bird(100, 300)
{
    std::random_device rdGen;
    std::mt19937 gen(rdGen());
    std::uniform_int_distribution<> dis0_15(70, this->height() - 70);

    int distance = -50;

    for(int i = 0; i < 4; i++)
    {
        QPoint point(this->width() + distance,dis0_15(gen));
        points.push_back(point);
        distance += 300;
    }

    QTimer* ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), SLOT(MoveColumn()));
    connect(ptimer, SIGNAL(timeout()), SLOT(MoveBird()));
    ptimer->start(25);

    ui->setupUi(this);
}

void FlappyBird::MoveColumn()
{
    std::random_device rdGen;
    std::mt19937 gen1(rdGen());
    std::uniform_int_distribution<> dis0_15(70, this->height() - 70);
    for(int i = 0; i < points.size(); i++)
    {
        points[i].setX(points[i].x() + x_column_pace);
        if(points[i].x() + 50 <= 0)
        {
            points[i].setX(this->width() + 400);
            points[i].setY(dis0_15(gen1));
        }
    }
   this->update();
}

void FlappyBird::MoveBird()
{
    point_for_bird.setY(point_for_bird.y() + bird_pace);
    bird_pace++;

    if(point_for_bird.y() + radius < 0 || point_for_bird.y() + radius > this->height())
    {
        bird_pace = 0;
        x_column_pace = 0;
    }

//    for(int i = 0; i < points.size(); i++)
//    {
//        if(point_for_bird.x()+radius == points[i].x()+25)
//        {
//            if(point_for_bird.y()+radius <= points[i].y() || point_for_bird.y()+radius >= points[i].y()+70)
//            {
//                bird_pace = 0;
//                x_column_pace = 0;
//            }
//        }
//    }

    this->update(); 
}

void FlappyBird::paintEvent(QPaintEvent *event)
{
    Column first_column(this->points[0]);
    Column second_column(this->points[1]);
    Column third_column(this->points[2]);
    Column forth_column(this->points[3]);

    Bird bird(point_for_bird);

    QPainter painter(this);
    QImage background("C:/Users/Yuriy Kozlov/Documents/flappybird/1616033040_2-p-fon-flappy-bird-3.png", "PNG");
    QBrush background_brush(background);
    painter.fillRect(0, 0, this->width(), this->height(), background_brush);

    QImage lower_image("C:/Users/Yuriy Kozlov/Documents/flappybird/lower-pipe-green.png");
    QImage upper_image("C:/Users/Yuriy Kozlov/Documents/flappybird/pipe-green.png");
    first_column.DrawColumn(&painter, points[0], lower_image, upper_image);
    second_column.DrawColumn(&painter, points[1], lower_image, upper_image);
    third_column.DrawColumn(&painter, points[2], lower_image, upper_image);
    forth_column.DrawColumn(&painter, points[3], lower_image, upper_image);

    QImage bird_image("C:/Users/Yuriy Kozlov/Documents/flappybird/bluebird-downflap.png");

    bird.DrawBird(&painter, point_for_bird, bird_image);
}

void FlappyBird::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        x_column_pace = -4;
        bird_pace = -10;
    }
}

void FlappyBird::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
       //bird_pace = 0;
    }
}

FlappyBird::~FlappyBird()
{
    delete ui;
}
