#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QSizePolicy>
#include <QJsonObject>
#include <string>
#include "./ui_mainwindow.h"
#include "QLabel"
#include "QLayoutItem"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /******************************************* INTRO TAB *******************************************/
    introLayout = new QGridLayout();

    QLabel *l = new QLabel("Icone (Qui parle ?)");
    QComboBox *cb = new QComboBox();

    QGridLayout *gl = new QGridLayout();
    QGridLayout *gl2 = new QGridLayout();

    QSpacerItem *sp = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    QLabel *l2 = new QLabel("Dialogue :");
    QTextEdit *te = new QTextEdit();

    te->setMinimumHeight(100);

    gl->addWidget(l, 0, 0);
    gl->addWidget(cb, 0, 1);
    gl->addItem(sp, 0, 2);
    cb->addItem("Le Z");
    cb->addItem("Zart");


    vectComboIntro.push_back(cb);
    vectTextIntro.push_back(te);

    introLayout->addLayout(gl, 0, 0);
    gl2->addWidget(l2, 0, 0);
    gl2->addWidget(te, 0, 1);

    introLayout->addLayout(gl2, 1, 0);

    QWidget *introWidget = new QWidget();
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
    QLabel *l = new QLabel("Icone (Qui parle ?)");
    QComboBox *cb = new QComboBox();

    QGridLayout *gl = new QGridLayout();
    QGridLayout *gl2 = new QGridLayout();

    QSpacerItem *sp = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    QLabel *l2 = new QLabel("Dialogue :");
    QTextEdit *te = new QTextEdit();
    te->setMinimumHeight(100);

    gl->addWidget(l, 0, 0);
    gl->addWidget(cb, 0, 1);
    gl->addItem(sp, 0, 2);
    cb->addItem("Le Z");
    cb->addItem("Zart");

    vectComboIntro.push_back(cb);
    vectTextIntro.push_back(te);

    int line = introLayout->rowCount();

    introLayout->addLayout(gl, line, 0);
    gl2->addWidget(l2, 0, 0);
    gl2->addWidget(te, 0, 1);

    introLayout->addLayout(gl2, line + 1, 0);
}

QString MainWindow::ZimageToHtml()
{
    return "<img src=\"" + Zimage + "\" width=\"400\" height=\"500\" />";
}

void MainWindow::on_actionExporter_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        QFile saveFile(fileName);

        if (!saveFile.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open save file.");
        }

        QJsonObject json = toJson();
        saveFile.write(QJsonDocument(json).toJson());
    }
}

void MainWindow::on_actionExporter_en_html_triggered()
{
    QString Ztitle = ui->lineEdit->displayText();
    QString Zcity = ui->lineEdit_2->displayText();
    QString Zdept = ui->lineEdit_3->displayText();
    QString Ztime = ui->lineEdit_4->displayText();
    int Zdifficulty = ui->spinBox->value();
    QString Zlength = ui->lineEdit_5->displayText();

    QFile Zfile(QFileDialog::getSaveFileName(this, "ZOpen Ze Zfile"));

    if (!Zfile.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Le Z a volé le fichier: " + Zfile.errorString());
        return;
    }

    QTextStream Zstream(&Zfile);

    Zstream << "<!DOCTYPE html> <html> <head> <title> " + Ztitle + "</title> </head> <body>\n";

    // infos parcours

    Zstream << "<h2>Ville : " << Zcity << "</h2>";
    Zstream << "<h2>Département : " << Zdept << "</h2>";
    Zstream << "<h2>Difficulté : ";

    for (int i = 0; i < Zdifficulty; i++) {
        Zstream << "*";
    }

    Zstream << "</h2>";

    Zstream << "<h2>Durée : " << Ztime<< "h</h2>";
    Zstream << "<h2>Longueur : " << Zlength << "km</h2>";


    Zstream << "<h1> Intro </h1>";

    // intro

    for (int i = 0; i < vectTextIntro.size(); i++) {
        Zstream << "<h2>" + vectComboIntro[i]->currentText() + "</h2>";
        Zstream << "<p>" + vectTextIntro[i]->toPlainText() + "</p>";
    }


    // about

    Zstream << "<h1>A propos</h1>";

    Zstream << "<h2>Organisation : " + ui->lineEdit_orga->displayText() + "</h2>";
    Zstream << "<h2>Adresse : " + ui->lineEdit_adresse->displayText() + "</h2>";
    Zstream << "<h2>Code postal & Ville : " + ui->lineEdit_ville->displayText() + "</h2>";
    Zstream << "<h2>Num. téléphone : " + ui->lineEdit_tel->displayText() + "</h2>";
    Zstream << "<h2>Adresse e-mail : " + ui->lineEdit_mail->displayText() + "</h2>";
    Zstream << "<h2>Site web : <a href=\"" + ui->lineEdit_web->displayText() + "\">" + ui->lineEdit_web->displayText() + "</a> </h2>";

    Zstream << "\n</body> </html>\n\n";
    Zfile.close();
}

QJsonObject MainWindow::toJson() const
{
    QJsonObject json;
    json["ztitl"] = ui->lineEdit->displayText();
    json["zcity"] = ui->lineEdit_2->displayText();
    json["zdept"] = ui->lineEdit_3->displayText();
    json["ztime"] = ui->lineEdit_4->displayText();
    json["zdiff"] = QString::number(ui->spinBox->value());
    json["zleng"] = ui->lineEdit_5->displayText();
    return json;
}

void MainWindow::fromJson(const QJsonObject &json)
{
    if (const QJsonValue v = json["ztitl"]; v.isString())
        ui->lineEdit->setText(v.toString());
    if (const QJsonValue v = json["zcity"]; v.isString())
        ui->lineEdit_2->setText(v.toString());
    if (const QJsonValue v = json["zdept"]; v.isString())
        ui->lineEdit_3->setText(v.toString());
    if (const QJsonValue v = json["ztime"]; v.isString())
        ui->lineEdit_4->setText(v.toString());
    if (const QJsonValue v = json["zdiff"]; v.isString())
        ui->spinBox->setValue((v.toString()).toInt());
    if (const QJsonValue v = json["zleng"]; v.isString())
        ui->lineEdit_5->setText(v.toString());
}

void MainWindow::loadSave()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        QFile loadFile(fileName);
        if (!loadFile.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open save file.");
        }
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
        fromJson(loadDoc.object());
    }
}

void MainWindow::on_actionImporter_triggered()
{
    loadSave();
}
