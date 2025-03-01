#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <shape.h>

class Rectangle : public Shape
{
public:
    //Rectangle();
    using Shape::Shape;

    double countArea() override;
    double countPerimetr() override;

};

#endif // RECTANGLE_H
