#include "imagelabel.h"

imageLabel::imageLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent)
{}

imageLabel::~imageLabel() {}

void imageLabel::mousePressEvent(QMouseEvent *event)
{
    open();
}

void imageLabel::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        path = fileName;
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(
                this,
                tr("Image Viewer"),
                tr("Le Z a volé ce format de fichier. Merci d'entrer un fichier au format valide.")
                    .arg(fileName));
            return;
        }
        QPixmap tmp = QPixmap::fromImage(image);

        this->setPixmap(tmp.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
