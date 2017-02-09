#include "presetwindow.h"
#include "ui_presetwindow.h"
#include <QListWidgetItem>
#include "QFile"
#include <QMessageBox>

PresetWindow::PresetWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetWindow)
{
    ui->setupUi(this);
    loadPresets();
}

PresetWindow::~PresetWindow()
{
    delete ui;
}

void PresetWindow::loadPresets()
{
    QString pathToDatabase = "/home/"+qgetenv("USER")+"/.config/urxvtconfig/presets.db";
    QFile database(pathToDatabase);
    QString lineToCount;
    int linecount = 0;


    if(!database.exists())
    {
        QMessageBox msgBox;
        msgBox.setText("Error!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setInformativeText("Database does not exist!\nPlease manually create ~/.config/urxvtconfig/presets.db");
        msgBox.exec();
    }else{
        database.open(QIODevice::ReadOnly);
        while(!database.atEnd())
        {
            lineToCount = database.readLine();

            linecount++;

        }
        database.close();

            // reopen because bugs and stuff

        database.open(QIODevice::ReadOnly);

        for(int i = 0; i < linecount; i++)
        {

            QString presetString;
            presetString = database.readLine();
            QListWidgetItem *theme = new QListWidgetItem;
            theme->setText(presetString.left(presetString.indexOf(":")));
            theme->setToolTip(presetString);
            ui->listWidgetPresets->addItem(theme);
        }
        database.close();
    }

}

void PresetWindow::on_pushButtonCancel_clicked()
{
    this->close();
}

void PresetWindow::on_listWidgetPresets_itemDoubleClicked(QListWidgetItem *item)
{
    presetTitle = item->text();
    presetColors = item->toolTip();
    this->close();
}
