#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QListWidgetItem>
#include <QImage>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_buttonBox_accepted();

    void on_listWidget_itemSelectionChanged();

private:
    Ui::Dialog *ui;

    void load();
    void scan(QFileInfoList list);
};
#endif // DIALOG_H
