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


void Dialog::on_buttonBox_accepted()
{
    QMessageBox::information(this,"Selected","You have selected: \r\n" + ui->lineEdit->text());
    accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

void Dialog::on_pushButton_clicked()
{
    Selections *dlg = new Selections(this);

    //Set the default
    dlg->setSelected(ui->lineEdit->text());

    //Exec (Show on screen) the dialog
    dlg->exec();

    //Read back the new selection
    ui->lineEdit->setText(dlg->selected());

}
