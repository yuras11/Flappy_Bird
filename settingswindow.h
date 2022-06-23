#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QPainter>
#include <QString>
#include <string>
#include <QFont>
#include <vector>
#include <QAbstractItemModel>
#include <QStringListModel>
#include <QFileDialog>
#include <QMessageBox>

#include "bird.h"

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

    void SetMainBackgroundImage(const QImage &image);

    bool ColumnLinesAreEpmty();

private slots:
    void on_ReturnButton_clicked();

    void on_HeightOfJumpSlider_sliderMoved(int position);

    void on_ColumnPaceSlider_sliderMoved(int position);

    void on_PaceOfFallSlider_sliderMoved(int position);

    void on_ButtonForBackground_clicked();

    void on_ClearBackgroundButton_clicked();

    void on_ChangeColumnPicturesButton_clicked();

    void on_ClearColumnPicturesButton_clicked();

    void on_ChooseBirdPictureButton_clicked();

    void on_ClearButton_clicked();

    void on_SetBirdSkinButton_clicked();

signals:
    void SignalForHeightOfJump(int height_of_jump);

    void SignalForColumnPace(int pace);

    void SignalForBirdPaceOfFall(int pace);

    void SignalForBackgroundImage(const QImage &image);

    void SignalForColumnPictures(const std::vector<QString> &pictures);

    void SignalForSettingBirdPictures(const std::vector<QString> &pictures);

private:
    Ui::SettingsWindow *ui;
    std::vector<QString> phrases;
    std::vector<QFont> fonts;
    QImage* main_background_image;
    Bird* bird;
    QStringList bird_pictures_list;
    QAbstractItemModel *model;
};

#endif // SETTINGSWINDOW_H
