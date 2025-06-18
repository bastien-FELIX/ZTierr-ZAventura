#include <QFileDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString Zfilename = QFileDialog::getOpenFileName(this, "ZOpen Ze Zfile");
    QString Ztext = "<img src=\"" + Zfilename + "\" width=\"400\" height=\"500\" />";
    ui->Django->setText(Ztext);
}

