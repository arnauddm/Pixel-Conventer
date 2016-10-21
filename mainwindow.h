#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QMessageBox>
#include <QFileDialog>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    char colorRuling(unsigned int, unsigned int, unsigned int);
    void emitResult(unsigned int);

private:
    Ui::MainWindow *ui;
    
    //variable
    QImage image;
    char **colorEmplacement;
    bool imageLoad;
    
private slots :
    void quit();
    void openImage();
    void convert();
};

#endif // MAINWINDOW_H
