#include "rectangle.h"

//Rectangle::Rectangle() {}

double Rectangle::countArea()
{
    return width*height;
}

double Rectangle::countPerimetr()
{
    return 2*(width+height);
}
