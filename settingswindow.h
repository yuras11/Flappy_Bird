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
#include "column.h"

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

    void SetMainBackgroundImage(const QString &image);

private slots:
    void on_ReturnButton_clicked();

    void on_HeightOfJumpSlider_sliderMoved(int position);

    void on_ColumnPaceSlider_sliderMoved(int position);

    void on_PaceOfFallSlider_sliderMoved(int position);

    void on_ChooseBirdPictureButton_clicked();

    void on_ClearBirdListButton_clicked();

    void on_SetBirdSkinButton_clicked();

    void on_ChooseBackgroundButton_clicked();

    void on_ClearBackgroundButton_clicked();

    void on_SetBackgroundButton_clicked();

    void on_ChangeColumnPicturesButton_clicked();

    void on_ClearColumnPicturesButton_clicked();

    void on_ChooseColumnPicturesButton_clicked();

signals:
    void SignalForHeightOfJump(int height_of_jump);

    void SignalForColumnPace(int pace);

    void SignalForBirdPaceOfFall(int pace);

    void SignalForBackgroundImage(const QString &image);

    void SignalForColumnPictures(const std::vector<QString> &pictures);

    void SignalForSettingBirdPictures(const std::vector<QString> &pictures);

private:
    Ui::SettingsWindow *ui;
    std::vector<QString> phrases;
    std::vector<QFont> fonts;
    QString main_background_image;
    Bird* bird;
    Column *column;
    QStringList bird_pictures_list;
    QStringList background_pics_list;
    QStringList column_pics_list;
    QAbstractItemModel *modelBird;
    QAbstractItemModel *modelBackground;
    QAbstractItemModel *modelColumns;
};

#endif // SETTINGSWINDOW_H
