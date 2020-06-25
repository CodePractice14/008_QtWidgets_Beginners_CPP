#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toolBar->setMovable(false);
    ui->toolBar->setFloatable(false);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->actionCopy, &QAction::triggered, ui->plainTextEdit, &QPlainTextEdit::copy);
    connect(ui->actionCut, &QAction::triggered, ui->plainTextEdit, &QPlainTextEdit::cut);
    connect(ui->actionPaste, &QAction::triggered, ui->plainTextEdit, &QPlainTextEdit::paste);
    connect(ui->actionSelect_All, &QAction::triggered, ui->plainTextEdit, &QPlainTextEdit::selectAll);

    connect(ui->actionSelect_None, &QAction::triggered, this, &MainWindow::selectNone);

    this->setCentralWidget(ui->splitter);

    setupStatusBar();

    newFile();
    m_saved = true;

    for(int i = 0; i < 100; i ++)
    {
        QString title = "Item number " + QString::number(i);
        ui->listWidget->addItem(title);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    ui->plainTextEdit->clear();
    m_filename.clear();
    m_saved = false;

    updateStatus("New File");
}

void MainWindow::openFile()
{
    QString temp = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*txt);;All Files (*,*)");

    if(temp.isEmpty()) return;

    m_filename = temp;

    QFile file(m_filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        newFile();
        QMessageBox::critical(this, "Error",file.errorString());
        return;
    }

    QTextStream stream(&file);
    ui->plainTextEdit->setPlainText(stream.readAll());
    file.close();

    m_saved = true;
    updateStatus(m_filename);
}

void MainWindow::saveFile()
{
    if(m_filename.isEmpty())
    {
        saveFileAs();
        return;
    }

    QFile file(m_filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << ui->plainTextEdit->toPlainText();
    file.close();

    m_saved = true;
    updateStatus(m_filename);
}

void MainWindow::saveFileAs()
{
    QString temp = QFileDialog::getSaveFileName(this, "Open File", QString(), "Text Files (*txt);;All Files (*,*)");
    if(temp.isEmpty()) return;
    m_filename = temp;

    saveFile();
}

void MainWindow::selectNone()
{
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    int pos = cursor.position();
    cursor.clearSelection();
    cursor.setPosition(pos, QTextCursor::MoveMode::KeepAnchor);
    ui->plainTextEdit->setTextCursor(cursor);
}


void MainWindow::on_actionToolbar_top_triggered()
{
    addToolBar(Qt::ToolBarArea::TopToolBarArea, ui->toolBar);
}

void MainWindow::on_actionToolbar_bottom_triggered()
{
    addToolBar(Qt::ToolBarArea::BottomToolBarArea, ui->toolBar);
}

void MainWindow::on_actionToolbar_left_triggered()
{
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, ui->toolBar);
}

void MainWindow::on_actionToolbar_right_triggered()
{
    addToolBar(Qt::ToolBarArea::RightToolBarArea, ui->toolBar);
}

void MainWindow::on_actionToolbar_floatable_toggled(bool arg1)
{
    ui->toolBar->setFloatable(arg1);
}

void MainWindow::on_actionToolbar_movable_toggled(bool arg1)
{
    ui->toolBar->setMovable(arg1);
}

void MainWindow::setupStatusBar()
{
    QLabel *lblIcon = new QLabel(this);
    lblIcon->setPixmap(QPixmap(":/files/images/new.png"));
    ui->statusbar->addWidget(lblIcon);

    QLabel *lblStatus = new QLabel(this);
    lblStatus->setText("Not Saved:");
    ui->statusbar->addWidget(lblStatus);

    QLabel *lblFile = new QLabel(this);
    lblFile->setText("New");
    ui->statusbar->addWidget(lblFile);

}

void MainWindow::updateStatus(QString message)
{
    foreach (QObject* obj, ui->statusbar->children())
    {
        qDebug()<< obj;
    }

    QLabel *lblIcon = qobject_cast<QLabel*>(ui->statusbar->children().at(1));
    QLabel *lblStatus = qobject_cast<QLabel*>(ui->statusbar->children().at(2));
    QLabel *lblFile = qobject_cast<QLabel*>(ui->statusbar->children().at(4));

    if(m_saved)
    {
       lblIcon->setPixmap(QPixmap(":/files/images/save.png"));
       lblStatus->setText("Saved:");
    }
    else
    {
        lblIcon->setPixmap(QPixmap(":/files/images/new.png"));
        lblStatus->setText("Not Saved:");
    }
    lblFile->setText(m_filename);
}

void MainWindow::on_plainTextEdit_textChanged()
{
    m_saved = false;
    if(m_filename.isEmpty())
    {
        updateStatus("New File!");
    }
    else
    {
        updateStatus(m_filename);
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText(item->text());
}

void MainWindow::on_actionAnimals_triggered()
{
    QStringList options;
    options << "Cats" << "Dog" << "Bird" << "Fish";

    QScopedPointer<Dialog> dlg(new Dialog());
    dlg.data()->setList(options);
    dlg.data()->exec();

    ui->plainTextEdit->insertPlainText(dlg.data()->selected());
}

void MainWindow::on_actionShapes_triggered()
{
    QStringList options;
    options << "Square" << "Circle" << "Triangle" << "Pentagram";

    QScopedPointer<Dialog> dlg(new Dialog());
    dlg.data()->setList(options);
    dlg.data()->exec();

    ui->plainTextEdit->insertPlainText(dlg.data()->selected());
}

void MainWindow::on_actionFood_triggered()
{
    QStringList options;
    options << "Ice Cream" << "KFC" << "Shaorma" << "Burger";

    QScopedPointer<Dialog> dlg(new Dialog());
    dlg.data()->setList(options);
    dlg.data()->exec();

    ui->plainTextEdit->insertPlainText(dlg.data()->selected());
}
