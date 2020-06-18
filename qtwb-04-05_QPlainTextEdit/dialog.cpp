#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //Allow resise
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowContextHelpButtonHint;
    flags |= Qt::WindowCloseButtonHint;

    setWindowFlags(flags);

    QPushButton *btnCopy = new QPushButton("Copy", this);
    QPushButton *btnCut = new QPushButton("Cut", this);
    QPushButton *btnPaste = new QPushButton("Paste", this);
    QPushButton *btnUndo = new QPushButton("Undo", this);
    QPushButton *btnRedo = new QPushButton("Redo", this);

    ui->buttonBox->addButton(btnCopy, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnCut, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnPaste, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnUndo, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnRedo, QDialogButtonBox::ActionRole);

    connect(btnCopy, &QPushButton::clicked, ui->plainTextEdit, &QPlainTextEdit::copy);
    connect(btnCut, &QPushButton::clicked, ui->plainTextEdit, &QPlainTextEdit::cut);
    connect(btnPaste, &QPushButton::clicked, ui->plainTextEdit, &QPlainTextEdit::paste);
    connect(btnUndo, &QPushButton::clicked, ui->plainTextEdit, &QPlainTextEdit::undo);
    connect(btnRedo, &QPushButton::clicked, ui->plainTextEdit, &QPlainTextEdit::redo);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_plainTextEdit_textChanged()
{
    m_saved = false;
}
void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text().contains("Open"))
    {
        load();
        return;
    }

    if(button->text().contains("Save"))
    {
        save();
        return;
    }
}

void Dialog::load()
{
    ui->plainTextEdit->clear();
    QFile file("file.txt");

    if(!file.exists()) return;

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "error", "Something bad happend: "+ file.errorString());
        return;
    }

    QTextStream stream(&file);
    ui->plainTextEdit->setPlainText(stream.readAll());

    file.close();
    m_saved = true;
}
void Dialog::save()
{
    QFile file("file.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "error", "Something bad happend: "+ file.errorString());
    }

    QTextStream stream(&file);
    stream << ui->plainTextEdit->toPlainText();

    file.close();
    m_saved = true;

    QMessageBox::information(this, "Succes", "We saved the file!");
}

void Dialog::closeEvent(QCloseEvent *event)
{
    if(!m_saved)
    {
        QMessageBox::question(this, "Confirm","File not saved. Are you sure you want to quit?");

    }
    else
    {

    }
}
