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

    //on créer notre tableau dynamiquement
    colorEmplacement = new char* [numberPiece];
    for(unsigned int i(0) ; i < numberPiece ; i++)
        colorEmplacement[i] = new char[numberPiece];

    //on averti du nomber de découpage
    QMessageBox::information(this, "t", "Nombre de découpage : " + QString::number(numberPiece * numberPiece));

    int sizePx(((image.width() + image.height()) / 2) / numberPiece);
    for(unsigned int i(0) ; i < numberPiece ; i++) {
        for(unsigned int j(0) ; j < numberPiece ; j++) {
            //on parcours l'image
            int red(0), green(0), blue(0), counter(0);
            for(unsigned int x(i * sizePx) ; x < ((i + 1) * sizePx) - 1 ; x++) {
                for(unsigned int y(j * sizePx) ; y < ((j + 1) * sizePx) - 1 ; y++) {
                    red += qRed(image.pixel(x, y));
                    green += qGreen(image.pixel(x, y));
                    blue += qBlue(image.pixel(x, y));
                    counter++;
                }
            }
            red /= counter; green /= counter; blue /= counter;
            Px *px = new Px(i * sizePx, j * sizePx, sizePx, red, green, blue);
            scene->addItem(px);

        }
    }


    emitResult(numberPiece);
    view->setScene(scene);
    view->show();
}

char MainWindow::colorRuling(unsigned int red, unsigned int green, unsigned int blue) {
    //fonction qui détermine la couleur dominante
    if(red == green == blue == 255)
        return 'w';
    else if(red == green == blue == 0)
        return 'n';
    else if(red > green && red > blue)
        return 'r';
    else if(green > red && green > blue)
        return 'g';
    else if(blue > red && blue > green)
        return 'b';
}

void MainWindow::emitResult(unsigned int numberPiece) {
    int red(0), green(0), blue(0);
    for(unsigned int i(0) ; i < numberPiece ; i++) {
        for(unsigned int j(0) ; j < numberPiece ; j++) {
            if(colorEmplacement[i][j] == 'r')
                red++;
            if(colorEmplacement[i][j] == 'g')
                green++;
            if(colorEmplacement[i][j] == 'b')
                blue++;
        }
    }

    QMessageBox::information(this, "Résultats", "Rouge : " + QString::number(red) + "\nVert : " + QString::number(green) + "\nBleu" + QString::number(blue));

    /*scene->clear();
    int sizePx(image.width() / numberPiece);

    for(unsigned int i(0) ; i < numberPiece ; i++) {
        for(unsigned int j(0) ; j < numberPiece ; j++) {
            //create pixel
            Px *pix = new Px(i * sizePx, j * sizePx, sizePx, colorEmplacement[i][j]);
            scene->addItem(pix);
        }
    }
    view->setScene(scene);
    view->show();*/
}
