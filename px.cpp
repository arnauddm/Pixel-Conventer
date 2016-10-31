#include "px.hpp"

Px::Px(int x, int y, int size, int red, int green, int blue) {
    //get color of pixel & create brush
    /*QBrush brush;
    switch (color) {
    case 'w':
        brush = Qt::white;
        break;
    case 'n':
        brush = Qt::black;
        break;
    case 'r':
        brush = Qt::red;
        break;
    case 'g':
        brush = Qt::green;
        break;
    case 'b':
        brush = Qt::blue;
    default:
        brush = Qt::white;
        break;
    }*/

    this->setRect(x, y, size, size);
    this->setBrush(QColor(red, green, blue));
}
