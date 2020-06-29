#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    init();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::init()
{
    QStringList headers;
    headers << "My Items";
    model.setHorizontalHeaderLabels(headers);

    QStandardItem *root = model.invisibleRootItem();

    for(int p=0; p < 100; p++)
    {
        QStandardItem *parentItem = new QStandardItem(QString("Parent %0").arg(p));
        root->appendRow(parentItem);

        for(int c=0; c < 10; c++)
        {
            QStandardItem *childItem = new QStandardItem(QString("Child %0%1").arg(p).arg(c));
            parentItem->appendRow(childItem);

            for(int s=0; s < 10; s++)
            {
                QStandardItem *subItem = new QStandardItem(QString("Item %0%1%2").arg(p).arg(c).arg(s));
                childItem->appendRow(subItem);
            }
        }
    }

    ui->treeView->setModel(&model);
}
