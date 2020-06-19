#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnLoad_clicked()
{
    QFile file(":/documents/files/files/file.txt");
    if(!file.exists())
    {
        QMessageBox::critical(this,"File not found","Sorry, we could not find that file!");
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    QTextStream stream(&file);
    ui->plainTextEdit->setPlainText(stream.readAll());
    file.close();
}

void Dialog::on_btnSave_clicked()
{
    QFile file(":/documents/files/files/file.txt");
    if(!file.exists())
    {
        QMessageBox::critical(this,"File not found","Sorry, we could not find that file!");
        return;
    }

    if(!file.isWritable())
    {
        QMessageBox::critical(this,"Non_Writeable","Can not write to file!!!");
        return;
    }
    else
    {
        QMessageBox::information(this,"Writeable","Can write to file!!!");
    }

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << ui->plainTextEdit->toPlainText();
    file.close();
}
