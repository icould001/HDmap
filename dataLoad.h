//
// Created by Aykut Ismailov on 6.5.2020 г..
//

#ifndef HDMAP_DATALOAD_H
#define HDMAP_DATALOAD_H

#include <map>
#include <vector>
#include <iostream>
#include "object.h"
#include "route.h"
#include "dijkstra.h"


void printTest(std::map<object, std::vector<std::pair<object, route> > >& map)
{
    for(auto& i : map)
    {
        std::cout << i.first << ":\n";
        for(auto& j : i.second)
        {
            std::cout << "\t" << j.second << std::endl;
        }
    }
}

void putInMap(const std::vector<std::pair<object, route>>& vector, const object& obj)
{
    wholeMap.insert(std::pair<object, std::vector<std::pair<object, route> > >
                            (obj, std::vector<std::pair<object, route> >(vector)));
    highwayOnlyMap.insert(std::pair<object, std::vector<std::pair<object, route> > >
                                  (obj, std::vector<std::pair<object, route> >(vector)));
    noTolSystemMap.insert(std::pair<object, std::vector<std::pair<object, route> > >
                                  (obj, std::vector<std::pair<object, route> >(vector)));

}

void addRoute(const object& o1, const object& o2, route_type route_type, double duration)
{
    wholeMap.at(o1).push_back(std::pair<object, route>(o2,
                                                       route(o1.getX(),
                                                             o1.getY(),
                                                             o1.getObjectType(),
                                                             o2.getX(),
                                                             o2.getY(),
                                                             o2.getObjectType(),
                                                             route_type,
                                                             duration)));
    if(route_type == route_type::Highway)
    {
        highwayOnlyMap.at(o1).push_back(std::pair<object, route>(o2,
                                                                 route(o1.getX(),
                                                                       o1.getY(),
                                                                       o1.getObjectType(),
                                                                       o2.getX(),
                                                                       o2.getY(),
                                                                       o2.getObjectType(),
                                                                       route_type,
                                                                       duration)));
    }
    if(o1.getObjectType() != object_type::Tol_system && o2.getObjectType() != object_type::Tol_system)
    {
        noTolSystemMap.at(o1).push_back(std::pair<object, route>(o2,
                                                                 route(o1.getX(),
                                                                       o1.getY(),
                                                                       o1.getObjectType(),
                                                                       o2.getX(),
                                                                       o2.getY(),
                                                                       o2.getObjectType(),
                                                                       route_type,
                                                                       duration)));
    }
}

void load_data()
{
    std::vector<std::pair<object, route> > empty_vector;
    object o1(1, 2, object_type::Sign);
    object o2(2, 2, object_type::Crossroad);
    object o3(3, 2, object_type::Sign);
    object o4(3, 3, object_type::Tol_system);
    object o5(3, 4, object_type::Sign);
    object o6(2, 4, object_type::Crossroad);
    object o7(2, 3, object_type::Tol_system);
    object o8(1, 5, object_type::Sign);
    object o9(3, 5, object_type::Sign);

    putInMap(empty_vector, o1);
    putInMap(empty_vector, o2);
    putInMap(empty_vector, o3);
    putInMap(empty_vector, o4);
    putInMap(empty_vector, o5);
    putInMap(empty_vector, o6);
    putInMap(empty_vector, o7);
    putInMap(empty_vector, o8);
    putInMap(empty_vector, o9);

    addRoute(o1, o2, route_type::Highway, 10);
    addRoute(o1, o8, route_type::Inter_city, 30);
    addRoute(o2, o1, route_type::Highway, 10);
    addRoute(o2, o3, route_type::Highway, 10);
    addRoute(o2, o7, route_type::Highway, 10);
    addRoute(o3, o2, route_type::Highway, 10);
    addRoute(o3, o4, route_type::Highway, 10);
    addRoute(o4, o3, route_type::Highway, 10);
    addRoute(o4, o5, route_type::Highway, 10);
    addRoute(o5, o4, route_type::Highway, 10);
    addRoute(o5, o6, route_type::Highway, 10);
    addRoute(o5, o9, route_type::Off_read, 10);
    addRoute(o6, o5, route_type::Highway, 10);
    addRoute(o6, o7, route_type::Highway, 15);
    addRoute(o7, o2, route_type::Highway, 10);
    addRoute(o7, o6, route_type::Highway, 15);
    addRoute(o8, o1, route_type::Inter_city, 30);
    addRoute(o8, o9, route_type::Inter_city, 20);
    addRoute(o9, o5, route_type::Off_read, 10);
    addRoute(o9, o8, route_type::Inter_city, 20);
}



#endif //HDMAP_DATALOAD_H
