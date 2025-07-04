#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QScrollArea>
#include <QSizePolicy>
#include "etape.h"
#include <qcombobox.h>
#include <qgridlayout.h>
#include <qtextedit.h>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<QComboBox *> vectComboIntro;
    std::vector<QTextEdit *> vectTextIntro;
    std::vector<Etape *> vectEtapes;
    QGridLayout *introLayout;
    QGridLayout *etapesLayout;
    QString ZimageToHtml();
    QJsonObject toJson() const;
    QMap<QPushButton *, Etape *> mapbt;

    void buildEtape();

    void fromJson(const QJsonObject &json);
    void loadSave();
    void addPerso(QString t);

private slots:

    void on_btPlusIntro_clicked();

    void on_actionExporter_triggered();

    void on_actionExporter_en_html_triggered();

    void on_actionImporter_triggered();

    void on_pushButtonAddEtape_clicked();

    void on_actionPersonnage_triggered();

    void on_pushButton_2_clicked();

public slots:
    void on_push_addDialogEtape();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
