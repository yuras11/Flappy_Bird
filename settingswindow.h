#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QPainter>
#include <QString>
#include <string>
#include <QFont>
#include <vector>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);

    ~SettingsWindow();

    void paintEvent(QPaintEvent *event);

    void SetMainBackgroundImage(QImage image);

private slots:
    void on_ReturnButton_clicked();

    void on_HeightOfJumpSlider_sliderMoved(int position);

    void on_ColumnPaceSlider_sliderMoved(int position);

    void on_PaceOfFallSlider_sliderMoved(int position);

    void on_ButtonForBackground_clicked();

    void on_ClearBackgroundButton_clicked();

    void on_ChangeBirdSkinButton_clicked();

    void on_ClearBirdButton_clicked();

signals:
    void SignalForHeightOfJump(int height_of_jump);

    void SignalForColumnPace(int pace);

    void SignalForBirdPaceOfFall(int pace);

    void SignalForBackgroundImage(QImage image);

    void SignalForBirdSkin(std::vector<QString> &skins);

private:
    Ui::SettingsWindow *ui;
    std::vector<QString> phrases;
    QImage main_background_image;
};

#endif // SETTINGSWINDOW_H
