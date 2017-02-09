#ifndef PRESETWINDOW_H
#define PRESETWINDOW_H

#include <QString>
#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class PresetWindow;
}

class PresetWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PresetWindow(QWidget *parent = 0);
    ~PresetWindow();
    void loadPresets();
    QString presetTitle;
    QString presetColors;

private slots:
    void on_pushButtonCancel_clicked();

    void on_listWidgetPresets_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::PresetWindow *ui;
};

#endif // PRESETWINDOW_H
