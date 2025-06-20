#ifndef ETAPE_H
#define ETAPE_H
#include <QMainWindow>
#include <qcombobox.h>
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <vector>

class Etape : public QWidget

{
    Q_OBJECT
public:
    Etape(QPushButton *bt, QWidget *parent = nullptr);
    QGridLayout *titleLayout;
    std::vector<QGridLayout *> vectgrid;
    QGridLayout *layout;
    QGridLayout *layoutbt;
    void build();
    void addDialog();
    std::vector<QComboBox*> vectcombo;
};

#endif // ETAPE_H
