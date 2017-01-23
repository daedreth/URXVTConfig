#include "urxvtconfig.h"
#include "ui_urxvtconfig.h"
#include "QColorDialog"
#include "QFile"
#include "QCheckBox"
#include "QMessageBox"
#include "QTextStream"
#include "QFileDialog"
#include "QProcess"

URXVTConfig::URXVTConfig(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::URXVTConfig)
{
    ui->setupUi(this);

    QObject::connect(ui->horizontalSliderShading, SIGNAL(valueChanged(int)), ui->spinBoxShading, SLOT(setValue(int)));
    QObject::connect(ui->spinBoxShading, SIGNAL(valueChanged(int)), ui->horizontalSliderShading, SLOT(setValue(int)));

    QObject::connect(ui->horizontalSliderFontSize, SIGNAL(valueChanged(int)), ui->spinBoxFontSize, SLOT(setValue(int)));
    QObject::connect(ui->spinBoxFontSize, SIGNAL(valueChanged(int)), ui->horizontalSliderFontSize, SLOT(setValue(int)));

    QObject::connect(ui->checkBoxTransparencyEnabled, SIGNAL(toggled(bool)), ui->horizontalSliderShading, SLOT(setEnabled(bool)));
    QObject::connect(ui->checkBoxTransparencyEnabled, SIGNAL(toggled(bool)), ui->spinBoxShading, SLOT(setEnabled(bool)));

    QObject::connect(ui->checkBoxClickableUrls, SIGNAL(toggled(bool)), ui->lineEditBrowser, SLOT(setEnabled(bool)));

    ui->lineEditBrowser->setDisabled(true);
    ui->checkBoxTabs->setChecked(false);
}

// setting up the filepaths
QString pathToFile = "/home/"+ qgetenv("USER") +"/.Xdefaults";
QString pathToFileResources = "/home/"+ qgetenv("USER") +"/.Xresources";

URXVTConfig::~URXVTConfig()
{
    delete ui;
}

void URXVTConfig::updatePreview()
{

    // Set up all the colors

    QColor backgroundColor(ui->lineEditColor2->text());
    QColor rowColor(ui->lineEditColor5->text());
    QColor includeColor(ui->lineEditColor14->text());
    QColor hppColor(ui->lineEditColor6->text());
    QColor usingColor(ui->lineEditColor10->text());
    QColor namespaceColor(ui->lineEditColor8->text());
    QColor stdColor(ui->lineEditColor1->text());
    QColor commentColor(ui->lineEditColor12->text());


    // Turn colors into qpalettes

    QPalette backgroundPal = ui->lineEditPreviewBackground->palette();
    QPalette rowPal = ui->labelPreviewRow1->palette();
    QPalette includePal = ui->labelPreviewInclude->palette();
    QPalette hppPal = ui->labelPreviewHpp->palette();
    QPalette usingPal = ui->labelPreviewUsing->palette();
    QPalette namespacePal = ui->labelPreviewNamespace->palette();
    QPalette stdPal = ui->labelPreviewStd->palette();
    QPalette commentPal = ui->labelPreviewComment->palette();


    // Apply color settings to UI

    backgroundPal.setColor(ui->lineEditPreviewBackground->backgroundRole(), backgroundColor);
    ui->lineEditPreviewBackground->setPalette(backgroundPal);

    rowPal.setColor(ui->labelPreviewRow1->foregroundRole(), rowColor);
    ui->labelPreviewRow1->setPalette(rowPal);
    ui->labelPreviewRow2->setPalette(rowPal);
    ui->labelPreviewRow3->setPalette(rowPal);
    ui->labelPreviewRow4->setPalette(rowPal);
    ui->labelPreviewRow5->setPalette(rowPal);
    ui->labelPreviewRow6->setPalette(rowPal);

    includePal.setColor(ui->labelPreviewInclude->foregroundRole(), includeColor);
    ui->labelPreviewInclude->setPalette(includePal);

    hppPal.setColor(ui->labelPreviewHpp->foregroundRole(), hppColor);
    ui->labelPreviewHpp->setPalette(hppPal);

    usingPal.setColor(ui->labelPreviewUsing->foregroundRole(), usingColor);
    ui->labelPreviewUsing->setPalette(usingPal);

    namespacePal.setColor(ui->labelPreviewNamespace->foregroundRole(), namespaceColor);
    ui->labelPreviewNamespace->setPalette(namespacePal);

    stdPal.setColor(ui->labelPreviewStd->foregroundRole(), stdColor);
    ui->labelPreviewStd->setPalette(stdPal);

    ui->labelPreviewInt->setPalette(namespacePal);
    ui->labelPreviewMain->setPalette(stdPal);

    commentPal.setColor(ui->labelPreviewComment->foregroundRole(), commentColor);
    ui->labelPreviewComment->setPalette(commentPal);

    ui->labelPreviewFloat->setPalette(namespacePal);
    ui->labelPreviewFloatName->setPalette(stdPal);
    ui->labelPreviewFloatValue->setPalette(hppPal);
    ui->labelPreviewFloatEnd->setPalette(stdPal);

    ui->labelPreviewEnd->setPalette(stdPal);

    // Font

    ui->labelPreviewRow1->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewRow2->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewRow3->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewRow4->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewRow5->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewRow6->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewInclude->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewHpp->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewUsing->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewNamespace->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewStd->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewInt->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewMain->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewComment->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewFloat->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewFloatName->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewFloatValue->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewFloatEnd->setFont(ui->fontComboBox->currentFont());
    ui->labelPreviewEnd->setFont(ui->fontComboBox->currentFont());


}

    // These functions apply colors to lineEdits,
    // I am aware that two of those are the same.

void setColorDefault(QLineEdit *line, QString colorString)
{
    QColor color(colorString);
    QPalette pal = line->palette();

    pal.setColor(line->backgroundRole(), color);
    line->setPalette(pal);
}

void setColor(QLineEdit *line)
{
    QColor color = QColorDialog::getColor(line->palette().color(line->backgroundRole()));
    QPalette pal = line->palette();

    line->setText(color.name());
    pal.setColor(line->backgroundRole(), color);
    line->setPalette(pal);
}

void setColorFromLoad(QString colorString, QLineEdit *line)
{
    QColor color(colorString);
    QPalette pal = line->palette();

    pal.setColor(line->backgroundRole(), color);
    line->setPalette(pal);

}

void URXVTConfig::on_actionNew_triggered()
{
    // Color reset

    ui->lineEditColor1->setText("#c5c8c6");
    setColorDefault(ui->lineEditColor1, ui->lineEditColor1->text());
    ui->lineEditColor2->setText("#1d1f21");
    setColorDefault(ui->lineEditColor2, ui->lineEditColor2->text());
    ui->lineEditColor3->setText("#c5c8c6");
    setColorDefault(ui->lineEditColor3, ui->lineEditColor3->text());
    ui->lineEditColor4->setText("#282a2e");
    setColorDefault(ui->lineEditColor4, ui->lineEditColor4->text());
    ui->lineEditColor5->setText("#373b41");
    setColorDefault(ui->lineEditColor5, ui->lineEditColor5->text());
    ui->lineEditColor6->setText("#a54242");
    setColorDefault(ui->lineEditColor6, ui->lineEditColor6->text());
    ui->lineEditColor7->setText("#cc6666");
    setColorDefault(ui->lineEditColor7, ui->lineEditColor7->text());
    ui->lineEditColor8->setText("#8c9440");
    setColorDefault(ui->lineEditColor8, ui->lineEditColor8->text());
    ui->lineEditColor9->setText("#b5bd68");
    setColorDefault(ui->lineEditColor9, ui->lineEditColor9->text());
    ui->lineEditColor10->setText("#de935f");
    setColorDefault(ui->lineEditColor10, ui->lineEditColor10->text());
    ui->lineEditColor11->setText("#f0c674");
    setColorDefault(ui->lineEditColor11, ui->lineEditColor11->text());
    ui->lineEditColor12->setText("#5f819d");
    setColorDefault(ui->lineEditColor12, ui->lineEditColor12->text());
    ui->lineEditColor13->setText("#81a2be");
    setColorDefault(ui->lineEditColor13, ui->lineEditColor13->text());
    ui->lineEditColor14->setText("#85678f");
    setColorDefault(ui->lineEditColor14, ui->lineEditColor14->text());
    ui->lineEditColor15->setText("#b294bb");
    setColorDefault(ui->lineEditColor15, ui->lineEditColor15->text());
    ui->lineEditColor16->setText("#5e8d87");
    setColorDefault(ui->lineEditColor16, ui->lineEditColor16->text());
    ui->lineEditColor17->setText("#8abeb7");
    setColorDefault(ui->lineEditColor17, ui->lineEditColor17->text());
    ui->lineEditColor18->setText("#707880");
    setColorDefault(ui->lineEditColor18, ui->lineEditColor18->text());
    ui->lineEditColor19->setText("#c5c8c6");
    setColorDefault(ui->lineEditColor19, ui->lineEditColor19->text());

    // Transparency reset

    ui->checkBoxTransparencyEnabled->setChecked(false);
    ui->horizontalSliderShading->setValue(0);
    ui->horizontalSliderShading->setEnabled(false);

    // Scrollbar reset

    ui->checkBoxScrollbarEnabled->setChecked(true);
    ui->checkBoxScrollbarRight->setChecked(true);

    // Clickable URL reset

    ui->checkBoxClickableUrls->setChecked(false);
    ui->lineEditBrowser->setText("URL-Handler?");

    // Other reset

    ui->spinBoxFontSize->setValue(12);
    ui->spinBoxFontSpacing->setValue(0);
    ui->checkBoxFontBoldDisable->setChecked(false);
    ui->checkBoxTabs->setChecked(false);

    updatePreview();
}

void URXVTConfig::on_actionOpen_triggered()
{
    QString openFileName = QFileDialog::getOpenFileName();

    QFile file(openFileName);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox msgBox;
        msgBox.setText("Unable to open file!");
        msgBox.setInformativeText("Ensure you have permissions to modify the file or that the file exists!");
        msgBox.exec();
    }else{
    for(int i = 0; i < 100; i++)
    {
        QString line = file.readLine();

        if (line.startsWith("!") || line.startsWith("#"))
        {
            // this deals with commented out lines
            continue;

        }else if(line.startsWith("*.foreground")){
            ui->lineEditColor1->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor1);
        }else if(line.startsWith("*.background")){
            ui->lineEditColor2->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor2);
        }else if(line.startsWith("*.cursorColor")){
            ui->lineEditColor3->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor3);
        }else if(line.startsWith("*.color0")){
            ui->lineEditColor4->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor4);
        }else if(line.startsWith("*.color8")){
            ui->lineEditColor5->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor5);
        }else if(line.startsWith("*.color15")){
            ui->lineEditColor19->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor19);
        }else if(line.startsWith("*.color9")){
            ui->lineEditColor7->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor7);
        }else if(line.startsWith("*.color2")){
            ui->lineEditColor8->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor8);
        }else if(line.startsWith("*.color10")){
            ui->lineEditColor9->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor9);
        }else if(line.startsWith("*.color3")){
            ui->lineEditColor10->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor10);
        }else if(line.startsWith("*.color11")){
            ui->lineEditColor11->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor11);
        }else if(line.startsWith("*.color4")){
            ui->lineEditColor12->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor12);
        }else if(line.startsWith("*.color12")){
            ui->lineEditColor13->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor13);
        }else if(line.startsWith("*.color5")){
            ui->lineEditColor14->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor14);
        }else if(line.startsWith("*.color13")){
            ui->lineEditColor15->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor15);
        }else if(line.startsWith("*.color6")){
            ui->lineEditColor16->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor16);
        }else if(line.startsWith("*.color14")){
            ui->lineEditColor17->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor17);
        }else if(line.startsWith("*.color7")){
            ui->lineEditColor18->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor18);
        }else if(line.startsWith("*.color1")){
            ui->lineEditColor6->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor6);

            // Transparency

        }else if(line.startsWith("URxvt*tran")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxTransparencyEnabled->setChecked(true);
            else ui->checkBoxTransparencyEnabled->setChecked(false);
        }else if(line.startsWith("URxvt*shad")){
            line = line.mid(line.length()-3,2);
            ui->spinBoxShading->setValue(line.toInt());

            // Scrollbar

        }else if(line.startsWith("URxvt*scrollBar_")){
            // this does nothing, like the government, but is necessary
            // just like the government
        }else if(line.startsWith("URxvt*scrollB")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxScrollbarEnabled->setChecked(true);
            else ui->checkBoxScrollbarEnabled->setChecked(false);

            // Font

        }else if(line.startsWith("URxvt.font:")){
            ui->spinBoxFontSize->setValue(line.mid(line.length()-3, 2).toInt());
            line = line.mid(16);
            ui->labelCurrentFont->setText(line.left(line.length() - 14));
        }else if(line.startsWith("URxvt.boldFont:")){
            ui->checkBoxFontBoldDisable->setChecked(true);
        }else if(line.startsWith("URxvt.letterSpa")){
            line = line.mid(line.length()-3,2);
            ui->spinBoxFontSpacing->setValue(line.toInt());
        }else if(line.startsWith("*antialias:")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxFontAntialiasing->setChecked(true);
            else ui->checkBoxFontAntialiasing->setChecked(false);
        }else if(line.startsWith("*autohint")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxFontHinting->setChecked(true);
            else ui->checkBoxFontHinting->setChecked(false);

            // Plugins

        }else if(line.startsWith("URxvt.url-launcher")){
            ui->checkBoxClickableUrls->setChecked(true);
            ui->lineEditBrowser->setText(line.mid(20));
        }else if(line.startsWith("URxvt.perl-ext-common: ...,tab")){
            ui->checkBoxTabs->setChecked(true);
        }
    }
}
    file.close();
    updatePreview();

}

void URXVTConfig::on_actionSave_triggered()
{

    QFile file(pathToFile);

    if (!file.open(QIODevice::ReadWrite) )
    {
        QMessageBox msgBox;
        msgBox.setText("Unable to open/write to ~/.Xdefaults.");
        msgBox.setInformativeText("Ensure you have permissions to modify the file.");
        msgBox.exec();
    }else{
        file.remove();
        file.close();
        file.open(QIODevice::ReadWrite);

        // Open stream in order to write to file

        QTextStream initialMessage(&file);
        initialMessage << "##### THIS FILE IS BEING CURRENTLY MANAGED BY URXVTCONFIG #####" << endl;
        initialMessage << "##### CHANGES DONE TO THIS FILE MANUALLY MAY AFFECT THE FUNCTIONALITY ######" << endl;
        initialMessage << "##### PROCEED WITH CAUTION! #####" << endl << endl;
        file.close();

        // Reopen the file to prevent errors

        file.open(QIODevice::Append);
        QTextStream stream(&file);

        stream << "! special colors" << endl;
        stream << "*.foreground:  " << ui->lineEditColor1->text() << endl;
        stream << "*.background:  " << ui->lineEditColor2->text() << endl;
        stream << "*.cursorColor  " << ui->lineEditColor3->text() << endl;
        stream << "! black" << endl;
        stream << "*.color0:      " << ui->lineEditColor4->text() << endl;
        stream << "*.color8:      " << ui->lineEditColor5->text() << endl;
        stream << "! red" << endl;
        stream << "*.color1:      " << ui->lineEditColor6->text() << endl;
        stream << "*.color9:      " << ui->lineEditColor7->text() << endl;
        stream << "! green" << endl;
        stream << "*.color2:      " << ui->lineEditColor8->text() << endl;
        stream << "*.color10:     " << ui->lineEditColor9->text() << endl;
        stream << "! yellow" << endl;
        stream << "*.color3:      " << ui->lineEditColor10->text() << endl;
        stream << "*.color11:     " << ui->lineEditColor11->text() << endl;
        stream << "! blue" << endl;
        stream << "*.color4:      " << ui->lineEditColor12->text() << endl;
        stream << "*.color12:     " << ui->lineEditColor13->text() << endl;
        stream << "! magenta" << endl;
        stream << "*.color5:      " << ui->lineEditColor14->text() << endl;
        stream << "*.color13:     " << ui->lineEditColor15->text() << endl;
        stream << "! cyan" << endl;
        stream << "*.color6:      " << ui->lineEditColor16->text() << endl;
        stream << "*.color14:     " << ui->lineEditColor17->text() << endl;
        stream << "! white" << endl;
        stream << "*.color7:      " << ui->lineEditColor18->text() << endl;
        stream << "*.color15:     " << ui->lineEditColor19->text() << endl << endl;

        // Scrollbar

        if(ui->checkBoxScrollbarEnabled->isChecked())
        {
            stream << "URxvt*scrollBar:     true" << endl;
        }else{
            stream << "URxvt*scrollBar:     false" << endl << endl;
        }
        if(ui->checkBoxScrollbarRight->isChecked())
        {
            stream << "URxvt*scrollBar_right:   true" << endl;
        }else{
            stream << "URxvt*scrollBar_right:   false" << endl << endl;
        }

        // Transparency

        if(ui->checkBoxTransparencyEnabled->isChecked()){
            stream << "URxvt*transparent:   true" << endl;
            stream << "URxvt*shading:       " << ui->horizontalSliderShading->value() << endl << endl;
        }else{
            stream << "URxvt*transparent:   false" << endl << endl;
        }

        // Font

        QString current = ui->fontComboBox->currentFont().toString();
        current.chop(20);
        stream << "URxvt.font: xft:" << current.left(current.length()-1) << ":pixelsize=" << ui->spinBoxFontSize->value() << endl << endl;

        if(ui->checkBoxFontBoldDisable->isChecked()){
            stream << "URxvt.boldFont:" << endl;
        }

        stream << "URxvt.letterSpace: " << ui->spinBoxFontSpacing->value() << endl;

        if(ui->checkBoxFontAntialiasing->isChecked())
        {
            stream << "*antialias:  true" << endl;
        }else{
            stream << "*antialias:  false" << endl;
        }

        if(ui->checkBoxFontHinting->isChecked())
        {
            stream << "*autohint:  true" << endl;
        }else{
            stream << "*autohint:  false" << endl << endl;
        }

        // Plugins

        if(ui->checkBoxClickableUrls->isChecked())
        {
            stream << "URxvt.perl-ext-common: default,matcher" << endl;
            stream << "URxvt.url-launcher: " << ui->lineEditBrowser->text() << endl;
            stream << "URxvt.matcher.button: 1" << endl << endl;
        }

        if(ui->checkBoxTabs->isChecked())
        {
            // this uses colors already defined above for some reason

            stream << "URxvt.perl-ext-common: ...,tabbed,..." << endl;
            stream << "URxvt.tabbed.tabbar-fg: 2" << endl;
            stream << "URxvt.tabbed.tabbar-bg: 0" << endl;
            stream << "URxvt.tabbed.tab-fg: 3" << endl;
            stream << "URxvt.tabbed.tab-bg: 2" << endl;
        }

        file.close();

        // Confirmation message

        QMessageBox msgBox;
        msgBox.setText("Changes saved!");
        msgBox.exec();

    }
}

// apply changes to lineEditColor's

void URXVTConfig::on_pushButtonColor1_clicked()
{
    setColor(ui->lineEditColor1);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor2_clicked()
{
    setColor(ui->lineEditColor2);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor3_clicked()
{
    setColor(ui->lineEditColor3);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor4_clicked()
{
    setColor(ui->lineEditColor4);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor5_clicked()
{
    setColor(ui->lineEditColor5);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor6_clicked()
{
    setColor(ui->lineEditColor6);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor7_clicked()
{
    setColor(ui->lineEditColor7);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor8_clicked()
{
    setColor(ui->lineEditColor8);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor9_clicked()
{
    setColor(ui->lineEditColor9);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor10_clicked()
{
    setColor(ui->lineEditColor10);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor11_clicked()
{
    setColor(ui->lineEditColor11);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor12_clicked()
{
    setColor(ui->lineEditColor12);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor13_clicked()
{
    setColor(ui->lineEditColor13);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor14_clicked()
{
    setColor(ui->lineEditColor14);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor15_clicked()
{
    setColor(ui->lineEditColor15);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor16_clicked()
{
    setColor(ui->lineEditColor16);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor17_clicked()
{
    setColor(ui->lineEditColor17);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor18_clicked()
{
    setColor(ui->lineEditColor18);
    updatePreview();
}

void URXVTConfig::on_pushButtonColor19_clicked()
{
    setColor(ui->lineEditColor19);
    updatePreview();
}

void URXVTConfig::on_checkBoxClickableUrls_clicked()
{
    if(ui->lineEditBrowser->isEnabled())
    {
        // install urxvt-perls

        QMessageBox msgBox;
        msgBox.setText("External software necessary!!");
        msgBox.setInformativeText("Please install \"urxvt-perls\" with your distributions package manager!");
        msgBox.exec();
    }
}

void URXVTConfig::loadPreset(QString preset)
{

    QString presetString = preset;

    presetString.remove(0,presetString.indexOf('#'));
    ui->lineEditColor1->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor1, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor2->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor2, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor3->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor3, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor4->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor4, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor5->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor5, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor6->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor6, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor7->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor7, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor8->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor8, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor9->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor9, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor10->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor10, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor11->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor11, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor12->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor12, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor13->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor13, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor14->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor14, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor15->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor15, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor16->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor16, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor17->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor17, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor18->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor18, presetString.left(7));
    presetString.remove(0,presetString.indexOf('#', 3));
    ui->lineEditColor19->setText(presetString.left(7));
    setColorDefault(ui->lineEditColor19, presetString.left(7));
}

void URXVTConfig::on_actionFrom_File_triggered()
{

    // imagemagick is necessary for this to work

    QProcess process;
    QString fileName = QFileDialog::getOpenFileName();
    QString processName = "convert ";
    processName.append(fileName);   // this launches imagemagick
    processName.append(" +dither -colors 18 -unique-colors txt:-");
    process.start(processName);
    process.waitForFinished(-1);

    QString stdout = process.readAllStandardOutput();


    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor19->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor19, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor2->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor2, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor3->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor3, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor4->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor4, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor5->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor5, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor6->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor6, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor7->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor7, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor8->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor8, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor9->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor9, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor10->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor10, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor11->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor11, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor12->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor12, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor13->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor13, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor14->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor14, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor15->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor15, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor16->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor16, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor17->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor17, stdout.left(7));
        ui->lineEditColor19->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor19, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor18->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor18, stdout.left(7));
    stdout.remove(0,stdout.indexOf('#', 3));
        ui->lineEditColor1->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor1, stdout.left(7));
        ui->lineEditColor3->setText(stdout.left(7));
        setColorDefault(ui->lineEditColor3, stdout.left(7));

}

void URXVTConfig::on_actionHelp_triggered()
{
    // Help box

    QMessageBox msgBox;
    msgBox.setText("Help");
    msgBox.setInformativeText("Visit the GitHub page for more information!\n\n\nhttp://github.com/daedreth/URXVTConfig");
    msgBox.exec();
}

void URXVTConfig::on_actionAbout_triggered()
{
    // About box

    QMessageBox msgBox;
    msgBox.setText("About");
    msgBox.setInformativeText("(c) URXVTConfig by Dawid 'daedreth' Eckert\n\nURXVTConfig is a tool intended for configuration of the rxvt-unicode terminal.");
    msgBox.exec();
}

void URXVTConfig::on_actionQuit_triggered()
{
    // Quit the application

    QApplication::quit();
}

void URXVTConfig::on_actionSolarized_Dark_triggered()
{
    QString preset = "#93a1a1,#002b36,#93a1a1,#002b36,#657b83,#dc322f,#dc322f,#859900,#859900,#b58900,#b58900,#268bd2,#268bd2,#6c71c4,#6c71c4,#2aa198,#2aa198,#93a1a1,#fdf6e3";
    loadPreset(preset);
    updatePreview();
}

void URXVTConfig::on_actionSolarized_Light_triggered()
{
    QString preset = "#586e75,#fdf6e3,#586e75,#002b36,#657b83,#dc322f,#dc322f,#859900,#859900,#b58900,#b58900,#268bd2,#268bd2,#6c71c4,#6c71c4,#2aa198,#2aa198,#93a1a1,#fdf6e3";
    loadPreset(preset);
    updatePreview();
}

void URXVTConfig::on_actionGreyscale_Dark_triggered()
{
    QString preset = "#b9b9b9,#101010,#b9b9b9,#101010,#525252,#7c7c7c,#7c7c7c,#8e8e8e,#8e8e8e,#a0a0a0,#a0a0a0,#686868,#686868,#747474,#747474,#868686,#868686,#b9b9b9,#f7f7f7";
    loadPreset(preset);
    updatePreview();
}

void URXVTConfig::on_actionGreyscale_Light_triggered()
{
    QString preset = "#464646,#f7f7f7,#464646,#101010,#525252,#7c7c7c,#7c7c7c,#8e8e8e,#8e8e8e,#a0a0a0,#a0a0a0,#686868,#686868,#747474,#747474,#868686,#868686,#b9b9b9,#f7f7f7";
    loadPreset(preset);
    updatePreview();
}

void URXVTConfig::on_actionCodeschool_Dark_triggered()
{
    QString preset = "#9ea7a6,#232c31,#9ea7a6,#232c31,#3f4944,#2a5491,#2a5491,#237986,#237986,#a03b1e,#a03b1e,#484d79,#484d79,#c59820,#c59820,#b02f30,#b02f30,#9ea7a6,#b5d8f6";
    loadPreset(preset);
    updatePreview();
}

void URXVTConfig::on_actionCodeschool_Light_triggered()
{
    QString preset = "#2a343a,#b5d8f6,#2a343a,#232c31,#3f4944,#2a5491,#2a5491,#237986,#237986,#a03b1e,#a03b1e,#484d79,#484d79,#c59820,#c59820,#b02f30,#b02f30,#9ea7a6,#b5d8f6";
    loadPreset(preset);
    updatePreview();
}

void URXVTConfig::on_actionEmbers_Dark_triggered()
{
    QString preset = "#a39a90,#16130f,#a39a90,#16130f,#5a5047,#826d57,#826d57,#57826d,#57826d,#6d8257,#6d8257,#6d5782,#6d5782,#82576d,#82576d,#576d82,#576d82,#a39a90,#dbd6d1";
    loadPreset(preset);
    updatePreview();
}

void URXVTConfig::on_actionEmbers_Light_triggered()
{
    QString preset = "#433b32,#dbd6d1,#433b32,#16130f,#5a5047,#826d57,#826d57,#57826d,#57826d,#6d8257,#6d8257,#6d5782,#6d5782,#82576d,#82576d,#576d82,#576d82,#a39a90,#dbd6d1";
    loadPreset(preset);
    updatePreview();
}

void URXVTConfig::on_actionSave_to_Xresources_triggered()
{

    QFile file(pathToFileResources);

    if (!file.open(QIODevice::ReadWrite) )
    {
        QMessageBox msgBox;
        msgBox.setText("Unable to open/write to ~/.Xresources");
        msgBox.setInformativeText("Ensure you have permissions to modify the file.");
        msgBox.exec();
    }else{
        file.remove();
        file.close();
        file.open(QIODevice::ReadWrite);

        // Open stream in order to write to file

        QTextStream initialMessage(&file);
        initialMessage << "##### THIS FILE IS BEING CURRENTLY MANAGED BY URXVTCONFIG #####" << endl;
        initialMessage << "##### CHANGES DONE TO THIS FILE MANUALLY MAY AFFECT THE FUNCTIONALITY ######" << endl;
        initialMessage << "##### PROCEED WITH CAUTION! #####" << endl << endl;
        file.close();

        // Reopen the file to prevent errors

        file.open(QIODevice::Append);
        QTextStream stream(&file);

        stream << "! special colors" << endl;
        stream << "*.foreground:  " << ui->lineEditColor1->text() << endl;
        stream << "*.background:  " << ui->lineEditColor2->text() << endl;
        stream << "*.cursorColor  " << ui->lineEditColor3->text() << endl;
        stream << "! black" << endl;
        stream << "*.color0:      " << ui->lineEditColor4->text() << endl;
        stream << "*.color8:      " << ui->lineEditColor5->text() << endl;
        stream << "! red" << endl;
        stream << "*.color1:      " << ui->lineEditColor6->text() << endl;
        stream << "*.color9:      " << ui->lineEditColor7->text() << endl;
        stream << "! green" << endl;
        stream << "*.color2:      " << ui->lineEditColor8->text() << endl;
        stream << "*.color10:     " << ui->lineEditColor9->text() << endl;
        stream << "! yellow" << endl;
        stream << "*.color3:      " << ui->lineEditColor10->text() << endl;
        stream << "*.color11:     " << ui->lineEditColor11->text() << endl;
        stream << "! blue" << endl;
        stream << "*.color4:      " << ui->lineEditColor12->text() << endl;
        stream << "*.color12:     " << ui->lineEditColor13->text() << endl;
        stream << "! magenta" << endl;
        stream << "*.color5:      " << ui->lineEditColor14->text() << endl;
        stream << "*.color13:     " << ui->lineEditColor15->text() << endl;
        stream << "! cyan" << endl;
        stream << "*.color6:      " << ui->lineEditColor16->text() << endl;
        stream << "*.color14:     " << ui->lineEditColor17->text() << endl;
        stream << "! white" << endl;
        stream << "*.color7:      " << ui->lineEditColor18->text() << endl;
        stream << "*.color15:     " << ui->lineEditColor19->text() << endl << endl;

        // Scrollbar

        if(ui->checkBoxScrollbarEnabled->isChecked())
        {
            stream << "URxvt*scrollBar:     true" << endl;
        }else{
            stream << "URxvt*scrollBar:     false" << endl << endl;
        }
        if(ui->checkBoxScrollbarRight->isChecked())
        {
            stream << "URxvt*scrollBar_right:   true" << endl;
        }else{
            stream << "URxvt*scrollBar_right:   false" << endl << endl;
        }

        // Transparency

        if(ui->checkBoxTransparencyEnabled->isChecked()){
            stream << "URxvt*transparent:   true" << endl;
            stream << "URxvt*shading:       " << ui->horizontalSliderShading->value() << endl << endl;
        }else{
            stream << "URxvt*transparent:   false" << endl << endl;
        }

        // Font

        QString current = ui->fontComboBox->currentFont().toString();
        current.chop(20);
        stream << "URxvt.font: xft:" << current.left(current.length()-1) << ":pixelsize=" << ui->spinBoxFontSize->value() << endl << endl;

        if(ui->checkBoxFontBoldDisable->isChecked()){
            stream << "URxvt.boldFont:" << endl;
        }

        stream << "URxvt.letterSpace: " << ui->spinBoxFontSpacing->value() << endl;

        if(ui->checkBoxFontAntialiasing->isChecked())
        {
            stream << "*antialias:  true" << endl;
        }else{
            stream << "*antialias:  false" << endl;
        }

        if(ui->checkBoxFontHinting->isChecked())
        {
            stream << "*autohint:  true" << endl;
        }else{
            stream << "*autohint:  false" << endl << endl;
        }

        // Plugins

        if(ui->checkBoxClickableUrls->isChecked())
        {
            stream << "URxvt.perl-ext-common: default,matcher" << endl;
            stream << "URxvt.url-launcher: " << ui->lineEditBrowser->text() << endl;
            stream << "URxvt.matcher.button: 1" << endl << endl;
        }

        if(ui->checkBoxTabs->isChecked())
        {
            // this uses colors already defined above for some reason

            stream << "URxvt.perl-ext-common: ...,tabbed,..." << endl;
            stream << "URxvt.tabbed.tabbar-fg: 2" << endl;
            stream << "URxvt.tabbed.tabbar-bg: 0" << endl;
            stream << "URxvt.tabbed.tab-fg: 3" << endl;
            stream << "URxvt.tabbed.tab-bg: 2" << endl;
        }

        file.close();

        // Confirmation message

        QMessageBox msgBox;
        msgBox.setText("Changes saved!");
        msgBox.exec();

    }
}

void URXVTConfig::on_actionSave_to_custom_file_triggered()
{
    QString saveFileName = QFileDialog::getSaveFileName();


    QFile file(saveFileName);

    if (!file.open(QIODevice::ReadWrite) )
    {
        QMessageBox msgBox;
        msgBox.setText("Unable to open your selected file!");
        msgBox.setInformativeText("Ensure you have permissions to modify the file.");
        msgBox.exec();
    }else{
        file.remove();
        file.close();
        file.open(QIODevice::ReadWrite);

        // Open stream in order to write to file

        QTextStream initialMessage(&file);
        initialMessage << "##### THIS FILE IS BEING CURRENTLY MANAGED BY URXVTCONFIG #####" << endl;
        initialMessage << "##### CHANGES DONE TO THIS FILE MANUALLY MAY AFFECT THE FUNCTIONALITY ######" << endl;
        initialMessage << "##### PROCEED WITH CAUTION! #####" << endl << endl;
        file.close();

        // Reopen the file to prevent errors

        file.open(QIODevice::Append);
        QTextStream stream(&file);

        stream << "! special colors" << endl;
        stream << "*.foreground:  " << ui->lineEditColor1->text() << endl;
        stream << "*.background:  " << ui->lineEditColor2->text() << endl;
        stream << "*.cursorColor  " << ui->lineEditColor3->text() << endl;
        stream << "! black" << endl;
        stream << "*.color0:      " << ui->lineEditColor4->text() << endl;
        stream << "*.color8:      " << ui->lineEditColor5->text() << endl;
        stream << "! red" << endl;
        stream << "*.color1:      " << ui->lineEditColor6->text() << endl;
        stream << "*.color9:      " << ui->lineEditColor7->text() << endl;
        stream << "! green" << endl;
        stream << "*.color2:      " << ui->lineEditColor8->text() << endl;
        stream << "*.color10:     " << ui->lineEditColor9->text() << endl;
        stream << "! yellow" << endl;
        stream << "*.color3:      " << ui->lineEditColor10->text() << endl;
        stream << "*.color11:     " << ui->lineEditColor11->text() << endl;
        stream << "! blue" << endl;
        stream << "*.color4:      " << ui->lineEditColor12->text() << endl;
        stream << "*.color12:     " << ui->lineEditColor13->text() << endl;
        stream << "! magenta" << endl;
        stream << "*.color5:      " << ui->lineEditColor14->text() << endl;
        stream << "*.color13:     " << ui->lineEditColor15->text() << endl;
        stream << "! cyan" << endl;
        stream << "*.color6:      " << ui->lineEditColor16->text() << endl;
        stream << "*.color14:     " << ui->lineEditColor17->text() << endl;
        stream << "! white" << endl;
        stream << "*.color7:      " << ui->lineEditColor18->text() << endl;
        stream << "*.color15:     " << ui->lineEditColor19->text() << endl << endl;

        // Scrollbar

        if(ui->checkBoxScrollbarEnabled->isChecked())
        {
            stream << "URxvt*scrollBar:     true" << endl;
        }else{
            stream << "URxvt*scrollBar:     false" << endl << endl;
        }
        if(ui->checkBoxScrollbarRight->isChecked())
        {
            stream << "URxvt*scrollBar_right:   true" << endl;
        }else{
            stream << "URxvt*scrollBar_right:   false" << endl << endl;
        }

        // Transparency

        if(ui->checkBoxTransparencyEnabled->isChecked()){
            stream << "URxvt*transparent:   true" << endl;
            stream << "URxvt*shading:       " << ui->horizontalSliderShading->value() << endl << endl;
        }else{
            stream << "URxvt*transparent:   false" << endl << endl;
        }

        // Font

        QString current = ui->fontComboBox->currentFont().toString();
        current.chop(20);
        stream << "URxvt.font: xft:" << current.left(current.length()-1) << ":pixelsize=" << ui->spinBoxFontSize->value() << endl << endl;

        if(ui->checkBoxFontBoldDisable->isChecked()){
            stream << "URxvt.boldFont:" << endl;
        }

        stream << "URxvt.letterSpace: " << ui->spinBoxFontSpacing->value() << endl;

        if(ui->checkBoxFontAntialiasing->isChecked())
        {
            stream << "*antialias:  true" << endl;
        }else{
            stream << "*antialias:  false" << endl;
        }

        if(ui->checkBoxFontHinting->isChecked())
        {
            stream << "*autohint:  true" << endl;
        }else{
            stream << "*autohint:  false" << endl << endl;
        }

        // Plugins

        if(ui->checkBoxClickableUrls->isChecked())
        {
            stream << "URxvt.perl-ext-common: default,matcher" << endl;
            stream << "URxvt.url-launcher: " << ui->lineEditBrowser->text() << endl;
            stream << "URxvt.matcher.button: 1" << endl << endl;
        }

        if(ui->checkBoxTabs->isChecked())
        {
            // this uses colors already defined above for some reason

            stream << "URxvt.perl-ext-common: ...,tabbed,..." << endl;
            stream << "URxvt.tabbed.tabbar-fg: 2" << endl;
            stream << "URxvt.tabbed.tabbar-bg: 0" << endl;
            stream << "URxvt.tabbed.tab-fg: 3" << endl;
            stream << "URxvt.tabbed.tab-bg: 2" << endl;
        }

        file.close();

        // Confirmation message

        QMessageBox msgBox;
        msgBox.setText("Changes saved!");
        msgBox.exec();

    }
}

void URXVTConfig::on_actionLoad_from_Xresourced_triggered()
{


    QFile file(pathToFileResources);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox msgBox;
        msgBox.setText("Unable to open ~/.Xresources.");
        msgBox.setInformativeText("Ensure you have permissions to modify the file or that the file exists!");
        msgBox.exec();
    }else{
    for(int i = 0; i < 100; i++)
    {
        QString line = file.readLine();

        if (line.startsWith("!") || line.startsWith("#"))
        {
            // this deals with commented out lines
            continue;

        }else if(line.startsWith("*.foreground")){
            ui->lineEditColor1->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor1);
        }else if(line.startsWith("*.background")){
            ui->lineEditColor2->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor2);
        }else if(line.startsWith("*.cursorColor")){
            ui->lineEditColor3->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor3);
        }else if(line.startsWith("*.color0")){
            ui->lineEditColor4->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor4);
        }else if(line.startsWith("*.color8")){
            ui->lineEditColor5->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor5);
        }else if(line.startsWith("*.color15")){
            ui->lineEditColor19->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor19);
        }else if(line.startsWith("*.color9")){
            ui->lineEditColor7->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor7);
        }else if(line.startsWith("*.color2")){
            ui->lineEditColor8->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor8);
        }else if(line.startsWith("*.color10")){
            ui->lineEditColor9->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor9);
        }else if(line.startsWith("*.color3")){
            ui->lineEditColor10->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor10);
        }else if(line.startsWith("*.color11")){
            ui->lineEditColor11->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor11);
        }else if(line.startsWith("*.color4")){
            ui->lineEditColor12->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor12);
        }else if(line.startsWith("*.color12")){
            ui->lineEditColor13->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor13);
        }else if(line.startsWith("*.color5")){
            ui->lineEditColor14->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor14);
        }else if(line.startsWith("*.color13")){
            ui->lineEditColor15->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor15);
        }else if(line.startsWith("*.color6")){
            ui->lineEditColor16->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor16);
        }else if(line.startsWith("*.color14")){
            ui->lineEditColor17->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor17);
        }else if(line.startsWith("*.color7")){
            ui->lineEditColor18->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor18);
        }else if(line.startsWith("*.color1")){
            ui->lineEditColor6->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor6);

            // Transparency

        }else if(line.startsWith("URxvt*tran")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxTransparencyEnabled->setChecked(true);
            else ui->checkBoxTransparencyEnabled->setChecked(false);
        }else if(line.startsWith("URxvt*shad")){
            line = line.mid(line.length()-3,2);
            ui->spinBoxShading->setValue(line.toInt());

            // Scrollbar

        }else if(line.startsWith("URxvt*scrollBar_")){
            // this does nothing, like the government, but is necessary
            // just like the government
        }else if(line.startsWith("URxvt*scrollB")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxScrollbarEnabled->setChecked(true);
            else ui->checkBoxScrollbarEnabled->setChecked(false);

            // Font

        }else if(line.startsWith("URxvt.font:")){
            ui->spinBoxFontSize->setValue(line.mid(line.length()-3, 2).toInt());
            line = line.mid(16);
            ui->labelCurrentFont->setText(line.left(line.length() - 14));
        }else if(line.startsWith("URxvt.boldFont:")){
            ui->checkBoxFontBoldDisable->setChecked(true);
        }else if(line.startsWith("URxvt.letterSpa")){
            line = line.mid(line.length()-3,2);
            ui->spinBoxFontSpacing->setValue(line.toInt());
        }else if(line.startsWith("*antialias:")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxFontAntialiasing->setChecked(true);
            else ui->checkBoxFontAntialiasing->setChecked(false);
        }else if(line.startsWith("*autohint")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxFontHinting->setChecked(true);
            else ui->checkBoxFontHinting->setChecked(false);

            // Plugins

        }else if(line.startsWith("URxvt.url-launcher")){
            ui->checkBoxClickableUrls->setChecked(true);
            ui->lineEditBrowser->setText(line.mid(20));
        }else if(line.startsWith("URxvt.perl-ext-common: ...,tab")){
            ui->checkBoxTabs->setChecked(true);
        }
    }
}
    file.close();
    updatePreview();
}

void URXVTConfig::on_actionLoad_from_Xdefaults_triggered()
{


    QFile file(pathToFile);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox msgBox;
        msgBox.setText("Unable to open ~/.Xdefaults.");
        msgBox.setInformativeText("Ensure you have permissions to modify the file or that the file exists!");
        msgBox.exec();
    }else{
    for(int i = 0; i < 100; i++)
    {
        QString line = file.readLine();

        if (line.startsWith("!") || line.startsWith("#"))
        {
            // this deals with commented out lines
            continue;

        }else if(line.startsWith("*.foreground")){
            ui->lineEditColor1->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor1);
        }else if(line.startsWith("*.background")){
            ui->lineEditColor2->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor2);
        }else if(line.startsWith("*.cursorColor")){
            ui->lineEditColor3->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor3);
        }else if(line.startsWith("*.color0")){
            ui->lineEditColor4->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor4);
        }else if(line.startsWith("*.color8")){
            ui->lineEditColor5->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor5);
        }else if(line.startsWith("*.color15")){
            ui->lineEditColor19->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor19);
        }else if(line.startsWith("*.color9")){
            ui->lineEditColor7->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor7);
        }else if(line.startsWith("*.color2")){
            ui->lineEditColor8->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor8);
        }else if(line.startsWith("*.color10")){
            ui->lineEditColor9->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor9);
        }else if(line.startsWith("*.color3")){
            ui->lineEditColor10->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor10);
        }else if(line.startsWith("*.color11")){
            ui->lineEditColor11->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor11);
        }else if(line.startsWith("*.color4")){
            ui->lineEditColor12->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor12);
        }else if(line.startsWith("*.color12")){
            ui->lineEditColor13->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor13);
        }else if(line.startsWith("*.color5")){
            ui->lineEditColor14->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor14);
        }else if(line.startsWith("*.color13")){
            ui->lineEditColor15->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor15);
        }else if(line.startsWith("*.color6")){
            ui->lineEditColor16->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor16);
        }else if(line.startsWith("*.color14")){
            ui->lineEditColor17->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor17);
        }else if(line.startsWith("*.color7")){
            ui->lineEditColor18->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor18);
        }else if(line.startsWith("*.color1")){
            ui->lineEditColor6->setText(line.mid(line.length()-8,7));
            setColorFromLoad(line.mid(line.length()-8,7), ui->lineEditColor6);

            // Transparency

        }else if(line.startsWith("URxvt*tran")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxTransparencyEnabled->setChecked(true);
            else ui->checkBoxTransparencyEnabled->setChecked(false);
        }else if(line.startsWith("URxvt*shad")){
            line = line.mid(line.length()-3,2);
            ui->spinBoxShading->setValue(line.toInt());

            // Scrollbar

        }else if(line.startsWith("URxvt*scrollBar_")){
            // this does nothing, like the government, but is necessary
            // just like the government
        }else if(line.startsWith("URxvt*scrollB")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxScrollbarEnabled->setChecked(true);
            else ui->checkBoxScrollbarEnabled->setChecked(false);

            // Font

        }else if(line.startsWith("URxvt.font:")){
            ui->spinBoxFontSize->setValue(line.mid(line.length()-3, 2).toInt());
            line = line.mid(16);
            ui->labelCurrentFont->setText(line.left(line.length() - 14));
        }else if(line.startsWith("URxvt.boldFont:")){
            ui->checkBoxFontBoldDisable->setChecked(true);
        }else if(line.startsWith("URxvt.letterSpa")){
            line = line.mid(line.length()-3,2);
            ui->spinBoxFontSpacing->setValue(line.toInt());
        }else if(line.startsWith("*antialias:")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxFontAntialiasing->setChecked(true);
            else ui->checkBoxFontAntialiasing->setChecked(false);
        }else if(line.startsWith("*autohint")){
            line = line.mid(line.length()-5,4);
            if(line == "true") ui->checkBoxFontHinting->setChecked(true);
            else ui->checkBoxFontHinting->setChecked(false);

            // Plugins

        }else if(line.startsWith("URxvt.url-launcher")){
            ui->checkBoxClickableUrls->setChecked(true);
            ui->lineEditBrowser->setText(line.mid(20));
        }else if(line.startsWith("URxvt.perl-ext-common: ...,tab")){
            ui->checkBoxTabs->setChecked(true);
        }
    }
}
    file.close();
    updatePreview();
}
