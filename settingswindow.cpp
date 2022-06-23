#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::SettingsWindow)
  , main_background_image(new QImage("C:/Users/Yuriy Kozlov/Documents/flappybird/background-day.png"))
  , bird(new Bird)

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

    for(int i = 0; i < bird->bird_images.size(); i++)
    {
        bird_pictures_list << bird->bird_images[i];
    }

    model = new QStringListModel(bird_pictures_list, parent);

    ui->BirdSkinListView->setModel(model);

}

void SettingsWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(0, 0, this->width(), this->height(), *main_background_image);
    painter.setFont(fonts[0]);
    painter.drawText(55, 50, phrases[0]);
    painter.setFont(fonts[1]);
    painter.drawText(ui->HeightOfJumpSlider->x(), ui->HeightOfJumpSlider->y()-15, phrases[1]);
    painter.setFont(fonts[2]);
    painter.drawText(ui->ColumnPaceSlider->x(), ui->ColumnPaceSlider->y()-15, phrases[2]);
    painter.setFont(fonts[1]);
    painter.drawText(ui->PaceOfFallSlider->x(), ui->PaceOfFallSlider->y()-15, phrases[3]);

}

void SettingsWindow::SetMainBackgroundImage(const QImage &image)
{
    *main_background_image = image;
}

bool SettingsWindow::ColumnLinesAreEpmty()
{
    return ui->LineForLowerColumnPicture->text() == "" && ui->LineForUpperColumnPicture->text() == "";
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_ReturnButton_clicked()
{
    if(!bird_pictures_list.isEmpty())
    {
        this->hide();
    }
    else
    {
        QMessageBox::critical(this, "Warning", "Cannot initialize the bird without any pictures");
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

void SettingsWindow::on_ButtonForBackground_clicked()
{
    if(ui->LineForBackground->text() != "")
    {
        QString background = ui->LineForBackground->text();
        QImage image(background);
        SetMainBackgroundImage(image);
        emit SignalForBackgroundImage(image);
    }
    else
    {
        QMessageBox::critical(this, "Warning", "Cannot initialize background without a picture");
    }
}

void SettingsWindow::on_ClearBackgroundButton_clicked()
{
    ui->LineForBackground->clear();
    ui->LineForBackground->grabKeyboard();
}

void SettingsWindow::on_ChangeColumnPicturesButton_clicked()
{
    std::vector<QString> pictures;

    if(!ColumnLinesAreEpmty())
    {
        pictures.push_back(ui->LineForUpperColumnPicture->text());
        pictures.push_back(ui->LineForLowerColumnPicture->text());

        emit SignalForColumnPictures(pictures);
    }
    else
    {
        QMessageBox::critical(this, "Warning", "Cannot initialize columns without any pictures");
    }
}

void SettingsWindow::on_ClearColumnPicturesButton_clicked()
{
    ui->LineForLowerColumnPicture->clear();
    ui->LineForLowerColumnPicture->clear();
}

void SettingsWindow::on_ChooseBirdPictureButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
    if(!fileName.isEmpty())
    {
        bird_pictures_list << fileName;
        model = new QStringListModel(bird_pictures_list);
        ui->BirdSkinListView->setModel(model);
    }

}

void SettingsWindow::on_ClearButton_clicked()
{
    bird_pictures_list.clear();
    model = new QStringListModel(bird_pictures_list);
    ui->BirdSkinListView->setModel(model);
}


void SettingsWindow::on_SetBirdSkinButton_clicked()
{
    std::vector<QString> pictures;

    if(bird_pictures_list.isEmpty())
    {
        QMessageBox::critical(this, "Warning", "Cannot initialize the bird without any pictures");
    }

    if(!bird_pictures_list.isEmpty())
    {
        for(int i = 0; i < bird_pictures_list.size(); i++)
        {
            pictures.push_back(bird_pictures_list[i]);
        }
        emit SignalForSettingBirdPictures(pictures);
    }
}
