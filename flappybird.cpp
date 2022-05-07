#include "flappybird.h"
#include "./ui_flappybird.h"

FlappyBird::FlappyBird(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlappyBird)
    , point_for_bird(100, 300)
{
    phrases.push_back("Press \"s\" to start");
    phrases.push_back("You have died!");
    phrases.push_back("Your score: ");
    phrases.push_back("Press \"r\" to restart");
    phrases.push_back("Press \"h\" to leave the game");

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

    connect(starting_bird_timer, SIGNAL(timeout()), SLOT(MoveBirdBeforeStartingTheGame()));
    connect(column_timer, SIGNAL(timeout()), SLOT(MoveColumn()));
    connect(bird_timer, SIGNAL(timeout()), SLOT(MoveBird()));

    starting_bird_timer->start(25);

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

    IncreaseCounter();
    CheckIntersections();
    this->update();
}

void FlappyBird::MoveBirdBeforeStartingTheGame()
{
    point_for_bird.setY(point_for_bird.y() + starting_bird_pace);

    if(point_for_bird.y() <= 285 || point_for_bird.y() >= 315)
    {
        starting_bird_pace = -starting_bird_pace;
    }
    this->update();
}

void FlappyBird::StartGame()
{
    column_timer->start(25);
    bird_timer->start(25);
}

void FlappyBird::MoveBird()
{
    point_for_bird.setY(point_for_bird.y() + bird_pace);
    bird_pace++;
    this->update();
}

void FlappyBird::CheckIntersections()
{
    if(point_for_bird.y() + radius >= this->height())
    {
        DeathCase();
    }
    for(int i = 0; i < points.size(); i++)
    {
        if(point_for_bird.x()+radius >= points[i].x()-25 && point_for_bird.x() <= points[i].x()+45)
        {
            if(point_for_bird.y()+radius <= points[i].y()-25 || point_for_bird.y()+radius >= points[i].y()+70)
            {
                x_column_pace = 0;
            }
        }
    }    
}

void FlappyBird::DeathCase()
{
    death = true;
    bird_pace = 0;
    bird_timer->stop();
    column_timer->stop();
}

void FlappyBird::SetStartingCoordinates()
{
    counter = 0;

    int distance = -50;

    std::random_device rdGen;
    std::mt19937 gen(rdGen());
    std::uniform_int_distribution<> dis0_15(70, this->height() - 70);

    point_for_bird.setX(100);
    point_for_bird.setY(300);
    bird_pace = -10;
    x_column_pace = -4;

    for(int i = 0; i < 4; i++)
    {
        points[i].setX(this->width()+distance);
        distance += 300;
        points[i].setY(dis0_15(gen));
    }

    StartGame();
}

void FlappyBird::IncreaseCounter()
{
    for(int i = 0; i < 4; i++)
    {
        if(point_for_bird.x() >= points[i].x()-3 && point_for_bird.x() <= points[i].x())
        {
            counter++;
        }
    }
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

    first_column.DrawColumn(&painter, lower_image, upper_image);
    second_column.DrawColumn(&painter, lower_image, upper_image);
    third_column.DrawColumn(&painter, lower_image, upper_image);
    forth_column.DrawColumn(&painter, lower_image, upper_image);

    QImage bird_image("C:/Users/Yuriy Kozlov/Documents/flappybird/bluebird-downflap.png");

    bird.DrawBird(&painter, point_for_bird, bird_image);

    score = QString("%1").arg(counter);
    QFont font("Courier", 35, QFont::DemiBold);
    painter.setFont(font);
    painter.drawText(350, 100, score);

    phrases[0] = QString("%1").arg(phrases[0]);
    painter.drawText(150, 300, phrases[0]);

    QFont font_1("Courier", 25, QFont::DemiBold);
    painter.setFont(font_1);

    if(death)
    {
        for(int i = 1; i < phrases.size(); i++)
        {
            phrases[i] = QString("%1").arg(phrases[i]);
            painter.drawText(150, 200+(i-1)*45, phrases[i]);
        }
         painter.drawText(400, 245, score);
    }
}

void FlappyBird::keyPressEvent(QKeyEvent *event)
{
    if(x_column_pace != 0)
    {
        if(event->key() == Qt::Key_Space)
        {
            bird_pace = -10;
        }
    }
    if(event->key() == Qt::Key_R)
    {
        SetStartingCoordinates();
       death = false;
    }
    if(!column_timer->isActive() && !bird_timer->isActive() && bird_pace == -10)
    {
        if(event->key() == Qt::Key_S)
        {
             starting_bird_timer->stop();
             StartGame();
             phrases[0] = "";
        }
    }
    if(event->key() == Qt::Key_H)
    {
        hide();
    }
}

FlappyBird::~FlappyBird()
{
    delete ui;
}
