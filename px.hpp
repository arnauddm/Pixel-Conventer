#ifndef PX_HPP
#define PX_HPP

#include <QGraphicsEllipseItem>
#include <QBrush>

class Px : public QGraphicsEllipseItem
{
public:
    Px(int x, int y, int size, char color);
    ~Px();

signals:

public slots:
};

#endif // PX_HPP
