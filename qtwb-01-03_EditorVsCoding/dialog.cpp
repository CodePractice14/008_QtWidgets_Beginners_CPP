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


void Dialog::on_btnAccept_clicked()
{
    QMessageBox::information(this, "Name", "Hello there General " + ui->txtName->text());
    this->accept();
}
