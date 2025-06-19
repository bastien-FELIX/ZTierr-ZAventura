#include "mainwindow.h"
#include <QFileDialog>
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

    int l = Zfilename.length();
    QString ZfileFormat;

    if (l >= 4) {
        ZfileFormat = QString(Zfilename[l - 4]) + QString(Zfilename[l - 3]) + QString(Zfilename[l - 2]) + QString(Zfilename[l - 1]);

        if (ZfileFormat == ".png" || ZfileFormat == ".jpg" || ZfileFormat == "jpeg") {
            QString Ztext = "<img src=\"" + Zfilename + "\" width=\"400\" height=\"500\" />";
            ui->Django->setText(Ztext);
        } else {
            ui->Django->setText("Le Z a volé les autres formats de fichiers. \n\nMerci de donner une image sous le bon format");
        }
    } else {
        ui->Django->setText("Le Z a volé le fichier sélectionné. \n\nMerci de bien sélectionner un fichier.");
    }



}
