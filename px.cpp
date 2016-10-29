#include "px.hpp"

Px::Px(int x, int y, int size, char color) {
    //get color of pixel & create brush
    QBrush brush;
    switch (color) {
    case 'r':
        brush = Qt::red;
        break;
    case 'g':
        brush = Qt::green;
        break;
    case 'b':
        brush = Qt::blue;
        break;
    default:
        brush = Qt::white;
        break;
    }

    this->setRect(x, y, size, size);
    this->setBrush(brush);
}

Px::~Px()
{
    delete this;
}
