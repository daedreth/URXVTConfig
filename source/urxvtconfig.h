#ifndef URXVTCONFIG_H
#define URXVTCONFIG_H

#include <QMainWindow>

namespace Ui {
class URXVTConfig;
}

class URXVTConfig : public QMainWindow
{
    Q_OBJECT

public:
    explicit URXVTConfig(QWidget *parent = 0);
    ~URXVTConfig();
    void updatePreview();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_pushButtonColor1_clicked();

    void on_pushButtonColor2_clicked();

    void on_pushButtonColor3_clicked();

    void on_pushButtonColor4_clicked();

    void on_pushButtonColor5_clicked();

    void on_pushButtonColor6_clicked();

    void on_pushButtonColor7_clicked();

    void on_pushButtonColor8_clicked();

    void on_pushButtonColor9_clicked();

    void on_pushButtonColor10_clicked();

    void on_pushButtonColor11_clicked();

    void on_pushButtonColor12_clicked();

    void on_pushButtonColor13_clicked();

    void on_pushButtonColor14_clicked();

    void on_pushButtonColor15_clicked();

    void on_pushButtonColor16_clicked();

    void on_pushButtonColor17_clicked();

    void on_pushButtonColor18_clicked();

    void on_pushButtonColor19_clicked();

    void on_checkBoxClickableUrls_clicked();

    void on_actionFrom_File_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

private:
    Ui::URXVTConfig *ui;
};

#endif // URXVTCONFIG_H
