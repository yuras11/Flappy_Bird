#include "flappybird.h"
#include "./ui_flappybird.h"

FlappyBird::FlappyBird(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlappyBird)
{
    std::random_device rdGen;
    std::mt19937 gen(rdGen());
    std::uniform_int_distribution<> dis0_15(50, this->height() - 50);

    int distance = -50;

    for(int i = 0; i < 4; i++)
    {
        QPoint point(this->width() + distance,dis0_15(gen));
        points.push_back(point);
        distance += 300;
    }

    QTimer* ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), SLOT(MoveColumn()));
    ptimer->start(25);

    ui->setupUi(this);
}

void FlappyBird::MoveColumn()
{
    std::random_device rdGen;
    std::mt19937 gen1(rdGen());
    std::uniform_int_distribution<> dis0_15(50, this->height() - 50);
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

void FlappyBird::paintEvent(QPaintEvent *event)
{
    Column first_column(this->points[0]);
    Column second_column(this->points[1]);
    Column third_column(this->points[2]);
    Column forth_column(this->points[3]);

    QPainter painter(this);
    QImage background("C:/Users/Yuriy Kozlov/Documents/flappybird/1616033040_2-p-fon-flappy-bird-3.png", "PNG");
    QBrush background_brush(background);
    painter.fillRect(0, 0, this->width(), this->height(), background_brush);

    QImage lower_column("C:/Users/Yuriy Kozlov/Documents/flappybird/flappy-bird-column.png");
    QBrush brush_for_lower_column(lower_column);

    QImage upper_column("C:/Users/Yuriy Kozlov/Documents/flappybird/flappy-bird-column.png");
    QBrush brush_for_upper_column(upper_column);

    first_column.DrawColumn(&painter, brush_for_upper_column, brush_for_lower_column);
    second_column.DrawColumn(&painter, brush_for_upper_column, brush_for_lower_column);
    third_column.DrawColumn(&painter, brush_for_upper_column, brush_for_lower_column);
    forth_column.DrawColumn(&painter, brush_for_upper_column, brush_for_lower_column);
}

void FlappyBird::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        x_column_pace = -4;
    }
}

FlappyBird::~FlappyBird()
{
    delete ui;
}
