//
// Created by Aykut Ismailov on 6.5.2020 г..
//

#ifndef HDMAP_DIJKSTRA_H
#define HDMAP_DIJKSTRA_H

#include <map>
#include <limits>
#include <iostream>
#include <vector>
#include "object.h"
#include "route.h"

static std::map<object, std::vector<std::pair<object, route> > > wholeMap;
static std::map<object, std::vector<std::pair<object, route> > > highwayOnlyMap;
static std::map<object, std::vector<std::pair<object, route> > > noTolSystemMap;

object minDistance(std::map<object, double>& dist, std::map<object, bool>& sptSet)
{
    // Initialize min value
    double min = std::numeric_limits<double>::max();
    object min_index(0, 0, object_type::Invalid);

    for(auto& v : dist)
    {
        if(!sptSet[v.first] && v.second <= min)
        {
            min = v.second;
            min_index = v.first;
        }
    }

    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(std::map<object, double>& dist, std::map<object, object>& parent)
{
    printf("Vertex \t\t Distance from Source\n");
    for(auto& i : dist)
    {
        std::cout << i.first << "\t\t" << i.second << "\t\t" << parent[i.first] << std::endl;
    }
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation

std::pair<double, std::map<object, object>> dijkstra_min_duration(std::map<object, std::vector<std::pair<object, route> > > map,
                                                                  object start,
                                                                  object end)
{
    std::map<object, double> dist; // The output array. dist[i] will hold the shortest
// distance from start to i

    std::map<object, bool> sptSet; // sptSet[i] will be true if vertex i is included in shortest
// path tree or shortest distance from start to i is finalized

    std::map<object, object> parent;// the shortest path tracker


    // Initialize all distances as INFINITE and stpSet[] as false
    for(auto& i : map)
    {
        dist.insert({i.first, std::numeric_limits<double>::max()});
        sptSet.insert({i.first, false});
        parent.insert(std::pair<object, object>(i.first, start));
    }

// Distance of source vertex from itself is always 0
    dist[start] = 0;

// Find shortest path for all vertices
    for(auto count = map.rbegin()++; count != map.rend(); count++)
    {
// Pick the minimum distance vertex from the set of vertices not
// yet processed. u is always equal to start in the first iteration.
        object u = minDistance(dist, sptSet);

// Mark the picked vertex as processed
        sptSet[u] = true;

// Update dist value of the adjacent vertices of the picked vertex.
        for(auto v = map[u].begin(); v != map[u].end(); v++)
        {

// Update dist[v] only if is not in sptSet, there is an edge from
// u to v, and total weight of path from start to v through u is
// smaller than current value of dist[v]
            if(!sptSet[v->first] && (dist[u] != std::numeric_limits<double>::max())
               && dist[u] + v->second.getDuration() < dist[v->first])
            {
                dist[v->first] = dist[u] + v->second.getDuration();
                parent.at(v->first) = u;
            }
        }
    }

// print the constructed distance array
//printSolution(dist,parent);

    return {dist[end], parent};
}

std::pair<double, std::map<object, object>> dijkstra_min_crossroads(std::map<object, std::vector<std::pair<object, route> > > map,
                                                                    object start,
                                                                    object end)
{
    std::map<object, double> crossroads; // The output array. crossroads[i] will hold the min
    // crossroads from start to i

    std::map<object, bool> sptSet; // sptSet[i] will be true if vertex i is included in min
    //crossroad path from start to i is finalized

    std::map<object, object> parent;// the shortest path tracker


    // Initialize all crossroads as INFINITE and stpSet[] as false
    for(auto& i : map)
    {
        crossroads.insert({i.first, std::numeric_limits<double>::max()});
        sptSet.insert({i.first, false});
        parent.insert(std::pair<object, object>(i.first, start));
    }

    // Crossroads of source vertex from itself is always 0
    crossroads[start] = 0;

    // Find min crossroad path for all vertices
    for(auto count = map.rbegin()++; count != map.rend(); count++)
    {
        // Pick the non crossroad vertex(if has one) from the set of vertices not
        // yet processed. u is always equal to start in the first iteration.
        object u = minDistance(crossroads, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for(auto v = map[u].begin(); v != map[u].end(); v++)
        {
            double d = v->first.getObjectType() == object_type::Crossroad ? 1 : 0;
            // Update crossroads[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from start to v through u is
            // smaller than current value of crossroads[v]
            if(!sptSet[v->first] && (crossroads[u] != std::numeric_limits<double>::max())
               && crossroads[u] + d < crossroads[v->first])
            {
                crossroads[v->first] = d;
                parent.at(v->first) = u;
            }
        }
    }

    // print the constructed array with the vertex from which you come from
    //printSolution(dist,parent);

    return {crossroads[end], parent};
}

#endif //HDMAP_DIJKSTRA_H
