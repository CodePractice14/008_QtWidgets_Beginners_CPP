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


void Dialog::on_btnCancel_clicked()
{
    QMessageBox::critical(this,"Really?", "You do not want icecream???");
    reject();
}

void Dialog::on_btnOk_clicked()
{
    QString icecream = getOptions(ui->grpIceCream);
    QString toppings = getOptions(ui->grpToppings);
    QString syrup = getOptions(ui->grpSyrup);
    QString size = getOptions(ui->grpSize);

    QString order;
    order += "Order: \r\n";
    order += "Size: "+ size +"  \r\n";
    order += "Icecream: "+ icecream +"  \r\n";
    order += "Toppings: "+ toppings +"  \r\n";
    order += "Syrup: "+ syrup +"  \r\n";

    QMessageBox::information(this, "Your Order", order);

    accept();
}

QString Dialog::getOptions(QObject *obj)
{
    QString value = "none";

    QList<QRadioButton*> lst = obj->findChildren<QRadioButton*>(QString(), Qt::FindDirectChildrenOnly);

    foreach (QRadioButton* rdo, lst)
    {
        if(rdo->isChecked())
        {
            value = rdo->text();
            break;
        }
    }

    return value;
}


