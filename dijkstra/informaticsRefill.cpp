#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

class refillPath
{
private:
    int cost;
    bool isInf;

public:
    refillPath(int inCost) : cost(inCost), isInf(false) {} // Конструктор, задающий все поля
    refillPath(bool inIsInf = false) : isInf(inIsInf) // Конструктор для создания пути бесконечной или нулевой длины
    {
        isInf = inIsInf;
        cost = 0; // Если isInf == true, то pathLen уже не важна
    }

    refillPath& mergeWith (refillPath& inPath)
    {
        if (isInf || inPath.isInf)
            return *(new refillPath(true));
        else
            return *(new refillPath(cost + inPath.cost));
    }

    bool getIsInf ()
    {
        return isInf;
    }

    friend bool operator < (const refillPath& inPathLeft, const refillPath& inPathRight)
    {
        if (!inPathLeft.isInf && !inPathRight.isInf)
        {
            return (inPathLeft.cost < inPathRight.cost);
        }
        else if (!inPathLeft.isInf || !inPathRight.isInf)
        {
            if (inPathLeft.isInf)
                return false;
            else
                return true;
        }
    }

    friend std::ostream& operator << (std::ostream& outStream, refillPath& inPath)
    {
        if (!inPath.isInf)
            outStream << inPath.cost;
        else
            outStream << "inf";
        return outStream;
    }
};

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
    int size;                                      // Кол-ыо вершин в графе
    std::vector< path > paths;                     // Расстояния от стартовой вершины до всех остальных
    std::vector< std::vector< std::pair<int, path> > > edges;  // Ребра

public:
    graph(int inSize)
    {
        size = inSize;
        edges.resize(size);

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

    void dijkstra (int start)
    {
        std::multiset< std::pair<int, path>, edgeCompare<path> > visited;
        visited.insert( std::make_pair(start, path() ) );
        paths[start] = path();

        while (!visited.empty())
        {
            int current = visited.begin()->first;
            visited.erase(visited.begin());
            for (auto it = edges[current].begin(); it != edges[current].end(); ++it)
            {
                if ( paths[current].mergeWith(it->second) < paths[it->first] )
                {
                    visited.erase( std::make_pair(it->first, paths[it->first]) );
                    paths[it->first] = paths[current].mergeWith(it->second);
                    visited.insert( std::make_pair(it->first, paths[current].mergeWith(it->second) ) );
                }
            }
        }
    }
};

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
    refillSolve();
    return 0;
}
