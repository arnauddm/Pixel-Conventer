#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "px.hpp"

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

    //init scene & view
    scene = new QGraphicsScene();
    view = new QGraphicsView();
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
    imageLoad = true;
}

void MainWindow::convert() {
    if(!imageLoad) {
        QMessageBox::warning(this, "Error", "Error ! No image !");
        return; //si aucune image n'est sélectionnée on quitte
    }

    scene->clear();

    unsigned int lastX(0), lastY(0), numberPiece(ui->numberPiece->value());

    int wPx(image.width() / numberPiece);
    int hPx(image.height() / numberPiece);
    for(unsigned int i(0) ; i < numberPiece ; i++) {
        for(unsigned int j(0) ; j < numberPiece ; j++) {
            //on parcours l'image
            int red(0), green(0), blue(0), counter(0);
            for(unsigned int x(i * wPx) ; x < ((i + 1) * wPx) - 1 ; x++) {
                for(unsigned int y(j * hPx) ; y < ((j + 1) * hPx) - 1 ; y++) {
                    red += qRed(image.pixel(x, y));
                    green += qGreen(image.pixel(x, y));
                    blue += qBlue(image.pixel(x, y));
                    counter++;
                }
            }
            red /= counter; green /= counter; blue /= counter;
            Px *px = new Px(i * wPx, j * hPx, (hPx + wPx) / 2, red, green, blue);
            scene->addItem(px);

        }
    }
    view->setScene(scene);
    view->show();
}
