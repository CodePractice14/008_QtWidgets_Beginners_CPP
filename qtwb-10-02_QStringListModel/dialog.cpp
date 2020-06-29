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
    accept();
}

void Dialog::on_buttonBox_rejected()
{
    reject();
}

void Dialog::add()
{
    QString value = QInputDialog::getText(this, "Add item", "Enter item to add");
    if(value.isEmpty()) return;

    //Use the inherited functiuons of QAbastractModel

    if(model.insertRow(model.rowCount()))
    {
        QModelIndex index = model.index(model.rowCount() -1, 0);
        model.setData(index, value);
    }
}

void Dialog::remove()
{
    QModelIndex index = ui->listView->currentIndex();
    model.removeRow(index.row());
}

void Dialog::init()
{
    //Set up the data
    list.append("Cat");
    list.append("Dog");
    list.append("Dinozaur");
    list.append("Lizzard");
    list.append("Bird");

    //Set up the model --> using the data
    model.setStringList(list);

    //Set up the view
    ui->listView->setModel(&model);

    //Build our UI
    QPushButton *btnAdd = new QPushButton("Add", this);
    QPushButton *btnRemove = new QPushButton("Remove", this);

    connect(btnAdd, &QPushButton::clicked, this, &Dialog::add);
    connect(btnRemove, &QPushButton::clicked, this, &Dialog::remove);

    ui->buttonBox->addButton(btnAdd, QDialogButtonBox::ButtonRole::ActionRole);
    ui->buttonBox->addButton(btnRemove, QDialogButtonBox::ButtonRole::ActionRole);
}
