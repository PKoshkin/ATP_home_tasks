#ifndef GRAPH_KOSHKIN_PAVEL_493
#define GRAPH_KOSHKIN_PAVEL_493

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

template <class path>
struct edgeCompare // Класс для сравнения вершин (по длине пути)
{
    bool operator () (const std::pair<int, path>& pairLeft, const std::pair<int, path>& pairRight)
    {
        return ( pairLeft.second < pairRight.second );
    }
};

template <class path>
class graph
{
private:
    int size;                                                   // Кол-ыо вершин в графе
    int startVertex;                                            // Стартовая вершина. Нужна для восстановления пути
    std::vector< path > paths;                                  // Расстояния от стартовой вершины до всех остальных
    std::vector< std::vector< std::pair<int, path> > > edges;   // Ребра
    std::vector< int > ancesters;                               // Для восстановления пути

public:
    graph(int inSize)
    {
        size = inSize;
        edges.resize(size);
        ancesters.resize(size);

        // Изначальо сделаем все расстояния до вершин бесконечные
        for (int i = 0; i < size; i++)
            paths.push_back( path(true) );
    }

    void addEdge (int first, int second, path& inPath)
    {
        edges[first].push_back( std::make_pair(second, inPath) );
    }

    path& getPath(int in)
    {
        return paths[in];
    }

    friend std::ostream& operator << (std::ostream& outStream, graph<path>& inGraph)
    {
        for (int i = 0; i < inGraph.size; i++)
        {
            outStream << i;
            if (!inGraph.paths[i].getIsInf())
                outStream << "-" << inGraph.paths[i];
            outStream << std::endl;
        }
        return outStream;
    }

    void showPath (int inVertNum)
    {
        std::cout << inVertNum;
        inVertNum = ancesters[inVertNum];
        while (inVertNum != startVertex)
        {
            std::cout << '-' << inVertNum;
            inVertNum = ancesters[inVertNum];
        }
    }

    void dijkstra (int start)
    {
        std::multiset< std::pair<int, path>, edgeCompare<path> > visited;
        visited.insert( std::make_pair(start, path() ) );
        paths[start] = path();

        startVertex = start;

        while (!visited.empty())
        {
            int current = visited.begin()->first;
            visited.erase(visited.begin());
            for (auto it = edges[current].begin(); it != edges[current].end(); ++it)
            {
                if ( paths[current].mergeWith(it->second) < paths[it->first] )
                {
                    ancesters[it->first] = current;
                    visited.erase( std::make_pair(it->first, paths[it->first]) );
                    paths[it->first] = paths[current].mergeWith(it->second);
                    visited.insert( std::make_pair(it->first, paths[current].mergeWith(it->second) ) );
                }
            }
        }
    }
};

#endif // GRAPH_KOSHKIN_PAVEL_493
