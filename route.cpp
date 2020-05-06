//
// Created by Aykut Ismailov on 29.4.2020 г..
//

#include "route.h"

object route::getStart() const
{
    return start;
}

object route::getEnd() const
{
    return end;
}

route_type route::getRoadType() const
{
    return road_type;
}

double route::getDuration() const
{
    return duration;
}

double route::getDistance() const
{
    return distance(start, end);
}

std::string route::getDurationString() const
{
    int hours = static_cast<int>(duration / 3600);
    int minutes = static_cast<int>((duration - hours * 3600) / 60);
    double seconds = duration - minutes * 60 - hours * 3600;

    return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
}

std::ostream& operator<<(std::ostream& out, route o)
{
    std::string str;
    switch(o.getRoadType())
    {
        case route_type::Highway:
            str = "Highway";
            break;
        case route_type::Inter_city:
            str = "Inter-city";
            break;
        case route_type::Off_read:
            str = "Off-road";
            break;
        default:
            str = "";
    }
    out << "This " << str << " starts from " << o.start << " and ends in " << o.end << ". The duration is " << o.getDurationString() << ".";
    return out;
}







