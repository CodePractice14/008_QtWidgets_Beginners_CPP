#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->chkEnabled->setChecked(ui->txtTest->isEnabled());
    ui->chkReadOnly->setChecked(ui->txtTest->isReadOnly());
    ui->chkClearButton->setChecked(ui->txtTest->isClearButtonEnabled());

    QMetaEnum metaenum = QMetaEnum::fromType<QLineEdit::EchoMode>();

    for(int i =0 ; i <metaenum.keyCount(); i++)
    {
        ui->cmbEcho->addItem(metaenum.valueToKey(i), metaenum.value(i));
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_cmbEcho_currentIndexChanged(int index)
{
    QMetaEnum metaenum = QMetaEnum::fromType<QLineEdit::EchoMode>();
    int value = metaenum.keyToValue(ui->cmbEcho->currentText().toLocal8Bit().data());
    QLineEdit::EchoMode mode = static_cast<QLineEdit::EchoMode>(value);
    ui->txtTest->setEchoMode(mode);
}

void Dialog::on_txtDefault_textChanged(const QString &arg1)
{
    ui->txtTest->setText(arg1);
}

void Dialog::on_chkEnabled_toggled(bool checked)
{
    ui->txtTest->setEnabled(checked);
}

void Dialog::on_chkReadOnly_toggled(bool checked)
{
    ui->txtTest->setReadOnly(checked);
}

void Dialog::on_chkClearButton_toggled(bool checked)
{
    ui->txtTest->setClearButtonEnabled(checked);
}

void Dialog::on_buttonBox_accepted()
{
    QMessageBox::information(this, "Entered", "You entered "+ ui->txtTest->text());
    accept();
}
