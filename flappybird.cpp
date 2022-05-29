#include "flappybird.h"
#include "settingswindow.h"
#include "./ui_flappybird.h"

FlappyBird::FlappyBird(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlappyBird)
    , main_background_image("C:/Users/Yuriy Kozlov/Documents/flappybird/background-day.png")
{

   phrases.push_back("You have died!");
   phrases.push_back("Your score: ");
   phrases.push_back("Best score: ");

   for(int i = 0; i < 2; i++)
   {
        QPoint point(i*800, 550);
        points_for_basement.push_back(point);
   }

    std::random_device rdGen;
    std::mt19937 gen(rdGen());
    std::uniform_int_distribution<> dis0_15(70, 410);

    int distance = -50;

    for(int i = 0; i < 4; i++)
    {
        QPoint point(2*this->width() + distance,dis0_15(gen));
        points.push_back(point);
        distance += 300;
    }

    connect(starting_bird_timer, SIGNAL(timeout()), SLOT(MoveBirdBeforeStartingTheGame()));
    connect(column_timer, SIGNAL(timeout()), SLOT(MoveColumn()));
    connect(bird_timer, SIGNAL(timeout()), SLOT(MoveBird()));
    connect(basement_timer, SIGNAL(timeout()), SLOT(MoveBasement()));

    starting_bird_timer->start(25);
    basement_timer->start(25);

    ui->setupUi(this);

    ui->RestartButton->hide();

    connect(window, &SettingsWindow::SignalForHeightOfJump, this, &FlappyBird::SlotForHeightOfJump);
    connect(window, &SettingsWindow::SignalForColumnPace, this, &FlappyBird::SlotForColumnPace);
    connect(window, &SettingsWindow::SignalForBirdPaceOfFall, this, &FlappyBird::SlotForBirdPaceOfFall);
    connect(window, &SettingsWindow::SignalForBackgroundImage, this, &FlappyBird::SlotForBackgroundImage);
    connect(window, &SettingsWindow::SignalForBirdSkin, this, &FlappyBird::SlotForBirdSkin);
}

void FlappyBird::MoveColumn()
{
    std::random_device rdGen;
    std::mt19937 gen1(rdGen());
    std::uniform_int_distribution<> dis0_15(70, 410);
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
    this->update();
}

void FlappyBird::MoveBirdBeforeStartingTheGame()
{
    bird.point_for_bird.setY(bird.point_for_bird.y() + bird.starting_bird_pace);
    if(bird.point_for_bird.y() <= 285 || bird.point_for_bird.y() >= 315)
    {
        bird.starting_bird_pace = -bird.starting_bird_pace;
    }
    this->update();
}

void FlappyBird::MoveBasement()
{
    for(int i = 0; i < points_for_basement.size(); i++)
    {
        points_for_basement[i].setX(points_for_basement[i].x() + basement_pace);

        if(points_for_basement[i].x()+800 <= 0)
        {
            points_for_basement[i].setX(this->width()-10);
        }
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
    bird.point_for_bird.setY(bird.point_for_bird.y() + bird.bird_pace);
    bird.bird_pace += bird.bird_pace_of_fall;

    CheckIntersections();
    this->update();
}

void FlappyBird::CheckIntersections()
{   
    if(bird.point_for_bird.y() + bird.radius >= 550)
    {
        DeathCase();
    }

    for(int i = 0; i < points.size(); i++)
    {
        if(bird.point_for_bird.x()+bird.radius >= points[i].x()-25 && bird.point_for_bird.x() <= points[i].x()+45)
        {
            if(bird.point_for_bird.y()+bird.radius <= points[i].y()-25 || bird.point_for_bird.y()+bird.radius >= points[i].y()+70)
            {
                column_timer->stop();
                basement_timer->stop();
            }
        }
    }    
}

void FlappyBird::DeathCase()
{
    death = true;
    bird.bird_pace = 0;

    if(column_timer->isActive() && basement_timer->isActive())
    {
        column_timer->stop();
        basement_timer->stop();
    }

    bird_timer->stop();
    ui->RestartButton->show();
    ui->CloseGameButton->show();
    ui->SettingsButton->show();
    ui->RestartButton->grabKeyboard();
}

void FlappyBird::SetStartingCoordinates()
{
    counter = 0;

    int distance = -50;

    std::random_device rdGen;
    std::mt19937 gen(rdGen());
    std::uniform_int_distribution<> dis0_15(70, 410);

    bird.point_for_bird.setX(200);
    bird.point_for_bird.setY(300);
    bird.bird_pace = -10;

    for(int i = 0; i < 4; i++)
    {
        points[i].setX(2*this->width()+distance);
        distance += 300;
        points[i].setY(dis0_15(gen));
    }
    StartGame();
}

void FlappyBird::IncreaseCounter()
{
    for(int i = 0; i < 4; i++)
    {
        if(bird.point_for_bird.x() > points[i].x()+x_column_pace-1 && bird.point_for_bird.x() < points[i].x())
        {
             counter++;
        }
    }
}

void FlappyBird::SetMainBackgroundImage(QImage image)
{
    main_background_image = image;
}

void FlappyBird::paintEvent(QPaintEvent *event)
{
    Column first_column(this->points[0]);
    Column second_column(this->points[1]);
    Column third_column(this->points[2]);
    Column forth_column(this->points[3]);

    QPainter painter(this);

    painter.fillRect(0, 0, this->width(), this->height(), main_background_image);

    QImage lower_image("C:/Users/Yuriy Kozlov/Documents/flappybird/lower-pipe-green.png");
    QImage upper_image("C:/Users/Yuriy Kozlov/Documents/flappybird/pipe-green.png");
    first_column.DrawColumn(&painter, lower_image, upper_image);
    second_column.DrawColumn(&painter, lower_image, upper_image);
    third_column.DrawColumn(&painter, lower_image, upper_image);
    forth_column.DrawColumn(&painter, lower_image, upper_image);

    bird.DrawBird(&painter);

    Basement basement1(points_for_basement[0]);
    Basement basement2(points_for_basement[1]);

    QImage image_for_basement("C:/Users/Yuriy Kozlov/Documents/flappybird/basement.png");
    basement1.DrawBasement(&painter, image_for_basement);
    basement2.DrawBasement(&painter, image_for_basement);

    if(!death)
    {
        bird.BirdAnimation();
    }

    score = QString("%1").arg(counter);
    QFont font("Courier", 35, QFont::DemiBold);
    painter.setFont(font);
    painter.drawText(350, 100, score);

    QFont font_1("Courier", 25, QFont::DemiBold);
    painter.setFont(font_1);

    if(death)
    {
        if(counter > counter_for_best_score)
        {
            counter_for_best_score = counter;
        }

        best_score = QString("%1").arg(counter_for_best_score);

        for(int i = 0; i < phrases.size(); i++)
        {
            phrases[i] = QString("%1").arg(phrases[i]);
            painter.drawText(250, 200+i*45, phrases[i]);
        }

        painter.drawText(500, 245, score);
        painter.drawText(500, 290, best_score);
    }
}

void FlappyBird::keyPressEvent(QKeyEvent *event)
{
    if(column_timer->isActive())
    {
        if(event->key() == Qt::Key_Space)
        {
            bird.bird_pace = bird.height_of_jump;
        }
    }
}

void FlappyBird::SetColumnPace(int pace)
{
    x_column_pace = -pace;
    basement_pace = -pace;
}

FlappyBird::~FlappyBird()
{
    delete ui;
}

void FlappyBird::on_StartGameButton_clicked()
{
    ui->centralwidget->grabKeyboard();
    ui->StartGameButton->releaseKeyboard();
    ui->StartGameButton->hide();
    ui->CloseGameButton->hide();
    ui->SettingsButton->hide();
    starting_bird_timer->stop();
    StartGame();
}

void FlappyBird::on_RestartButton_clicked()
{
    basement_timer->start(25);
    SetStartingCoordinates();
    death = false;
    ui->centralwidget->grabKeyboard();
    ui->RestartButton->hide();
    ui->CloseGameButton->hide();
    ui->SettingsButton->hide();
}

void FlappyBird::on_CloseGameButton_clicked()
{
    this->close();
}

void FlappyBird::on_SettingsButton_clicked()
{
    window->setFixedSize(800, 600);
    if(!window->isActiveWindow())
    {
        window->show();
    }
}

void FlappyBird::SlotForHeightOfJump(int height_of_jump)
{
    bird.SetHeightOfJump(height_of_jump);
}

void FlappyBird::SlotForColumnPace(int pace)
{
    SetColumnPace(pace);
}

void FlappyBird::SlotForBirdPaceOfFall(int pace)
{
    bird.SetBirdPaceOfFall(pace);
}

void FlappyBird::SlotForBackgroundImage(QImage image)
{
    SetMainBackgroundImage(image);
}

void FlappyBird::SlotForBirdSkin(std::vector<QString> &skins)
{
    std::vector<QImage> images;
    for(int i = 0; i < skins.size(); i++)
    {
        QImage image(skins[i]);
        images.push_back(image);
    }
    bird.SetBirdImages(images);
}
