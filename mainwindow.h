#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    std::vector<QComboBox*> vectComboIntro;
    std::vector<QTextEdit*> vectTextIntro;
    std::vector<QTextEdit*> vectTextEtapes;
    std::vector<QComboBox*> vectComboEtapes;
    QGridLayout* introLayout;
    QGridLayout* etapesLayout;
    QString ZimageToHtml();

private slots:

    void on_btPlusIntro_clicked();

    void on_actionExporter_triggered();

    void on_actionExporter_en_html_triggered();

private:
    Ui::MainWindow *ui;
    QString Zimage;
};
#endif // MAINWINDOW_H
