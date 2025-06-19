#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    QGridLayout* introLayout;
    QString ZimageToHtml();

private slots:
    void on_pushButton_clicked();
    void on_btPlusIntro_clicked();

    void on_actionExporter_triggered();
    void on_actionImporter_triggered();
    void on_actionExporter_en_html_triggered();

private:
    Ui::MainWindow *ui;
    QString Zimage;
};
#endif // MAINWINDOW_H
