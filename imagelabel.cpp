#include "imagelabel.h"

imageLabel::imageLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent)
{}

imageLabel::~imageLabel() {}

void imageLabel::mousePressEvent(QMouseEvent *event)
{
    open();
}

void imageLabel::setPath(const QString &newPath)
{
    path = newPath;
}

QString imageLabel::getPath() const
{
    return path;
}

void imageLabel::open()
{
    QString fileName;
    if (path.length() > 0) {
        fileName = path;

    } else {
        fileName = QFileDialog::getOpenFileName(this,
                                                tr("Open File"), QDir::currentPath());
    }

    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::critical(
                this,
                tr("Sacré Z"),
                tr("Le Z a volé ce format de fichier. Merci d'entrer un fichier au format valide.")
                    .arg(fileName));
            if (path.length() > 0) {
                path = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), QDir::currentPath());
                open();
            }
            return;
        }
        QPixmap tmp = QPixmap::fromImage(image);
        this->setPixmap( tmp.scaled( this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation) );

        path = fileName;
    }
}
