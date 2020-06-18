#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    load();
}

Dialog::~Dialog()
{
    delete ui;
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

void Dialog::load()
{
    ui->txtName->setText("");
    ui->sbAge->setValue(0);
    ui->sbQty->setValue(0);

    QFile file("file.dat");

    if(!file.exists()) return;

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "error", "failed to open: "+file.errorString());
        return;
    }

    QDataStream stream(&file);

    QString name;
    int age;
    double qty;

    stream >> name;
    stream >> age;
    stream >> qty;

    ui->txtName->setText(name);
    ui->sbAge->setValue(age);
    ui->sbQty->setValue(qty);

    file.close();
}

void Dialog::save()
{
    QFile file("file.dat");
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "error", "failed to open: "+file.errorString());
        return;
    }

    QDataStream stream(&file);
    stream << ui->txtName->text();
    stream << ui->sbAge->value();
    stream << ui->sbQty->value();


    file.close();
    QMessageBox::information(this, "saved", "We have saved the file!");
}
