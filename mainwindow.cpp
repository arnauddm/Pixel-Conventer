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
    image = image.scaled(ui->imageViewer->size(), Qt::IgnoreAspectRatio, Qt::FastTransformation); //afficher l'image en occupant tout l'espace
    ui->imageViewer->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::convert() {
    unsigned int lastX(0), lastY(0);
    colorEmplacement.resize(ui->numberPiece->value());

    for(unsigned int i(0) ; i < colorEmplacement.size() ; i++) {
        for(unsigned int j(0) ; j < colorEmplacement.size() ; j++) {
            unsigned int red(0), green(0), blue(0), counter(0); //variable propre à chaque frag reconstitué

            for(unsigned int x(lastX) ; x < lastX + (image.width() / ui->numberPiece->value()) ; x++) { //pour x allant de l'ancien X jusqu'au X du prochain frag
                for(unsigned int y(lastY) ; y < lastY + (image.height()) ; y++) {
                    red += qRed(image.pixel(x, y));
                    green += qGreen(image.pixel(x, y));
                    blue += qBlue(image.pixel(x, y));
                    counter++;
                }
            }

            colorEmplacement[i][j] = colorRuling(red, green, blue);

        }
    }
}

char MainWindow::colorRuling(unsigned int red, unsigned int green, unsigned int blue) {
    if(red > green && red > blue)
        return 'r';
    if(green > blue)
        return 'g';
    return 'b';
}
