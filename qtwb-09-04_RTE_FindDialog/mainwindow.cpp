#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   setCentralWidget(ui->textEdit);

   m_path = "";
   m_changed = false;
   newFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    checksave();
    newFile();
}

void MainWindow::on_actionOpen_triggered()
{
    checksave();
    openFile();
}

void MainWindow::on_actionSave_triggered()
{
    saveFile(m_path);
}

void MainWindow::on_actionSave_As_triggered()
{
    saveFileAs();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionFind_triggered()
{
    FindDialog *dlg = new FindDialog(this);
    if(!dlg->exec()) return;

    QTextDocument::FindFlags flags;
    if(dlg->caseSensitive()) flags = flags | QTextDocument::FindFlag::FindCaseSensitively;
    if(dlg->wholeWords()) flags = flags | QTextDocument::FindFlag::FindWholeWords;
    if(dlg->backwards()) flags = flags | QTextDocument::FindFlag::FindBackward;

    bool value = ui->textEdit->find(dlg->text(),flags);
    if(!value) QMessageBox::information(this,"Not Found","Was not able to find: " + dlg->text());
}

void MainWindow::on_actionReplace_triggered()
{

}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionZoom_in_triggered()
{
    ui->textEdit->zoomIn(1);
}

void MainWindow::on_actionZoom_out_triggered()
{
    ui->textEdit->zoomOut(1);
}

void MainWindow::on_actionBold_triggered()
{

}

void MainWindow::on_actionItalic_triggered()
{

}

void MainWindow::on_actionUnderline_triggered()
{

}

void MainWindow::on_actionStrike_triggered()
{

}

void MainWindow::on_actionColor_triggered()
{

}

void MainWindow::on_actionFont_triggered()
{

}

void MainWindow::on_actionHelp_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_textEdit_textChanged()
{
    m_changed = true;
}

void MainWindow::newFile()
{
    ui->textEdit->clear();
    ui->statusbar->showMessage("New File");
    m_path = "";
    m_changed = false;
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this,"Open File");
    if(path.isEmpty()) return;

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    ui->textEdit->setHtml(stream.readAll());
    file.close();

    m_path = path;
    ui->statusbar->showMessage(m_path);
    m_changed = false;
}

void MainWindow::saveFile(QString path)
{
    if(path.isEmpty())
    {
        saveFileAs();
        return;
    }

    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error", file.errorString());
        ui->statusbar->showMessage("Error could not save file!");
        saveFileAs();
        return;
    }

    QTextStream stream(&file);
    stream << ui->textEdit->toHtml();
    file.close();

    m_path = path;
    ui->statusbar->showMessage(m_path);
    m_changed = false;
}

void MainWindow::saveFileAs()
{
    QString path = QFileDialog::getSaveFileName(this,"Save File");
    if(path.isEmpty()) return;
    saveFile(path);
}

void MainWindow::checksave()
{
    if(!m_changed) return;

    QMessageBox::StandardButton value = QMessageBox::question(this,"Save File?","You have un-saved changes would you like to save them?");

    if(value != QMessageBox::StandardButton::Yes) return;

    if(m_path.isEmpty())
    {
        saveFileAs();
    }
    else
    {
        saveFile(m_path);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

