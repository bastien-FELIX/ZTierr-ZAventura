#include "mainwindow.h"
#include <QFileDialog>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    introLayout=new QGridLayout();



    QLabel *l=new QLabel("Icone (Qui parle ?)");
    QComboBox *cb=new QComboBox();

    QGridLayout *gl =new QGridLayout();
    QGridLayout *gl2 =new QGridLayout();

    QSpacerItem *sp=new QSpacerItem(0,0, QSizePolicy::Expanding);
    QLabel *l2=new QLabel("Dialogue :");
    QTextEdit* te=new QTextEdit();
    te->setMinimumHeight(100);

    gl->addWidget(l,0,0);
    gl->addWidget(cb,0,1);
    gl->addItem(sp,0,2);

    vectComboIntro.push_back(cb);
    vectTextIntro.push_back(te);



    introLayout->addLayout(gl,0,0);
    gl2->addWidget(l2, 0, 0);
    gl2->addWidget(te, 0,1);

    introLayout->addLayout(gl2,1,0);

    QWidget* introWidget = new QWidget();
    introWidget->setLayout(introLayout);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(introWidget);



    ui->setupUi(this);
    ui->gridLayoutIntroDialogue->addWidget(scrollArea);



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
    } else {
        ui->Django->setText("Le Z a volé le fichier sélectionné. \n\nMerci de bien sélectionner un fichier.");
        return;
    }

    if (ZfileFormat == ".png" || ZfileFormat == ".jpg" || ZfileFormat == "jpeg") {
        Zimage = Zfilename;
        ui->Django->setText(ZimageToHtml());
    } else {
        ui->Django->setText("Le Z a volé les autres formats de fichiers. \n\nMerci de donner une image sous le bon format");
    }
}


void MainWindow::on_btPlusIntro_clicked()
{

    QLabel *l=new QLabel("Icone (Qui parle ?)");
    QComboBox *cb=new QComboBox();

    QGridLayout *gl =new QGridLayout();
    QGridLayout *gl2 =new QGridLayout();

    QSpacerItem *sp=new QSpacerItem(0,0, QSizePolicy::Expanding);
    QLabel *l2=new QLabel("Dialogue :");
    QTextEdit* te=new QTextEdit();
    te->setMinimumHeight(100);

    gl->addWidget(l,0,0);
    gl->addWidget(cb,0,1);
    gl->addItem(sp,0,2);

    vectComboIntro.push_back(cb);
    vectTextIntro.push_back(te);


    int line = introLayout->rowCount();

    introLayout->addLayout(gl,line,0);
    gl2->addWidget(l2, 0, 0);
    gl2->addWidget(te, 0,1);

    introLayout->addLayout(gl2,line+1,0);
}

QString MainWindow::ZimageToHtml() {
    return "<img src=\"" + Zimage + "\" width=\"400\" height=\"500\" />";
}

void MainWindow::on_actionExporter_triggered()
{
    QString Ztitle = ui->lineEdit->displayText();
    QString Zcity = ui->lineEdit_2->displayText();
    QString Zdept = ui->lineEdit_3->displayText();
    QString Ztime = ui->lineEdit_4->displayText();
    QString Zdifficulty = QString::number(ui->spinBox->value());
    QString Zlength = ui->lineEdit_5->displayText();

    QFile Zfile(QFileDialog::getOpenFileName(this, "ZOpen Ze Zfile"));

    if (!Zfile.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Le Z a volé le fichier: " + Zfile.errorString());
        return;
    }

    QTextStream Zstream(&Zfile);

    Zstream << Ztitle + "\n" + Zcity + "\n" + Zdept + "\n" + Zdifficulty + "\n" + Ztime + "\n" + Zlength + "\n" + Zimage;

    for (int i = 0; i < vectTextIntro.size(); i++) {
        Zstream << vectComboIntro[i]->currentText() + "\n";
        Zstream << vectTextIntro[i]->toPlainText() + "\n#";
    }
    
    Zfile.close();
}


void MainWindow::on_actionImporter_triggered()
{
    QFile Zfile(QFileDialog::getOpenFileName(this, "ZOpen Ze Zfile"));

    if (!Zfile.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Le Z a volé le fichier: " + Zfile.errorString());
        return;
    }

    QTextStream Zstream(&Zfile);
    QString line;


    for (int i = 0; i < 7; i++) {
        line = Zstream.readLine();

        switch(i) {
        case 0:
            ui->lineEdit->setText(line);
        case 1:
            ui->lineEdit_2->setText(line);
        case 2:
            ui->lineEdit_3->setText(line);
        case 3:
            ui->spinBox->setValue(line.toInt());
        case 4:
            ui->lineEdit_4->setText(line);
        case 5:
            ui->lineEdit_5->setText(line);
        case 6:
            Zimage = line;
            ui->Django->setText(ZimageToHtml());
        }
    }

    Zfile.close();
}


void MainWindow::on_actionExporter_en_html_triggered()
{
    QString Ztitle = ui->lineEdit->displayText();
    QString Zcity = ui->lineEdit_2->displayText();
    QString Zdept = ui->lineEdit_3->displayText();
    QString Ztime = ui->lineEdit_4->displayText();
    QString Zdifficulty = QString::number(ui->spinBox->value());
    QString Zlength = ui->lineEdit_5->displayText();

    QFile Zfile(QFileDialog::getOpenFileName(this, "ZOpen Ze Zfile"));

    if (!Zfile.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Le Z a volé le fichier: " + Zfile.errorString());
        return;
    }

    QTextStream Zstream(&Zfile);

    Zstream << "<!DOCTYPE html> <html> <head> <title> " + Ztitle + "</title> </head> <body>" + "\n";

    Zstream << Ztitle + " " + Zcity + "\n" + Zdept + "\n" + Zdifficulty + "\n" + Ztime + "\n" + Zlength + "\n" + ZimageToHtml();

    Zstream << "\n</body> </html>";

    Zfile.close();
}
