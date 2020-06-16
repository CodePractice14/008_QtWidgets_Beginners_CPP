#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->btn_1, &QPushButton::clicked, this, &Dialog::append);
    connect(ui->btn_2, &QPushButton::clicked, this, &Dialog::append);
    connect(ui->btn_3, &QPushButton::clicked, this, &Dialog::append);
    connect(ui->btn_4, &QPushButton::clicked, this, &Dialog::append);
    connect(ui->btn_5, &QPushButton::clicked, this, &Dialog::append);
    connect(ui->btn_6, &QPushButton::clicked, this, &Dialog::append);
    connect(ui->btn_7, &QPushButton::clicked, this, &Dialog::append);
    connect(ui->btn_8, &QPushButton::clicked, this, &Dialog::append);
    connect(ui->btn_9, &QPushButton::clicked, this, &Dialog::append);
    connect(ui->btn_0, &QPushButton::clicked, this, &Dialog::append);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::append()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(!btn) return;

    temp.append(btn->text());
    ui->lblNotify->setText("Typed: "+ temp);

    if(code.isEmpty())
    {
        ui->btnSave->setEnabled(true);
        ui->btnVerify->setEnabled(false);
    }
    else
    {
        ui->btnSave->setEnabled(false);
        ui->btnVerify->setEnabled(true);
    }
}


void Dialog::on_btnVerify_clicked()
{
    if(temp == code)
    {
        QMessageBox::information(this, "Code", "The codes match!");
    }
    else
    {
        QMessageBox::critical(this, "Code", "The codes dosen't match!");
    }

    temp.clear();
    ui->lblNotify->setText("Enter the Code and click verifiy");
}

void Dialog::on_btnSave_clicked()
{
    code = temp;
    temp.clear();
    ui->btnSave->setEnabled(false);
    ui->btnVerify->setEnabled(true);

    ui->lblNotify->setText("Code saved, please re-enter the code and click verify");
    QMessageBox::information(this, "Saved", ui->lblNotify->text());
}
