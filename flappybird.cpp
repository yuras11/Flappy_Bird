#include "flappybird.h"
#include "settingswindow.h"
#include "./ui_flappybird.h"

FlappyBird::FlappyBird(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlappyBird)
    , column(new Column)
    , bird(new Bird)
    , basement(new Basement)
    , main_background_image(new QImage("C:/Users/Yuriy Kozlov/Documents/flappybird/background-day.png"))
    , window(new SettingsWindow)
    , counter(0)
    , counter_for_best_score(0)
    , death(false)
    , intersection(false)
    , starting_bird_timer(new QTimer(this))
    , basement_timer(new QTimer(this))
    , main_timer(new QTimer(this))
{
    phrases.push_back("You have died!");
    phrases.push_back("Your score: ");
    phrases.push_back("Best score: ");

    connect(starting_bird_timer, SIGNAL(timeout()), SLOT(BeforeStartTheGame()));
    connect(main_timer, SIGNAL(timeout()), SLOT(StartGame()));
    connect(basement_timer, SIGNAL(timeout()), SLOT(MoveBasement()));

    starting_bird_timer->start(25);
    basement_timer->start(25);
    ui->setupUi(this);
    ui->RestartButton->hide();

    connect(window, &SettingsWindow::SignalForHeightOfJump, this, &FlappyBird::SlotForHeightOfJump);
    connect(window, &SettingsWindow::SignalForColumnPace, this, &FlappyBird::SlotForColumnPace);
    connect(window, &SettingsWindow::SignalForBirdPaceOfFall, this, &FlappyBird::SlotForBirdPaceOfFall);
    connect(window, &SettingsWindow::SignalForBackgroundImage, this, &FlappyBird::SlotForBackgroundImage);
    connect(window, &SettingsWindow::SignalForColumnPictures, this, &FlappyBird::SlotForColumnPictures);
    connect(window, &SettingsWindow::SignalForSettingBirdPictures, this, &FlappyBird::SlotForSettingBirdPictures);
}

void FlappyBird::MoveBasement()
{
    basement->MoveBasement();
    this->update();
}

void FlappyBird::BeforeStartTheGame()
{
    bird->MoveBirdBeforeStartingTheGame();
    this->update();
}

void FlappyBird::StartGame()
{
    main_timer->start(25);
    bird->MoveBird();
    column->MoveColumn();
    if(column->IntersectionHappened(*bird))
    {
        intersection = true;
        bird->point_for_bird->setY(bird->point_for_bird->y() + 10);
    }
    if(bird->point_for_bird->y() + bird->radius >= 550)
    {
        DeathCase();
    }
    IncreaseCounter();
    this->update();
}

void FlappyBird::DeathCase()
{
    death = true;
    bird->bird_pace = 0;
    main_timer->stop();
    basement_timer->stop();
    ui->RestartButton->show();
    ui->CloseGameButton->show();
    ui->SettingsButton->show();
    ui->RestartButton->grabKeyboard();
}

void FlappyBird::IncreaseCounter()
{
    for(int i = 0; i < 4; i++)
    {
        if(!intersection && bird->point_for_bird->x() > column->points_for_columns[i].x()+column->column_pace+39 &&
           bird->point_for_bird->x() < column->points_for_columns[i].x()+40)
        {
            counter++;
        }
    }
}

void FlappyBird::SetStartingCoordinates()
{
    counter = 0;
    intersection = false;
    column->SetStartingColumnCoordinates();
    bird->SetStartingBirdCoordinates();
    StartGame();
}

void FlappyBird::SetMainBackgroundImage(const QImage &image)
{
    *main_background_image = image;
}

void FlappyBird::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(0, 0, this->width(), this->height(), *main_background_image);
    column->DrawColumns(&painter);
    bird->DrawBird(&painter);
    basement->DrawBasement(&painter);
    if(!death)
    {
        bird->BirdAnimation();
    }
    score = QString("%1").arg(counter);
    QFont font35("Courier", 35, QFont::DemiBold);
    painter.setFont(font35);
    painter.drawText(350, 100, score);
    QFont font25("Courier", 25, QFont::DemiBold);
    painter.setFont(font25);
    if(death)
    {
        if(counter > counter_for_best_score)
        {
            counter_for_best_score = counter;
        }
        best_score = QString("%1").arg(counter_for_best_score);
        for(int i = 0; i < phrases.size(); i++)
        {
            painter.drawText(250, 200+i*45, phrases[i]);
        }
        painter.drawText(500, 245, score);
        painter.drawText(500, 290, best_score);
    }
}

void FlappyBird::keyPressEvent(QKeyEvent *event)
{
    if(!intersection && event->key() == Qt::Key_Space)
    {
        bird->bird_pace = bird->height_of_jump;
    }
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
    death = false;
    basement_timer->start(25);
    SetStartingCoordinates();
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
    bird->SetHeightOfJump(height_of_jump);
}

void FlappyBird::SlotForColumnPace(int pace)
{
    basement->SetBasementPace(pace);
    column->SetColumnPace(pace);
}

void FlappyBird::SlotForBirdPaceOfFall(int pace)
{
    bird->SetBirdPaceOfFall(pace);
}

void FlappyBird::SlotForBackgroundImage(const QString &image)
{
    QImage back_image(image);
    SetMainBackgroundImage(back_image);
}

void FlappyBird::SlotForColumnPictures(const std::vector<QString> &pictures)
{
    column->SetColumnPictures(pictures);
}

void FlappyBird::SlotForSettingBirdPictures(const std::vector<QString> &pictures)
{
   bird->bird_images = pictures;
}
