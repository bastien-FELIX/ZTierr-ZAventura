#include "mainwindow.h"
#include <QFileDialog>
#include <QJsonArray>
#include <QMessageBox>
#include <QScrollArea>
#include <QSizePolicy>
#include "./ui_mainwindow.h"
#include "QLabel"
#include "QLayoutItem"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /******************************************* INTRO TAB *******************************************/
    introLayout = new QGridLayout();

    setWindowIcon(QIcon("../../z.png"));

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
    etapesLayout = new QGridLayout();

    QWidget *etapesWidget = new QWidget();
    etapesWidget->setLayout(etapesLayout);

    QScrollArea *scrollAreaEtapes = new QScrollArea();
    scrollAreaEtapes->setWidgetResizable(true);
    scrollAreaEtapes->setWidget(etapesWidget);

    ui->setupUi(this);
    ui->gridLayoutEtapes->addWidget(scrollAreaEtapes);
    ui->gridLayoutIntroDialogue->addWidget(scrollArea);
}

MainWindow::~MainWindow()
{
    delete ui;

    for (Etape *e : vectEtapes) {
        delete e;
    }
}

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

    if (vectComboIntro.size() > 0) {
        for (int i = 0; i < vectComboIntro[0]->count(); i++) {
            cb->addItem(vectComboIntro[0]->itemText(i));
        }
    }

    vectComboIntro.push_back(cb);
    vectTextIntro.push_back(te);

    int line = introLayout->rowCount();

    introLayout->addLayout(gl, line, 0);
    gl2->addWidget(l2, 0, 0);
    gl2->addWidget(te, 0, 1);

    introLayout->addLayout(gl2, line + 1, 0);
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

    Zstream << "<img src=\"" << ui->label_7->getPath()
            << "\" alt=\"image d'illustration\" width=\"10%\" />";
    Zstream << "<h2>Ville : " << Zcity << "</h2>";
    Zstream << "<h2>Département : " << Zdept << "</h2>";
    Zstream << "<h2>Difficulté : ";

    for (int i = 0; i < Zdifficulty; i++) {
        Zstream << "*";
    }

    Zstream << "</h2>";

    Zstream << "<h2>Durée : " << Ztime << "h</h2>";
    Zstream << "<h2>Longueur : " << Zlength << "km</h2>";

    Zstream << "<h1> Intro </h1>";

    // intro

    for (int i = 0; i < vectTextIntro.size(); i++) {
        Zstream << "<h2>" + vectComboIntro[i]->currentText() + "</h2>";
        Zstream << "<p>" + vectTextIntro[i]->toPlainText() + "</p>";
    }

    // about

    Zstream << "<h1>Contact</h1>";

    Zstream << "<h2>Organisation : " + ui->lineEdit_orga->displayText() + "</h2>";
    Zstream << "<h2>Adresse : " + ui->lineEdit_adresse->displayText() + "</h2>";
    Zstream << "<h2>Code postal & Ville : " + ui->lineEdit_ville->displayText() + "</h2>";
    Zstream << "<h2>Num. téléphone : " + ui->lineEdit_tel->displayText() + "</h2>";
    Zstream << "<h2>Adresse e-mail : " + ui->lineEdit_mail->displayText() + "</h2>";
    Zstream << "<h2>Site web : <a href=\"" + ui->lineEdit_web->displayText() + "\">"
                   + ui->lineEdit_web->displayText() + "</a> </h2>";

    Zstream << "\n</body> </html>\n\n";
    Zfile.close();
}

void MainWindow::addPerso(QString t)
{
    for (auto elem : vectComboIntro) {
        bool in = false;
        for (int i = 0; i < elem->count(); i++) {
            if (elem->itemText(i) == t) {
                in = true;
            }
        }
        if (!in) {
            elem->addItem(t);
        }
    }

    for (Etape* etape : vectEtapes){
        for(QComboBox* elem: etape->vectcombo){
            bool in=false;
            for (int i = 0; i < elem->count(); i++) {
                if (elem->itemText(i) == t) {
                    in = true;
                }
            }
            if (!in) {
                elem->addItem(t);
            }


        }
    }
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
    json["zillu"] = ui->label_7->getPath();

    QJsonArray tmp;

    for (auto elem : vectComboIntro) {
        tmp.append(elem->currentText());
    }

    json["zcomi"] = tmp;

    tmp = QJsonArray();
    for (auto elem : vectTextIntro) {
        tmp.append(elem->toPlainText());
    }

    json["ztexi"] = tmp;

    return json;
}

void MainWindow::fromJson(const QJsonObject &json)
{
    for (auto elem : introLayout->children()) {
        delete elem;
    }

    for (auto elem : vectComboIntro) {
        delete elem;
    }
    vectComboIntro = std::vector<QComboBox *>();

    for (auto elem : vectTextIntro) {
        delete elem;
    }
    vectTextIntro = std::vector<QTextEdit *>();

    if (const QJsonValue v = json["ztitl"]; v.isString())
        ui->lineEdit->setText(v.toString());
    if (const QJsonValue v = json["zcity"]; v.isString())
        ui->lineEdit_2->setText(v.toString());
    if (const QJsonValue v = json["zdept"]; v.isString())
        ui->lineEdit_3->setText(v.toString());
    if (const QJsonValue v = json["ztime"]; v.isString())
        ui->lineEdit_4->setText(v.toString());
    if (const QJsonValue v = json["zdiff"]; v.isString())
        ui->spinBox->setValue(v.toString().toInt());
    if (const QJsonValue v = json["zleng"]; v.isString())
        ui->lineEdit_5->setText(v.toString());

    if (const QJsonValue v = json["zillu"]; v.isString()) {
        ui->label_7->setPath(v.toString());
        ui->label_7->open();
    }

    if (const QJsonValue v = json["zcomi"]; v.isArray()) {
        int i = 0;
        for (auto elem : v.toArray()) {
            on_btPlusIntro_clicked();
            addPerso(elem.toString());
            vectComboIntro[i]->setCurrentText(elem.toString());
            i++;
        }
    }

    if (const QJsonValue v = json["ztexi"]; v.isArray()) {
        int i = 0;
        for (auto elem : v.toArray()) {
            vectTextIntro[i]->setText(elem.toString());
            i++;
        }
    }
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

void MainWindow::on_actionPersonnage_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                         tr("Le Z a faim"),
                                         tr("Entrez zun nom de personnage"),
                                         QLineEdit::Normal,
                                         "Le Z demande une nouvelle victime",
                                         &ok);
    if (ok && !text.isEmpty()) {
        addPerso(text);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn
        = QMessageBox::critical(this,
                                tr("Le Z te salut"),
                                tr("Le Z te remercie pour tes services.\nmplc"),
                                QMessageBox::Ok | QMessageBox::Yes,
                                QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes || resBtn == QMessageBox::Ok) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_push_addDialogEtape()
{
    QObject *src = sender();
    QPushButton *s = static_cast<QPushButton *>(src);
    Etape *etape = mapbt[s];

    etape->addDialog();


    etape->build();

    vectEtapes.push_back(etape);

    if (vectComboIntro.size() > 0) {


        for(QComboBox* cb : etape->vectcombo ){
            for (int i = 0; i < vectComboIntro[0]->count(); i++) {
                bool v=true;
                for(int j=0;j<cb->count();j++){
                    if(cb->itemText(j)==vectComboIntro[0]->itemText(i)){
                        v=false;
                    }

                }
                if(v){
                    cb->addItem(vectComboIntro[0]->itemText(i));
                }
            }
        }




    }

    buildEtape();
}

void MainWindow::on_pushButtonAddEtape_clicked()
{
    QPushButton *bt = new QPushButton("Ajouter dialogue");

    Etape *e = new Etape(bt);

    mapbt.insert(bt, e);
    connect(bt, &QPushButton::clicked, this, &MainWindow::on_push_addDialogEtape);

    vectEtapes.push_back(e);

    buildEtape();

    /****************** OLD VERSION, ARCHIVE (DONT WORK & UNREADABLE) ******************/
    //  int blockCount = etapesLayout->rowCount() / 5;
    //  int baseRow = blockCount * 5;

    //  QLabel *le = new QLabel("Titre : ");
    //  QLineEdit *t = new QLineEdit();
    //  QGridLayout *titleLayout = new QGridLayout();
    //  titleLayout->addWidget(le, 0, 0);
    //  titleLayout->addWidget(t, 0, 1);

    //  QComboBox *comboNS = new QComboBox();
    //  QLineEdit *lncoordNS = new QLineEdit();
    //  QComboBox *comboEO = new QComboBox();
    //  QLineEdit *lncoordEO = new QLineEdit();
    //  QGridLayout *coordLayout = new QGridLayout();
    //  coordLayout->addWidget(comboNS, 0, 0);
    //  coordLayout->addWidget(lncoordNS, 0, 1);
    //  coordLayout->addWidget(comboEO, 0, 2);
    //  coordLayout->addWidget(lncoordEO, 0, 3);

    //  QLabel *letapedial = new QLabel("Icone (Qui parle ?)");
    //  QComboBox *cbetapedial = new QComboBox();
    //  QSpacerItem *spetapedial = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    //  QGridLayout *gletapedial = new QGridLayout();
    //  gletapedial->addWidget(letapedial, 0, 0);
    //  gletapedial->addWidget(cbetapedial, 0, 1);
    //  gletapedial->addItem(spetapedial, 0, 2);

    //  QLabel *letapedial2 = new QLabel("Dialogue :");
    //  QTextEdit* teetapedial = new QTextEdit();
    //  teetapedial->setMinimumHeight(100);
    //  QGridLayout *gletapedial2 = new QGridLayout();
    //  gletapedial2->addWidget(letapedial2, 0, 0);
    //  gletapedial2->addWidget(teetapedial, 0, 1);

    //  QPushButton *btAddDialog = new QPushButton("Ajouter un dialogue");
    //  QPushButton *btAddQuestion = new QPushButton("Ajouter une question");
    //  QHBoxLayout *btLayout = new QHBoxLayout();
    //  btLayout->addWidget(btAddDialog);
    //  btLayout->addWidget(btAddQuestion);
    //  connect(btAddDialog, &QPushButton::clicked, this, &MainWindow::on_push_addDialogEtape);

    //  etapesLayout->addLayout(titleLayout,    baseRow + 0, 0);
    //  etapesLayout->addLayout(coordLayout,    baseRow + 1, 0);
    //  etapesLayout->addLayout(gletapedial,    baseRow + 2, 0);
    //  etapesLayout->addLayout(gletapedial2,   baseRow + 3, 0);
    //  etapesLayout->addLayout(btLayout,       baseRow + 4, 0);

    //  if (etapesLayout->parentWidget()) {
    //      etapesLayout->parentWidget()->update();
    //      etapesLayout->parentWidget()->adjustSize();
    //  }
}

void MainWindow::buildEtape()
{
    for (int i = 0; i < etapesLayout->count(); i++) {
        etapesLayout->removeItem(etapesLayout->itemAt(i));
    }

    int i = 0;
    for (Etape *etape : vectEtapes) {
        etapesLayout->addLayout(etape->layout, i, 0);
        i++;
    }
}
