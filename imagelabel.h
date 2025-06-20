#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QWidget>
#include <Qt>

class imageLabel : public QLabel
{
    Q_OBJECT

public:
    explicit imageLabel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~imageLabel();
    void open();

protected:
    void mousePressEvent(QMouseEvent *event);
    QString path;
};

#endif // IMAGELABEL_H
