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

    void convert();
    char colorRuling(unsigned int, unsigned int, unsigned int);

private:
    Ui::MainWindow *ui;
    
    //variable
    QImage image;
    std::vector<std::vector<char> >colorEmplacement;
    bool imageLoad;
    
private slots :
    void quit();
    void openImage();
};

#endif // MAINWINDOW_H
