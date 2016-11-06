#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QMessageBox>
#include <QFileDialog>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    
    //variable
    QImage image;
    char **colorEmplacement; //on créer un pointeur de pointeur qui nous permettra d'avoir un tableau à deux dim
    bool imageLoad;

    QGraphicsScene *scene;
    QGraphicsView *view;
    
private slots :
    void quit();
    void openImage();
    void convert();
};

#endif // MAINWINDOW_H
