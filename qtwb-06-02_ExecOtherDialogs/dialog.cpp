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


void Dialog::on_btnWith_clicked()
{
    //Notice you can not select the parent - this is modal!!!
    Dialog2 *dialog = new Dialog2(this);
    dialog->exec();
}

void Dialog::on_btnWithout_clicked()
{
     //Pointer does not delete itself!!!
    Dialog2 *dialog = new Dialog2(nullptr);
    dialog->exec();


}
