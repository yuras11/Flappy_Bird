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
#include <random>
#include <QImage>

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

    void keyReleaseEvent(QKeyEvent *event);

    void paintEvent(QPaintEvent *event);

public slots:
    void MoveColumn();
    void MoveBird();

private:
    Ui::FlappyBird *ui;
    std::vector<QPoint> points;
    QPoint point_for_bird;
    int x_column_pace = 0;
    int bird_pace = 0;
    int radius = 25;
};

#endif // FLAPPYBIRD_H
