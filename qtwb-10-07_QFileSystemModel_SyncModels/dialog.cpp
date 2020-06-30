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

void Dialog::init()
{
    model.setRootPath(dir.currentPath());
    ui->treeView->setModel(&model);
    ui->listView->setModel(&model);

    for(int i=1; i< model.columnCount(); i++)
    {
        ui->treeView->hideColumn(i);
    }

    ui->listView->setViewMode(QListView::ViewMode::ListMode);
}


void Dialog::on_treeView_activated(const QModelIndex &index)
{
    ui->listView->setRootIndex(index);
}

void Dialog::on_listView_activated(const QModelIndex &index)
{
    ui->listView->setRootIndex(index);
    ui->treeView->setCurrentIndex(index);
    ui->treeView->expand(index);

}
