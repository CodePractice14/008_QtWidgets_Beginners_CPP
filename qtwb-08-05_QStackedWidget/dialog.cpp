#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    init();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_buttonBox_accepted()
{
    QMessageBox::information(this,"Hello",ui->txtFirst->text());
    accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

void Dialog::next()
{
    int index = ui->stackedWidget->currentIndex();
    index++;
    if(index >= ui->stackedWidget->count()) index = ui->stackedWidget->count() -1;

    ui->stackedWidget->setCurrentIndex(index);
    checkButtons();
}

void Dialog::back()
{
    int index = ui->stackedWidget->currentIndex();
    index--;
    if(index <= 0) index = 0;

    ui->stackedWidget->setCurrentIndex(index);
    checkButtons();
}

void Dialog::init()
{
    btnNext = new QPushButton("Next", this);
    btnBack = new QPushButton("Back", this);

    connect(btnNext,&QPushButton::clicked,this,&Dialog::next);
    connect(btnBack,&QPushButton::clicked,this,&Dialog::back);

    ui->buttonBox->addButton(btnBack, QDialogButtonBox::ButtonRole::ActionRole);
    ui->buttonBox->addButton(btnNext, QDialogButtonBox::ButtonRole::ActionRole);

    QWidget *widget = new QWidget(this);
    QLabel *lblNothing = new QLabel("Add your controls here!", this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(lblNothing);
    widget->setLayout(layout);
    ui->stackedWidget->addWidget(widget);

    ui->stackedWidget->setCurrentIndex(0);

    checkButtons();
}

void Dialog::checkButtons()
{
    //First Page
    if(ui->stackedWidget->currentIndex() == 0)
    {
        btnBack->setEnabled(false);
        btnNext->setEnabled(true);
        return;
    }

    //Last Page
    if(ui->stackedWidget->currentIndex() >= ui->stackedWidget->count() -1)
    {
        btnBack->setEnabled(true);
        btnNext->setEnabled(false);
        return;
    }

    //Others
    btnBack->setEnabled(true);
    btnNext->setEnabled(true);
}







