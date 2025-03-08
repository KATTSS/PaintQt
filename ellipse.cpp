#include "ellipse.h"


double Ellipse::countArea()
{
    return 3.14*(width/2)*(height/2);
}

double Ellipse::countPerimetr()
{
    return 3.14*(3*(width/2+height/2)-std::sqrt((3*width/2+height/2)*(3*height/2+width/2)));
}
