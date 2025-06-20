#include <QFileDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QLabel"
#include "QLayoutItem"
#include <QSizePolicy>
#include <QScrollArea>
#include<QMessageBox>
#include <QJsonArray>

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
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open File"), QDir::currentPath());
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

    for (auto elem: vectComboIntro) {
        tmp.append(elem->currentText());
    }

    json["zcome"] = tmp;

    tmp = QJsonArray();
    for (auto elem: vectComboIntro) {
        tmp.append(elem->currentText());
    }

    json["zcomi"] = tmp;

    tmp = QJsonArray();
    for (auto elem: vectTextEtapes) {
        tmp.append(elem->toPlainText() );
    }

    json["ztexe"] = tmp;

    tmp = QJsonArray();
    for (auto elem: vectTextIntro) {
        tmp.append(elem->toPlainText() );
    }

    json["ztexi"] = tmp;

    return json;
}

void MainWindow::fromJson(const QJsonObject &json)
{
    for (auto elem: introLayout->children()) {
        delete elem;
    }

    for (auto elem: vectComboIntro) {
        delete elem;
    }
    vectComboIntro = std::vector<QComboBox*>();

    for (auto elem: vectTextIntro) {
        delete elem;
    }
    vectTextIntro = std::vector<QTextEdit*>();

    for (auto elem: vectTextEtapes) {
        delete elem;
    }
    vectTextEtapes = std::vector<QTextEdit*>();

    for (auto elem: vectComboEtapes) {
        delete elem;
    }
    vectComboEtapes = std::vector<QComboBox*>();

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

    if (const QJsonValue v = json["zillu"]; v.isString()){
        ui->label_7->setPath(v.toString());
        ui->label_7->open();
    }

    if (const QJsonValue v = json["zcome"]; v.isArray()){
        //for (auto elem: v.toArray()) {
        //    on_btPlusIntro_clicked();
        //}
    }

    if (const QJsonValue v = json["ztexe"]; v.isArray()){
        //for (auto elem: v.toArray()) {
        //    on_btPlusIntro_clicked();
        //}
    }

    if (const QJsonValue v = json["zcomi"]; v.isArray()){
        int i = 0;
        for (auto elem: v.toArray()) {
            on_btPlusIntro_clicked();
            vectComboIntro[i]->addItem(elem.toString());
            i++;
        }
    }

    if (const QJsonValue v = json["ztexi"]; v.isArray()){
        int i = 0;
        for (auto elem: v.toArray()) {
            vectTextIntro[i]->setText(elem.toString());
            i++;
        }
    }
}

void MainWindow::loadSave()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), QDir::currentPath());
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
