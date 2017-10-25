#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

class busPath
{
private:
    int timeIn;
    int timeOut;
    bool isInf;

public:
    busPath(int inTimeIn, int inTimeOut) : timeIn(inTimeIn), timeOut(inTimeOut), isInf(false) {} // Конструктор, задающий все поля
    busPath(bool inIsInf = false) : isInf(inIsInf) // Конструктор для создания пути бесконечной или нулевой длины
    {
        isInf = inIsInf;
        timeIn = 0; // Если isInf == true, то time уже не важны
        timeOut = 0;
    }

    busPath& mergeWith (busPath& inPath)
    {
        if ( (isInf || inPath.isInf) || (timeOut > inPath.timeIn) )
            return *(new busPath(true));
        else
            return *(new busPath(timeIn, inPath.timeOut));
    }

    bool getIsInf ()
    {
        return isInf;
    }

    friend bool operator < (const busPath& inPathLeft, const busPath& inPathRight)
    {
        if (!inPathLeft.isInf && !inPathRight.isInf)
        {
            return (inPathLeft.timeOut < inPathRight.timeOut);
        }
        else if (!inPathLeft.isInf || !inPathRight.isInf)
        {
            if (inPathLeft.isInf)
                return false;
            else
                return true;
        }
    }

    friend std::ostream& operator << (std::ostream& outStream, busPath& inPath)
    {
        if (!inPath.isInf)
            outStream << inPath.timeOut;
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

int main()
{
    busSolve();
    return 0;
}
