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
    QString message;
    message.append("Email: " + ui->leEmail->text() + "\r\n");
    message.append("Name: " + ui->leName->text() + "\r\n");

    QString food = getOptions(ui->grpFood);
    message.append(food);

    QString activites = getOptions(ui->grpActivies);
    message.append(activites);

    QMessageBox::information(this,"Details", message);
    accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

QString Dialog::getOptions(QGroupBox *group)
{
    QString value;
    foreach(QObject* object, group->children())
    {
        QCheckBox* chk = qobject_cast<QCheckBox*>(object);
        if(!chk) continue;

        if(chk->isChecked()) value.append(chk->text() + "\r\n");
    }

    return value;
}
