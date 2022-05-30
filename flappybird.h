#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include "column.h"
#include "bird.h"
#include "basement.h"
#include "settingswindow.h"

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

    void MoveBasement();

    void CheckIntersections();

    void SetStartingCoordinates();

    void IncreaseCounter();

    void DeathCase();

    void StartGame();

    void SetMainBackgroundImage(QImage image);

    void SetColumnPictures(std::vector<QImage> &pictures);

private slots:
    void on_StartGameButton_clicked();

    void on_RestartButton_clicked();

    void on_CloseGameButton_clicked();

    void on_SettingsButton_clicked();

public slots:
    void SlotForHeightOfJump(int height_of_jump);

    void SlotForColumnPace(int pace);

    void SlotForBirdPaceOfFall(int pace);

    void SlotForBackgroundImage(QImage image);

    void SlotForBirdSkin(std::vector<QString> &skins);

    void SlotForColumnPictures(std::vector<QString> &pictures);

private:
    Ui::FlappyBird *ui;
    std::vector<QPoint> points_for_columns;
    Bird bird;
    Column column;
    Basement basement;
    std::vector<QPoint> points_for_basement;
    QString score;
    QString best_score;
    std::vector<QString> phrases;
    QImage main_background_image;
    SettingsWindow *window = new SettingsWindow;
    std::vector<QImage> column_pictures;

private:
    int counter = 0;
    int counter_for_best_score = 0;
    bool death = false;

private:
    QTimer* column_timer = new QTimer(this);
    QTimer* bird_timer = new QTimer(this);
    QTimer* starting_bird_timer = new QTimer(this);
    QTimer* basement_timer = new QTimer(this);
};

#endif // FLAPPYBIRD_H
