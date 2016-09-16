#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //print on imageViewer
    ui->imageViewer->setText("Aucune image sélectionnée...");
    ui->progress->setValue(0);

    //init
    imageLoad = false;
    
    //connect signal to slot
    connect(ui->close, SIGNAL(clicked(bool)), this, SLOT(quit()));
    connect(ui->open, SIGNAL(clicked(bool)), this, SLOT(openImage()));
    connect(ui->convert, SIGNAL(clicked(bool)), this, SLOT(convert()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quit() {
    if(QMessageBox::Yes == QMessageBox::warning(this, "Quitter", "Voulez - vous vraiment quitter ?", QMessageBox::Yes, QMessageBox::No)) {
        this->close();
    }
}

void MainWindow::openImage() {
    QString imageLink(QFileDialog::getOpenFileName(this, "Ouvrir", QDir::currentPath(), "Images (*.jpg *.jpeg *.png"));
    if(imageLink.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucune image n'a été sélectionnée...");
        return;
    }
    image.load(imageLink);
    image = image.scaled(ui->imageViewer->size(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
    ui->imageViewer->setPixmap(image);
}

void MainWindow::cut() {
    int height(image.height()), width(image.width()), lastX(0), lastY(0);

    for(int i(0) ; i < piece ; i++) {
        for(int j(0) ; j < piece ; j++) {
            cutImage[i][j] = image.copy(lastX, lastY, i * (width / piece), j * (height / piece));
            lastX += width / piece;
            lastY += height / piece;
        }
    }
}

void MainWindow::convert() {
    piece = ui->numberPiece->value();
    cut();
    int pieceCounter(0);
    QImage frag;
    int red(0), green(0), blue(0);

    for(int i(0) ; i != piece ; i++) {
        for(int j(0) ; j != piece ; j++) {
            frag = cutImage[i][j].toImage();
            int colorRed(0), colorGreen(0), colorBlue(0), counter(0);
            for(int x(0) ; x != frag.width() ; x++) {
                for(int y(0) ; y != frag.height() ; y++) {
                    QRgb pix(frag.pixel(x, y));
                    colorRed += qRed(pix);
                    colorGreen += qGreen(pix);
                    colorBlue += qBlue(pix);
                    counter++;
                }
            }
            //compteur++;
            colorRed /= counter;
            colorGreen /= counter;
            colorBlue /= counter;

            if(colorRed > colorGreen && colorRed > colorBlue) {
                colorEmplacement[i][j] = 'r';
                red++;
            }

            if(colorGreen > colorRed && colorGreen > colorBlue) {
                colorEmplacement[i][j] = 'g';
                green++;
            }

            if(colorBlue > colorRed && colorBlue > colorGreen) {
                colorEmplacement[i][j] = 'b';
                blue++;
            }

            pieceCounter++;
            ui->progress->setValue((pieceCounter / (piece * piece)) * 100);
        }
    }
    QMessageBox::information(this, "Nombre de découpe", QString::number(pieceCounter) + " carré ont été découpés !", QMessageBox::Ok);
    QMessageBox::information(this, "Résultats", "Résultats des couleurs :\nRouge : " + QString::number(red) + "\nVert : " + QString::number(green) + "\nBleu : " + QString::number(blue));
}
