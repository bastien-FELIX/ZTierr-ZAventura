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
