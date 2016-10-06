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

void MainWindow::convert() {
    unsigned int piece(ui->numberPiece->value());
    calculPixel(piece);
    emissionResult(piece);
}

void MainWindow::calculPixel(unsigned int numberPiece) {
    int height(image.height()), width(image.width()), lastX(0), lastY(0), red(0), green(0), blue(0), pieceCounter(0);

    for(int i(0) ; i < numberPiece ; i++) {
        for(int j(0) ; j < numberPiece ; j++) {
            QImage frag;
            frag = image.copy(lastX, lastY, i * (width / numberPiece), j * (height / numberPiece)).toImage();
            lastX += width / numberPiece;
            lastY += height / numberPiece;

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
            ui->progress->setValue((pieceCounter / (numberPiece * numberPiece)) * 100);
        }
    }
}

void MainWindow::emissionResult(unsigned int numberPiece) {
    unsigned int red(0), green(0), blue(0);

    for(unsigned int i(0) ; i < numberPiece ; i++) {
        for(unsigned int j(0) ; j < numberPiece ; j++) {
            switch (colorEmplacement[i][j]) {
            case 'r':
                red++;
                break;

            case 'g':
                green++;
                break;

            case 'b':
                blue++;
                break;

            default:
                break;
            }
        }
    }
    QMessageBox::information(this, "Résultats", "Émission des résultats...\n\tRouge : " + QString::number(red) + "\n\tVert : " + QString::number(green) + "\n\tBleu : " + QString::number(blue), QMessageBox::Ok);
}
