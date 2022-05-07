#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include <column.h>
#include <bird.h>

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QTimer>
#include <QKeyEvent>
#include <vector>
#include <string>
#include <random>
#include <QImage>
#include <QString>
#include <QFont>


QT_BEGIN_NAMESPACE
namespace Ui { class FlappyBird; }
QT_END_NAMESPACE

class FlappyBird : public QMainWindow
{
    Q_OBJECT

public:
    FlappyBird(QWidget *parent = nullptr);

    ~FlappyBird();

    void keyPressEvent(QKeyEvent *event);

    void paintEvent(QPaintEvent *event);

public slots:
    void MoveColumn();

    void MoveBird();

    void MoveBirdBeforeStartingTheGame();

    void CheckIntersections();

    void SetStartingCoordinates();

    void IncreaseCounter();

    void DeathCase();

    void StartGame();

private:
    Ui::FlappyBird *ui;
    std::vector<QPoint> points;
    QPoint point_for_bird;
    int starting_bird_pace = -2;
    int x_column_pace = -4;
    int bird_pace = -10;
    int radius = 25;
    int counter = 0;
    bool death = false;
    QTimer* column_timer = new QTimer(this);
    QTimer* bird_timer = new QTimer(this);
    QTimer* starting_bird_timer = new QTimer(this);
    QString score;
    std::vector<QString> phrases;
};

#endif // FLAPPYBIRD_H
