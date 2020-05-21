#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <sstream>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "route.h"
#include "dataLoad.h"
#include "dijkstra.h"

#define FILE_NAME "output.txt"

sem_t sem;

typedef struct args
{
    object& o1;
    object& o2;
    std::map<object, std::vector<std::pair<object, route>>>& map;
    std::string expl_str;
    int& out;
} args;

object findObject(int x, int y, std::map<object, std::vector<std::pair<object, route>>>& map);

void* doAlgorithmMinDuration(void* arg);

void* doAlgorithmMnCrossroads(void* arg);

void printPath(const args* a, const std::pair<double, std::map<object, object>>& path, std::string searched_thing);

int main()
{
    int fd = open(FILE_NAME,O_CREAT|O_WRONLY,0777);
    if(fd<0){
        perror("Error opening output file.");
        exit(1);
    }
    load_data();
    //printTest(highwayOnlyMap);
    int x1, x2, y1, y2;
    std::cout << "x1=";
    std::cin >> x1;
    std::cout << "y1=";
    std::cin >> y1;
    std::cout << "x2=";
    std::cin >> x2;
    std::cout << "y2=";
    std::cin >> y2;
    object o1 = findObject(x1, y1, wholeMap);
    object o2 = findObject(x2, y2, wholeMap);
    //std::cout<<o1<<std::endl;
    //std::cout<<o2<<std::endl;
    if(o1 == wholeMap.end()->first||o2 == wholeMap.end()->first){
        perror("Error: invalid coordinates.");
        exit(2);
    }

    if(sem_init(&sem, 0, 1)<0){
        perror("Error sem_init.");
        exit(3);
    }
    pthread_t wmT, ntT, mcT, hoT;
    args a1 = {o1, o2, wholeMap, "the whole map", fd};
    pthread_create(&wmT, nullptr, doAlgorithmMinDuration, (void*) &a1);
    args a2 = {o1, o2, noTolSystemMap, "the map without tol systems", fd};
    pthread_create(&ntT, nullptr, doAlgorithmMinDuration, (void*) &a2);
    args a3 = {o1, o2, highwayOnlyMap, "the map with highways only", fd};
    pthread_create(&hoT, nullptr, doAlgorithmMinDuration, (void*) &a3);
    args a4 = {o1, o2, wholeMap, "map with minimal crossroads", fd};
    pthread_create(&mcT, nullptr, doAlgorithmMnCrossroads, (void*) &a4);

    pthread_join(wmT, nullptr);
    pthread_join(ntT, nullptr);
    pthread_join(hoT, nullptr);
    pthread_join(mcT, nullptr);

    sem_destroy(&sem);
    close(fd);
    return 0;
}

void* doAlgorithmMinDuration(void* arg)
{
    args* a = static_cast<args*>(arg);
    auto path = dijkstra_min_duration(a->map, a->o1, a->o2);
    printPath(a, path, "s.");
    return nullptr;
}

void* doAlgorithmMnCrossroads(void* arg)
{
    args* a = static_cast<args*>(arg);
    auto path = dijkstra_min_crossroads(a->map, a->o1, a->o2);
    printPath(a, path, " crossroads.");
    return nullptr;
}

void printPath(const args* a, const std::pair<double, std::map<object, object>>& path, std::string searched_thing)
{
    std::stringstream out;
    if(path.first != std::numeric_limits<double>::max())
    {
        std::stack<std::string> directions;
        for(auto current = a->o2; current != a->o1; current = path.second.at(current))
        {
            std::stringstream s;
            s << "From " << path.second.at(current) << " go to " << current;
            //std::cout<<"From "<<path.second.at(current)<<" go to "<< current<<std::endl;

            directions.push(s.str());
        }

        out << std::endl << "Path in " << a->expl_str << std::endl;
        for(auto top = directions.top(); !directions.empty(); directions.pop(), top = !directions.empty() ?
                                                                                      directions.top() :
                                                                                      "")
        {
            out << top << std::endl;
        }
        out << "It will take you " << path.first << searched_thing << std::endl;

    }
    else
    {
        out << std::endl << "No path was found between " << a->o1 << " and " << a->o2 << " in " << a->expl_str << std::endl;
    }

    sem_wait(&sem);
    write(a->out,out.str().c_str(),out.str().size());
    sem_post(&sem);
}

object findObject(int x, int y, std::map<object, std::vector<std::pair<object, route> > >& map)
{
    for(auto& o:map)
    {
        if(o.first.getX() == x && o.first.getY() == y)
        {
            return o.first;
        }
    }
    return map.end()->first;
}

