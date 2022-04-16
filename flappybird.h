#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include <column.h>

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

    void paintEvent(QPaintEvent *event);

public slots:
    void MoveColumn();

private:
    Ui::FlappyBird *ui;
    std::vector<QPoint> points;
    int x_column_pace = 0;
};

#endif // FLAPPYBIRD_H
