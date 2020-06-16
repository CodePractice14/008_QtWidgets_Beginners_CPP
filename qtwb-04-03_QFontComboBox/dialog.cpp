#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    init();
    load();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_fontComboBox_currentFontChanged(const QFont &f)
{
    if(ui->lineEdit->font().toString() != f.toString())
    {
        ui->lineEdit->setFont(f);
    }
}

void Dialog::on_buttonBox_accepted()
{
    save();
    accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

void Dialog::init()
{
    ui->fontComboBox->setCurrentFont(ui->lineEdit->font());
}

void Dialog::load()
{
    QSettings settings;
    QString value = settings.value("font", "").toString();
    QFont font;

    if(!value.isEmpty())
    {
        if(font.fromString(value))
        {
            ui->fontComboBox->setCurrentFont(font);
        }
    }
}

void Dialog::save()
{
    QSettings settings;
    settings.setValue("font", ui->lineEdit->font().toString());
}
