#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtDebug>
#include <QStandardItemModel>
#include <QStandardItem>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

    QStandardItemModel model;

    void init();
};

#endif // DIALOG_H
