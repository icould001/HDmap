//
// Created by Aykut Ismailov on 29.4.2020 г..
//

#ifndef HDMAP_OBJECT_H
#define HDMAP_OBJECT_H


#include <ostream>
#include "object_type.h"

class object
{
    int x;
    int y;
    object_type type;
public:
    object(int x, int y, enum object_type object_type) : x(x), y(y), type(object_type)
    {
    }

    object() : x(0), y(0), type(object_type::Invalid)
    {
    }

    int getX() const;

    int getY() const;

    enum object_type getObjectType() const;

    friend double distance(object start, object end);

    friend std::ostream& operator<<(std::ostream& out, object object);

    friend inline bool operator<(const object& lhs, const object& rhs)
    {
        return (lhs.getX() == rhs.getX()) ? lhs.getY() < rhs.getY() : lhs.getX() < rhs.getX();
    }

    friend inline bool operator>(const object& lhs, const object& rhs)
    {
        return rhs < lhs;
    }

    friend inline bool operator<=(const object& lhs, const object& rhs)
    {
        return !(lhs > rhs);
    }

    friend inline bool operator>=(const object& lhs, const object& rhs)
    {
        return !(lhs < rhs);
    }

    friend inline bool operator==(const object& lhs, const object& rhs)
    {
        return (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY());
    }

    friend inline bool operator!=(const object& lhs, const object& rhs)
    {
        return !(rhs == lhs);
    }

    inline object& operator=(const object& rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->type = rhs.type;
        return *this;
    }
};


#endif //HDMAP_OBJECT_H
