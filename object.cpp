//
// Created by Aykut Ismailov on 29.4.2020 г..
//

#include <cmath>
#include "object.h"

double distance(object start, object end)
{
    return sqrt(
            (start.x - end.x) * (start.x - end.x)
            +
            (start.y - end.y) * (start.y - end.y)
               );
}

int object::getX() const
{
    return x;
}

int object::getY() const
{
    return y;
}

enum object_type object::getObjectType() const {
    return object_type;
}

std::ostream& operator<<(std::ostream& out, object point)
{
    std::string str;
    switch(point.object_type)
    {
        case object_type::Sign:
            str="Sign";
            break;
        case object_type::Tol_system:
            str="Tol-system";
            break;
        case object_type::Crossroad:
            str="Crossroad";
            break;
        default:
            str="";
    }
    out <<str<< " at (" << point.x << "," << point.y << ")";
    return out;
}



