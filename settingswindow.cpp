#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::SettingsWindow)
  , main_background_image("C:/Users/Yuriy Kozlov/Documents/flappybird/background-day.png")
  , bird(new Bird)
  , column(new Column)

{
    phrases.push_back("Settings");
    phrases.push_back("Change bird\'s hight of jump:");
    phrases.push_back("Change column\'s pace:");
    phrases.push_back("Change bird\'s pace of fall:");

    QFont font25("Courier", 25, QFont::DemiBold);
    fonts.push_back(font25);
    QFont font10("Courier", 10, QFont::DemiBold);
    fonts.push_back(font10);
    QFont font12("Courier", 12, QFont::DemiBold);
    fonts.push_back(font12);

    ui->setupUi(this);

    ui->HeightOfJumpSlider->setRange(5, 15);
    ui->HeightOfJumpSlider->setValue(10);
    ui->ColumnPaceSlider->setRange(1, 10);
    ui->ColumnPaceSlider->setValue(4);
    ui->PaceOfFallSlider->setRange(1, 5);
    ui->PaceOfFallSlider->setValue(1);

    ui->BirdSkinListView->setViewMode(QListView::ListMode);
    ui->BackgroundListView->setViewMode(QListView::ListMode);

    for(int i = 0; i < bird->bird_images.size(); i++)
    {
        bird_pictures_list << bird->bird_images[i];
    }
    background_pics_list << main_background_image;
    for(int i = 0; i < column->column_pictures.size(); i++)
    {
        column_pics_list << column->column_pictures[i];
    }

    modelBird = new QStringListModel(bird_pictures_list, parent);
    modelBackground = new QStringListModel(background_pics_list, parent);
    modelColumns = new QStringListModel(column_pics_list, parent);

    ui->BirdSkinListView->setModel(modelBird);
    ui->BackgroundListView->setModel(modelBackground);
    ui->ColumnPicturesListView->setModel(modelColumns);

}

void SettingsWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QImage back_image(main_background_image);
    painter.fillRect(0, 0, this->width(), this->height(), back_image);
    painter.setFont(fonts[0]);
    painter.drawText(55, 50, phrases[0]);
    painter.setFont(fonts[1]);
    painter.drawText(ui->HeightOfJumpSlider->x(), ui->HeightOfJumpSlider->y()-15, phrases[1]);
    painter.setFont(fonts[2]);
    painter.drawText(ui->ColumnPaceSlider->x(), ui->ColumnPaceSlider->y()-15, phrases[2]);
    painter.setFont(fonts[1]);
    painter.drawText(ui->PaceOfFallSlider->x(), ui->PaceOfFallSlider->y()-15, phrases[3]);
}

void SettingsWindow::SetMainBackgroundImage(const QString &image)
{
    main_background_image = image;
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_ReturnButton_clicked()
{
    if(!bird_pictures_list.isEmpty() && !background_pics_list.isEmpty() && !column_pics_list.isEmpty())
    {
        this->hide();
    }
    else
    {
        QMessageBox::critical(this, "Warning", "Fill in empty fields!");
    }
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

void SettingsWindow::on_ChooseBirdPictureButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
    if(!fileName.isEmpty())
    {
        bird_pictures_list << fileName;
        modelBird = new QStringListModel(bird_pictures_list);
        ui->BirdSkinListView->setModel(modelBird);
    }
}

void SettingsWindow::on_ClearBirdListButton_clicked()
{
    bird_pictures_list.clear();
    modelBird = new QStringListModel(bird_pictures_list);
    ui->BirdSkinListView->setModel(modelBird);
}

void SettingsWindow::on_SetBirdSkinButton_clicked()
{
    std::vector<QString> pictures;

    if(bird_pictures_list.isEmpty())
    {
        QMessageBox::critical(this, "Warning", "Cannot initialize the bird without any pictures");
    }
    else
    {
        for(int i = 0; i < bird_pictures_list.size(); i++)
        {
            pictures.push_back(bird_pictures_list[i]);
        }
        emit SignalForSettingBirdPictures(pictures);
    }
}

void SettingsWindow::on_ChooseBackgroundButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
    if(!fileName.isEmpty())
    {
        background_pics_list << fileName;
        modelBackground = new QStringListModel(background_pics_list);
        ui->BackgroundListView->setModel(modelBackground);
    }
}

void SettingsWindow::on_ClearBackgroundButton_clicked()
{
    background_pics_list.clear();
    modelBackground = new QStringListModel(background_pics_list);
    ui->BackgroundListView->setModel(modelBackground);
}

void SettingsWindow::on_SetBackgroundButton_clicked()
{
    if(background_pics_list.isEmpty())
    {
        QMessageBox::critical(this, "Warning", "Cannot initialize background without any pictures");
    }
    else if(background_pics_list.size() == 1)
    {
        emit SignalForBackgroundImage(background_pics_list[0]);
        SetMainBackgroundImage(background_pics_list[0]);
    }
    else
    {
        QMessageBox::critical(this, "Warning", "Cannot initialize background with more than one picture");
    }
}

void SettingsWindow::on_ChangeColumnPicturesButton_clicked()
{
    if(column_pics_list.isEmpty())
    {
        QMessageBox::critical(this, "Warning", "Cannot initialize columns without any pictures");

    }
    else if(column_pics_list.size() == 2)
    {
        std::vector<QString> pictures;
        for(int i = 0; i < column_pics_list.size(); i++)
        {
            pictures.push_back(column_pics_list[i]);
        }
        emit SignalForColumnPictures(pictures);
    }
    else
    {
        QMessageBox::critical(this, "Warning", "Cannot initialize columns with more or less than 2 pictures");
    }
}

void SettingsWindow::on_ClearColumnPicturesButton_clicked()
{
    column_pics_list.clear();
    modelColumns = new QStringListModel(column_pics_list);
    ui->ColumnPicturesListView->setModel(modelColumns);
}

void SettingsWindow::on_ChooseColumnPicturesButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
    if(!fileName.isEmpty())
    {
        column_pics_list << fileName;
        modelColumns = new QStringListModel(column_pics_list);
        ui->ColumnPicturesListView->setModel(modelColumns);
    }
}
