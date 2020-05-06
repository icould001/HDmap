//
// Created by Aykut Ismailov on 29.4.2020 г..
//

#ifndef HDMAP_ROUTE_H
#define HDMAP_ROUTE_H


#include "object.h"
#include "route_type.h"


class route
{
    object start;
    object end;
    route_type road_type;
    double duration;
public:
    route():start(0,0,object_type::Invalid),end(0,0,object_type::Invalid),road_type(route_type::Invalid),duration(0){}

    route(int start_x,
          int start_y,
          object_type start_ot,
          int end_x,
          int end_y,
          object_type end_ot,
          route_type road_type,
          double duration) :
            start(start_x, start_y, start_ot),
            end(end_x, end_y, end_ot),
            road_type(road_type),
            duration(duration)
    {
    }

    object getStart() const;

    object getEnd() const;

    route_type getRoadType() const;

    double getDuration() const;

    std::string getDurationString() const;

    double getDistance() const;

    ~route() = default;

    friend std::ostream& operator<<(std::ostream&, route);
};


#endif //HDMAP_ROUTE_H
