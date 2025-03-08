#ifndef HEART_H
#define HEART_H
#include "shape.h"

class Heart : public Shape
{
public:
    using Shape::Shape;

    double countArea() override;
    double countPerimetr() override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

#endif // HEART_H
