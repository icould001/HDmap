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
    if(wholeMap.find(obj) == wholeMap.end())
    {
        wholeMap.insert(std::pair<object, std::vector<std::pair<object, route> > >
                                (obj, std::vector<std::pair<object, route> >(vector)));
    }
    if(highwayOnlyMap.find(obj) == highwayOnlyMap.end())
    {
        highwayOnlyMap.insert(std::pair<object, std::vector<std::pair<object, route> > >
                                      (obj, std::vector<std::pair<object, route> >(vector)));
    }
    if(noTolSystemMap.find(obj) == noTolSystemMap.end())
    {
        noTolSystemMap.insert(std::pair<object, std::vector<std::pair<object, route> > >
                                      (obj, std::vector<std::pair<object, route> >(vector)));
    }
}

void addRoute(const object& o1, const object& o2, route_type road_type, double duration)
{
    if(wholeMap.find(o1) == wholeMap.end())
    {
        putInMap(std::vector<std::pair<object, route> >(), o1);
    }
    wholeMap.at(o1).push_back(std::pair<object, route>(o2,
                                                       route(o1.getX(),
                                                             o1.getY(),
                                                             o1.getObjectType(),
                                                             o2.getX(),
                                                             o2.getY(),
                                                             o2.getObjectType(),
                                                             road_type,
                                                             duration)));
    if(road_type == route_type::Highway)
    {
        if(highwayOnlyMap.find(o1) == highwayOnlyMap.end())
        {
            putInMap(std::vector<std::pair<object, route> >(), o1);
        }
        highwayOnlyMap.at(o1).push_back(std::pair<object, route>(o2,
                                                                 route(o1.getX(),
                                                                       o1.getY(),
                                                                       o1.getObjectType(),
                                                                       o2.getX(),
                                                                       o2.getY(),
                                                                       o2.getObjectType(),
                                                                       road_type,
                                                                       duration)));
    }
    if(o1.getObjectType() != object_type::Tol_system && o2.getObjectType() != object_type::Tol_system)
    {
        if(noTolSystemMap.find(o1) == noTolSystemMap.end())
        {
            putInMap(std::vector<std::pair<object, route> >(), o1);
        }
        noTolSystemMap.at(o1).push_back(std::pair<object, route>(o2,
                                                                 route(o1.getX(),
                                                                       o1.getY(),
                                                                       o1.getObjectType(),
                                                                       o2.getX(),
                                                                       o2.getY(),
                                                                       o2.getObjectType(),
                                                                       road_type,
                                                                       duration)));
    }

}

void load_data()
{
    std::vector<std::pair<object, route> > empty_vector;
    object o1_2(1, 2, object_type::Sign);
    object o2_2(2, 2, object_type::Crossroad);
    object o3_2(3, 2, object_type::Sign);
    object o3_3(3, 3, object_type::Tol_system);
    object o3_4(3, 4, object_type::Sign);
    object o2_4(2, 4, object_type::Crossroad);
    object o2_3(2, 3, object_type::Tol_system);
    object o1_5(1, 5, object_type::Sign);
    object o3_5(3, 5, object_type::Sign);
    object o4_2(4,2,object_type::Crossroad);
    object o5_2(5,2,object_type::Sign);
    object o4_3(4,3,object_type::Tol_system);
    object o5_3(5,3,object_type::Tol_system);
    object o4_4(4,4,object_type::Crossroad);
    object o5_4(5,4,object_type::Sign);
    object o4_5(4,5,object_type::Crossroad);
    object o5_5(5,5,object_type::Sign);
    object o4_6(4,6,object_type::Tol_system);
    object o5_6(5,6,object_type::Tol_system);
    object o4_7(4,7,object_type::Crossroad);
    object o5_7(5,7,object_type::Sign);
    object o1_6(1,6,object_type::Tol_system);
    object o1_7(1,7,object_type::Crossroad);
    object o2_6(2,6,object_type::Tol_system);
    object o2_7(2,7,object_type::Crossroad);
    object o3_6(3,6,object_type::Tol_system);
    object o3_7(3,7,object_type::Sign);

    putInMap(empty_vector, o1_2);
    putInMap(empty_vector, o2_2);
    putInMap(empty_vector, o3_2);
    putInMap(empty_vector, o3_3);
    putInMap(empty_vector, o3_4);
    putInMap(empty_vector, o2_4);
    putInMap(empty_vector, o2_3);
    putInMap(empty_vector, o1_5);
    putInMap(empty_vector, o3_5);
    putInMap(empty_vector, o4_2);
    putInMap(empty_vector, o5_2);
    putInMap(empty_vector, o4_3);
    putInMap(empty_vector, o5_3);
    putInMap(empty_vector, o4_4);
    putInMap(empty_vector, o5_4);
    putInMap(empty_vector, o4_5);
    putInMap(empty_vector, o5_5);
    putInMap(empty_vector, o4_6);
    putInMap(empty_vector, o5_6);
    putInMap(empty_vector, o4_7);
    putInMap(empty_vector, o5_7);
    putInMap(empty_vector, o1_6);
    putInMap(empty_vector, o1_7);
    putInMap(empty_vector, o2_6);
    putInMap(empty_vector, o2_7);
    putInMap(empty_vector, o3_6);
    putInMap(empty_vector, o3_7);

    addRoute(o1_2, o2_2, route_type::Highway, 10);
    addRoute(o1_2, o1_5, route_type::Inter_city, 30);
    addRoute(o2_2, o1_2, route_type::Highway, 10);
    addRoute(o2_2, o3_2, route_type::Highway, 10);
    addRoute(o2_2, o2_3, route_type::Highway, 10);
    addRoute(o3_2, o2_2, route_type::Highway, 10);
    addRoute(o3_2, o3_3, route_type::Highway, 10);
    addRoute(o3_3, o3_2, route_type::Highway, 10);
    addRoute(o3_3, o3_4, route_type::Highway, 10);
    addRoute(o3_4, o3_3, route_type::Highway, 10);
    addRoute(o3_4, o2_4, route_type::Highway, 10);
    addRoute(o3_4, o3_5, route_type::Off_read, 10);
    addRoute(o2_4, o3_4, route_type::Highway, 10);
    addRoute(o2_4, o2_3, route_type::Highway, 15);
    addRoute(o2_3, o2_2, route_type::Highway, 10);
    addRoute(o2_3, o2_4, route_type::Highway, 15);
    addRoute(o1_5, o1_2, route_type::Inter_city, 30);
    addRoute(o1_5, o3_5, route_type::Inter_city, 20);
    addRoute(o3_5, o3_4, route_type::Off_read, 10);
    addRoute(o3_5, o1_5, route_type::Inter_city, 20);
    addRoute(o3_2, o4_2, route_type::Inter_city, 20);
    addRoute(o4_2,o3_2,route_type::Inter_city,20);
    addRoute(o4_2, o5_2, route_type::Highway, 20);
    addRoute(o4_2,o4_3,route_type::Highway,5);
    addRoute(o5_2,o4_2,route_type::Highway,20);
    addRoute(o5_2,o5_3,route_type::Highway,25);
    addRoute(o4_3,o4_2,route_type::Highway,5);
    addRoute(o4_3,o5_3,route_type::Off_read,20);
    addRoute(o4_3,o4_4,route_type::Highway,15);
    addRoute(o5_3,o4_3,route_type::Off_read,20);
    addRoute(o5_3,o5_2,route_type::Highway,25);
    addRoute(o5_3,o5_4,route_type::Highway,10);
    addRoute(o3_4,o4_4,route_type::Highway,5);
    addRoute(o4_4,o3_4,route_type::Highway,5);
    addRoute(o4_4,o4_3,route_type::Highway,15);
    addRoute(o4_4,o5_4,route_type::Highway,10);
    addRoute(o4_4,o4_5,route_type::Highway,15);
    addRoute(o5_4,o5_3,route_type::Highway,10);
    addRoute(o5_4,o4_4,route_type::Highway,10);
    addRoute(o5_4,o5_5,route_type::Off_read,10);
    addRoute(o4_5,o4_4,route_type::Highway,15);
    addRoute(o4_5,o4_6,route_type::Highway,10);
    addRoute(o4_5,o5_5,route_type::Highway,10);
    addRoute(o5_5,o4_5,route_type::Highway,10);
    addRoute(o5_5,o5_4,route_type::Off_read,10);
    addRoute(o5_5,o5_6,route_type::Highway,10);
    addRoute(o4_6,o4_5,route_type::Highway,10);
    addRoute(o4_6,o4_7,route_type::Highway,15);
    addRoute(o5_6,o5_5,route_type::Highway,10);
    addRoute(o5_6,o5_7,route_type::Highway,10);
    addRoute(o4_7,o4_6,route_type::Highway,15);
    addRoute(o4_7,o5_7,route_type::Highway,10);
    addRoute(o4_7,o3_7,route_type::Off_read,15);
    addRoute(o5_7,o5_6,route_type::Highway,10);
    addRoute(o5_7,o4_7,route_type::Highway,10);
    addRoute(o3_5,o3_6,route_type::Off_read,10);
    addRoute(o3_6,o3_5,route_type::Off_read,10);
    addRoute(o3_6,o2_6,route_type::Inter_city,5);
    addRoute(o3_6,o3_7,route_type::Highway,10);
    addRoute(o3_7,o3_6,route_type::Highway,10);
    addRoute(o3_7,o4_7,route_type::Off_read,15);
    addRoute(o3_7,o2_7,route_type::Highway,10);
    addRoute(o2_6,o3_6,route_type::Inter_city,5);
    addRoute(o2_6,o2_7,route_type::Highway,15);
    addRoute(o2_6,o1_6,route_type::Inter_city,10);
    addRoute(o2_7,o2_6,route_type::Highway,15);
    addRoute(o2_7,o3_7,route_type::Highway,10);
    addRoute(o2_7,o1_7,route_type::Inter_city,20);
    addRoute(o1_5,o1_6,route_type::Off_read,10);
    addRoute(o1_6,o1_5,route_type::Off_read,10);
    addRoute(o1_6,o2_6,route_type::Inter_city,10);
    addRoute(o1_6,o1_7,route_type::Highway,15);
    addRoute(o1_7,o1_6,route_type::Highway,15);
    addRoute(o1_7,o2_7,route_type::Inter_city,20);
}


#endif //HDMAP_DATALOAD_H
