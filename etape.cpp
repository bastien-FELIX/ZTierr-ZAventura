#include "etape.h"
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <mainwindow.h>
#include <qcombobox.h>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qtextedit.h>

Etape::Etape(QPushButton *bt, QWidget *parent)
{
    bt->setParent(this);
    qDebug() << "a";
    titleLayout = new QGridLayout();
    QLabel *le = new QLabel("Titre : ");
    QLineEdit *t = new QLineEdit();
    QComboBox *comboNS = new QComboBox();
    QLineEdit *lncoordNS = new QLineEdit();
    QComboBox *comboEO = new QComboBox();
    QLineEdit *lncoordEO = new QLineEdit();

    comboNS->addItem("N");
    comboNS->addItem("S");

    comboEO->addItem("E");
    comboEO->addItem("O");

    QGridLayout *titleLayouttmp = new QGridLayout();
    QGridLayout *coordLayout = new QGridLayout();

    titleLayouttmp->addWidget(le, 0, 0);
    titleLayouttmp->addWidget(t, 0, 1);
    coordLayout->addWidget(comboNS, 0, 0);
    coordLayout->addWidget(lncoordNS, 0, 1);
    coordLayout->addWidget(comboEO, 0, 2);
    coordLayout->addWidget(lncoordEO, 0, 3);

    titleLayout->addLayout(titleLayouttmp, 0, 0);
    titleLayout->addLayout(coordLayout, 1, 0);

    layoutbt = new QGridLayout();
    layoutbt->addWidget(bt, 0, 0);

    layout = new QGridLayout();
    layout->addLayout(titleLayout, 0, 0);
    layout->addLayout(layoutbt, 1, 0);
}

void Etape::build()
{
    for (int i = 0; i < layout->count(); i++) {
        layout->removeItem(layout->itemAt(i));
    }

    layout->addLayout(titleLayout, 0, 0);
    int i = 1;
    for (QGridLayout *q : vectgrid) {
        layout->addLayout(q, i, 0);
        i++;
    }

    layout->addLayout(layoutbt, i, 0);
}

void Etape::addDialog()
{
    QLabel *l1 = new QLabel("Icone(Qui parle?)");
    QComboBox *cb = new QComboBox();
    QSpacerItem *sp = new QSpacerItem(0, 0, QSizePolicy::Expanding);

    QGridLayout *g1 = new QGridLayout();

    g1->addWidget(l1, 0, 0);
    g1->addWidget(cb, 0, 1);
    g1->addItem(sp, 0, 2);

    QLabel *l2 = new QLabel("Dialogue :");
    QTextEdit *te = new QTextEdit("Bounjour, c'est le Z");
    te->setMinimumHeight(100);

    QGridLayout *g2 = new QGridLayout();

    g2->addWidget(l2, 0, 0);
    g2->addWidget(te, 0, 1);

    QGridLayout *res = new QGridLayout;

    res->addLayout(g1, 0, 0);
    res->addLayout(g2, 1, 0);

    vectgrid.push_back(res);
}
