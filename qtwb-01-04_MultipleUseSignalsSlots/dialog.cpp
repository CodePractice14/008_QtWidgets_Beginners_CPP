#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->btnConnect, &QPushButton::clicked, this, &Dialog::doStuff);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::doStuff()
{
    qInfo() << "Clicked " << QDateTime::currentDateTime().toString("dd.MM.yyyy");
    accept(); //Will CLOSE the Form !
}


void Dialog::on_btnEditor_clicked()
{
    qDebug() <<"Extra stuff!";
    doStuff();
}
