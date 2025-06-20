#include <QFileDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QLabel"
#include "QLayoutItem"
#include <QSizePolicy>
#include <QScrollArea>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /******************************************* INTRO TAB *******************************************/
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


    /******************************************* ETAPES TAB *******************************************/

    // QLabel *le=new QLabel("Titre : ");
    // QTextEdit *t =new QTextEdit();
    // vectTextEtapes.push_back(t);
    // QComboBox *comboNS = new QComboBox();
    // QLineEdit *lncoordNS=new QLineEdit();
    // QComboBox *comboEO=new QComboBox();
    // QLineEdit *lncoordEO=new QLineEdit();

    // QGridLayout *titleLayout=new QGridLayout();
    
    // titleLayout->addWidget(le,0,0);
    // titleLayout->addWidget(t,1,0);
    // titleLayout->addWidget(comboNS,2,0);
    // titleLayout->addWidget(lncoordNS,3,0);
    




    // QWidget* etapesWidget = new QWidget();
    // etapesWidget->setLayout(etapesLayout);

    // QScrollArea *scrollAreaEtapes = new QScrollArea();
    // scrollAreaEtapes->setWidgetResizable(true);
    // scrollAreaEtapes->setWidget(etapesWidget);


    ui->setupUi(this);
    // ui->gridLayoutEtapes->addWidget(scrollAreaEtapes);
    ui->gridLayoutIntroDialogue->addWidget(scrollArea);



}

MainWindow::~MainWindow()
{
    delete ui;

}




// void on_pushbutton_clicked()
// {
//     MyCustomFrame *frame = new MyCustomFrame(this);
//     ui->verticalLayout->addWidget(frame);
//     // do other init stuff
// }

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

