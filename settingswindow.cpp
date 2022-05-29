#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "bird.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent)
  ,  ui(new Ui::SettingsWindow)
  , main_background_image("C:/Users/Yuriy Kozlov/Documents/flappybird/background-day.png")

{
    phrases.push_back("Settings");
    phrases.push_back("Change bird\'s hight of jump:");
    phrases.push_back("Change column\'s pace:");
    phrases.push_back("Change bird\'s pace of fall:");
    phrases.push_back("Paste your reference:");

    ui->setupUi(this);

    ui->HeightOfJumpSlider->setRange(5, 15);
    ui->HeightOfJumpSlider->setValue(10);
    ui->ColumnPaceSlider->setRange(1, 10);
    ui->ColumnPaceSlider->setValue(4);
    ui->PaceOfFallSlider->setRange(1, 5);
    ui->PaceOfFallSlider->setValue(1);
}

void SettingsWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(0, 0, this->width(), this->height(), main_background_image);

    phrases[0] = QString("%1").arg(phrases[0]);
    QFont font("Courier", 35, QFont::DemiBold);
    painter.setFont(font);
    painter.drawText(270, 50, phrases[0]);

    phrases[1] = QString("%1").arg(phrases[1]);
    QFont font10("Courier", 10, QFont::DemiBold);
    painter.setFont(font10);
    painter.drawText(ui->HeightOfJumpSlider->x(), ui->HeightOfJumpSlider->y()-15, phrases[1]);

    QFont font12("Courier", 12, QFont::DemiBold);
    painter.setFont(font12);

    phrases[2] = QString("%1").arg(phrases[2]);
    painter.drawText(ui->ColumnPaceSlider->x(), ui->ColumnPaceSlider->y()-15, phrases[2]);

    painter.setFont(font10);
    phrases[3] = QString("%1").arg(phrases[3]);
    painter.drawText(ui->PaceOfFallSlider->x(), ui->PaceOfFallSlider->y()-15, phrases[3]);

    phrases[4] = QString("%1").arg(phrases[4]);
    painter.setFont(font12);
    painter.drawText(ui->LineForBackground->x(), ui->LineForBackground->y()-15, phrases[4]);

}

void SettingsWindow::SetMainBackgroundImage(QImage image)
{
    main_background_image = image;
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_ReturnButton_clicked()
{
    this->hide();
}

void SettingsWindow::on_HeightOfJumpSlider_sliderMoved(int position)
{
    ui->HeightOfJumpSlider->setValue(position);
    emit SignalForHeightOfJump(position);
}

void SettingsWindow::on_ColumnPaceSlider_sliderMoved(int position)
{
    ui->ColumnPaceSlider->setValue(position);
    emit SignalForColumnPace(position);
}

void SettingsWindow::on_PaceOfFallSlider_sliderMoved(int position)
{
    ui->PaceOfFallSlider->setValue(position);
    emit SignalForBirdPaceOfFall(position);
}

void SettingsWindow::on_ButtonForBackground_clicked()
{ 
    QString background = ui->LineForBackground->text();
    QImage image(background);
    SetMainBackgroundImage(image);
    emit SignalForBackgroundImage(image);
}

void SettingsWindow::on_ClearBackgroundButton_clicked()
{
    ui->LineForBackground->clear();
    ui->LineForBackground->grabKeyboard();
}

void SettingsWindow::on_ChangeBirdSkinButton_clicked()
{
    std::vector<QString> skins;

    skins.push_back(ui->LineForFirstBirdPicture->text());
    skins.push_back(ui->LineForFirstBirdPicture->text());
    skins.push_back(ui->LineForFirstBirdPicture->text());

    skins.push_back(ui->LineForSecondBirdPicture->text());
    skins.push_back(ui->LineForSecondBirdPicture->text());
    skins.push_back(ui->LineForSecondBirdPicture->text());

    skins.push_back(ui->LineForThirdBirdPicture->text());
    skins.push_back(ui->LineForThirdBirdPicture->text());
    skins.push_back(ui->LineForThirdBirdPicture->text());

    skins.push_back(ui->LineForForthBirdPicture->text());
    skins.push_back(ui->LineForForthBirdPicture->text());
    skins.push_back(ui->LineForForthBirdPicture->text());

    emit SignalForBirdSkin(skins);
}

void SettingsWindow::on_ClearBirdButton_clicked()
{
    ui->LineForFirstBirdPicture->clear();
    ui->LineForSecondBirdPicture->clear();
    ui->LineForThirdBirdPicture->clear();
    ui->LineForForthBirdPicture->clear();
}
