#include <iostream>
#include "graph.h"
#include "busPath.h"
#include "basicPath.h"
#include "refillPath.h"

void busSolve ()
{
    int N, start, finish, pathsNumber;

    std::cin >> N >> start >> finish >> pathsNumber;

    graph<busPath> g(N);

    for (int i = 0; i < pathsNumber; i++)
    {
        int in, out, timeIn, timeOut;
        std::cin >> in >> timeIn >> out >> timeOut;
        g.addEdge( in - 1, out - 1, *( new busPath(timeIn, timeOut) ) );
    }

    g.dijkstra(start - 1);

    if (g.getPath(finish - 1).getIsInf())
        std::cout << -1 << std::endl;
    else
        std::cout << g.getPath(finish - 1) << std::endl;
}

void refillSolve ()
{
    int N, M;
    std::cin >> N;

    graph<refillPath> g(N);

    int costes[N];

    for (int i = 0; i < N; i++)
        std::cin >> costes[i];

    std::cin >> M;

    for (int i = 0; i < M; i++)
    {
        int first, second;
        std::cin >> first >> second;
        g.addEdge( first - 1, second - 1, *(new refillPath(costes[first - 1])) );
        g.addEdge( second - 1, first - 1, *(new refillPath(costes[second - 1])) );
    }

    g.dijkstra(0);

    if (g.getPath(N - 1).getIsInf())
        std::cout << -1 << std::endl;
    else
        std::cout << g.getPath(N - 1) << std::endl;
}

int main()
{
    int enter;

    std::cout << "If you want to solve bus problem, enter 0. If you want to solve refill problem, enter 1." << std::endl;
    std::cin >> enter;
    if (enter == 0)
        busSolve();
    else if (enter == 1)
        refillSolve();
    return 0;
}
