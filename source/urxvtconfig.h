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
    void loadPreset(QString preset);
    void saveToFile(QString target);
    void openFromFile(QString target);
    void loadConfig();

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

    void on_actionSolarized_Dark_triggered();

    void on_actionSolarized_Light_triggered();

    void on_actionGreyscale_Dark_triggered();

    void on_actionGreyscale_Light_triggered();

    void on_actionCodeschool_Dark_triggered();

    void on_actionCodeschool_Light_triggered();

    void on_actionEmbers_Dark_triggered();

    void on_actionEmbers_Light_triggered();

    void on_actionSave_to_Xresources_triggered();

    void on_actionSave_to_custom_file_triggered();

    void on_actionLoad_from_Xresourced_triggered();

    void on_actionLoad_from_Xdefaults_triggered();

    void on_actionGreenscreen_Dark_triggered();

    void on_actionGreenscreen_Light_triggered();

    void on_actionMocha_Dark_triggered();

    void on_actionMocha_Light_triggered();

    void on_checkBoxTransparencyEnabled_clicked();

    void on_checkBoxTrueTransparencyEnabled_clicked();

    void on_checkBoxTabs_clicked();

    void on_actionIsotope_Dark_triggered();

    void on_actionIsotope_Light_triggered();

    void on_actionOcean_Dark_triggered();

    void on_actionOcean_Light_triggered();

    void on_actionParaiso_Dark_triggered();

    void on_actionParaiso_Light_triggered();

    void on_fontComboBox_currentFontChanged();

    void on_actionChoose_Prese_triggered();

private:
    Ui::URXVTConfig *ui;
};

#endif // URXVTCONFIG_H
