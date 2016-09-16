#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QMessageBox>
#include <QFileDialog>

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
    QPixmap image;
    QPixmap cutImage[100][100];
    char colorEmplacement[100][100];
    bool imageLoad;
    int piece;
    
private slots :
    //functions
    void quit();
    void openImage();
    //void allToOne();
    void cut();
    void convert();
};

#endif // MAINWINDOW_H
