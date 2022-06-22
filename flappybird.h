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
    void MoveBasement();

    void BeforeStartTheGame();

    void StartGame();

    void DeathCase();

    void SetStartingCoordinates();

    void SetMainBackgroundImage(const QImage &image);

private slots:
    void on_StartGameButton_clicked();

    void on_RestartButton_clicked();

    void on_CloseGameButton_clicked();

    void on_SettingsButton_clicked();

public slots:
    void SlotForHeightOfJump(int height_of_jump);

    void SlotForColumnPace(int pace);

    void SlotForBirdPaceOfFall(int pace);

    void SlotForBackgroundImage(const QImage &image);

    void SlotForColumnPictures(const std::vector<QString> &pictures);

    void SlotForSettingBirdPictures(const std::vector<QString> &pictures);

private:
    Ui::FlappyBird *ui;
    Bird bird;
    Column column;
    Basement basement;
    SettingsWindow *window;
    QString score;
    QString best_score;
    std::vector<QString> phrases;
    QImage main_background_image;
    int counter;
    int counter_for_best_score;
    bool death;
    bool intersection;
    QTimer* starting_bird_timer;
    QTimer* basement_timer;
    QTimer* main_timer;
};

#endif // FLAPPYBIRD_H
