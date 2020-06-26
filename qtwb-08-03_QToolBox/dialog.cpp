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

void Dialog::itemDoubleClicked(QListWidgetItem *item)
{
    QString url = item->data(Qt::ItemDataRole::UserRole).toString();
    QDesktopServices::openUrl(QUrl(url));
}

void Dialog::init()
{
    //clear it out
    while(ui->toolBox->count() > 0)
    {
        ui->toolBox->removeItem(0);
    }

    //Add pages
    addCategory("News");
    addCategory("Social Media");
    addCategory("Search Engines");

    addNews();
    addSocial();
    addSearch();
}

void Dialog::addCategory(QString name)
{
    QListWidget * list = new QListWidget(this);
    ui->toolBox->addItem(list,QIcon(":/files/images/world.png"),name);

    connect(list,&QListWidget::itemDoubleClicked,this, &Dialog::itemDoubleClicked);
}

void Dialog::addLink(QListWidget *list, QString name, QString url)
{
    QListWidgetItem *itm = new QListWidgetItem(QIcon(":/files/images/page_world.png"), name);
    itm->setData(Qt::ItemDataRole::UserRole,url);
    list->addItem(itm);
}

void Dialog::addNews()
{
    QListWidget *list = qobject_cast<QListWidget*>(ui->toolBox->widget(0));

    if(!list)
    {
        qWarning() << "Could not find News List!";
        return;
    }

    addLink(list,"CNN", "http://www.cnn.com");
    addLink(list,"Fox", "http://www.foxnews.com");
    addLink(list,"Google", "http://www.google.com");
}

void Dialog::addSocial()
{
    QListWidget *list = qobject_cast<QListWidget*>(ui->toolBox->widget(1));

    if(!list)
    {
        qWarning() << "Could not find Social List!";
        return;
    }

    addLink(list,"Facebook", "http://www.facebook.com");
    addLink(list,"YouTube", "http://www.youtube.com");

}

void Dialog::addSearch()
{
    QListWidget *list = qobject_cast<QListWidget*>(ui->toolBox->widget(2));

    if(!list)
    {
        qWarning() << "Could not find Search List!";
        return;
    }

    addLink(list,"Google", "http://www.google.com");
    addLink(list,"Yahoo", "http://www.yahoo.com");
}

