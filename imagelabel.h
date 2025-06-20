#ifndef IMAGELABEL_H
#define IMAGELABEL_H


#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>

class imageLabel : public QLabel {
    Q_OBJECT

public:
    explicit imageLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~imageLabel();
    void open();

    QString getPath() const;

    void setPath(const QString &newPath);

protected:
    void mousePressEvent(QMouseEvent* event);
    QString path;

};

#endif // IMAGELABEL_H
