#include <vector>
#include <utility>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>

/**
 * Holds where the edge is pointing and its cost
 */
struct Edge {

    int to;
    int cost;

    Edge() {

    }

    Edge(int _to, int _cost) : to(_to), cost(_cost) {

    }
};

/**
 * Used in as comparator class for the priority queue. It orders the pairs by the cost of the path
 * the path is list stored on second position.
 */
struct EdgeAndPathCompare {
    bool operator()(std::pair<Edge, std::vector<int>> a, std::pair<Edge, std::vector<int>> b) {
        return a.first.cost > b.first.cost;
    }
};

class Graph {
private:
    // a entry for each node holding vector for edges starting from it
    std::vector<std::vector<Edge> > G;

    // maps vertex name to int
    std::unordered_map<std::string, int> nameToId;

    // reverse map in order to display the name of a vertex
    std::unordered_map<int, std::string> idToName;

    void tryAddNewNode(const std::string name) {
        if (nameToId.count(name) == 0) {
            std::vector<Edge> edges;
            G.push_back(edges);
            int id = G.size() - 1;
            nameToId[name] = id;
            idToName[id] = name;
        }
    }

    void addEdgeInternal(int from, int to, int cost) {
        G[from].push_back(Edge(to, cost));
    }

    void dfs(int k, bool *used) {
        used[k] = true;
        for (Edge &edge :G[k]) {
            if (!used[edge.to]) {
                dfs(edge.to, used);
            }
        }
    }

    bool hasPathInternal(int from, int to) {
        bool used[G.size()];
        for (int i = 0; i < G.size(); i++) {
            used[i] = false;
        }

        dfs(from, used); // O(|V|+|E|)
        return used[to];
    }

    /**
     * Runs modified dijkstra in order to retrieve the top 3 shortest paths.
     * @param from  the start vertex
     * @param to the end vertex
     * @param forbiddenVertex set containing vertex that should not be part of the path
     * @return list of paths sorted in shortest order
     */
    std::vector<std::vector<int>>
    findShortestPath(int from, int to, std::set<int> forbiddenVertex) {
        std::vector<int> count;
        count.resize(G.size());

        for (int i = 0; i < G.size(); i++) {
            count[i] = 0;
        }

        std::priority_queue<std::pair<Edge, std::vector<int>>, std::vector<std::pair<Edge, std::vector<int>>>, EdgeAndPathCompare> Q;
        std::vector<int> a = {from};
        Q.push(std::make_pair(Edge(from, 0), a));

        std::vector<std::vector<int>> paths;

        while (!Q.empty()) {
            std::pair<Edge, std::vector<int>> current = Q.top();
            Q.pop();
            if (forbiddenVertex.count(current.first.to)) {
                continue;
            }
            if (count[current.first.to] >= 3) {
                break;
            }
            count[current.first.to] += 1;
            if (current.first.to == to) {
                paths.push_back(current.second);
                continue;
            }

            for (Edge &edge: G[current.first.to]) {
                // at each step I will store the path too
                std::vector<int> newPath = current.second;
                newPath.push_back(edge.to);
                Q.push(std::make_pair(Edge(edge.to, current.first.cost + edge.cost), newPath));
            }
        }
        while (paths.size() < 3) {
            paths.push_back({});
        }
        return paths;
    }

    std::vector<std::string> transformIdToName(std::vector<int> &ids) {
        std::vector<std::string> result;
        for (int vertex:ids) {
            result.push_back(idToName[vertex]);
        }

        return result;
    }

    bool findEulerianCycleInternal(std::vector<int> &path, int current, bool **&used,
                                   int remaining) {
        if (remaining == 0) {
            return true;
        }

        for (Edge &edge: G[current]) {
            if (!used[current][edge.to]) {
                path.push_back(edge.to);
                used[current][edge.to] = true;
                if (findEulerianCycleInternal(path, edge.to, used, remaining - 1)) {
                    return true;
                }
                used[current][edge.to] = false;
                path.pop_back();
            }
        }

        return false;
    }

public:
    void addEdge(const std::string from, const std::string to, int cost) {
        //there was no such node so far as starting point
        tryAddNewNode(from);

        // there was no such node so far for ending
        tryAddNewNode(to);

        addEdgeInternal(nameToId[from], nameToId[to], cost);

    }

    bool hasPath(const std::string from, const std::string to) {
        if (!nameToId.count(from) || !nameToId.count(to)) {
            return false;
        }
        return hasPathInternal(nameToId[from], nameToId[to]);
    }

    /**
     * Runs bfs from the start vertex and finds if there is cycle including this vertex as beginning.
     * @param start the start vertex
     * @return true if there is path start->p1->p2->..->start, false otherwise
     */
    bool hasCycle(const std::string start) {
        if (nameToId.count(start) == 0) {
            return false;
        }
        bool used[G.size()];
        for (int i = 0; i < G.size(); i++) {
            used[i] = false;
        }
        int startId = nameToId[start];
        std::queue<int> Q;

        Q.push(startId);

        while (!Q.empty()) {
            int current = Q.front();
            Q.pop();
            if (used[startId]) {
                return true;
            }
            for (Edge &edge: G[current]) {
                if (!used[edge.to]) {
                    used[edge.to] = true;
                    Q.push(edge.to);
                }
            }

        }

        return false;
    }

    /**
     * Runs dfs in order to check if there is path from the start to all other vertices in the graph.
     * @param from the start vertex
     * @return true if all other nodes can be visited from the from start
     */
    bool hasPathToAllOthers(const std::string from) {
        if (nameToId.count(from) == 0) {
            return false;
        }
        int fromIndex = nameToId[from];

        bool pathToAll = true;

        bool *used = new bool[G.size()];
        for (int i = 0; i < G.size(); i++) {
            used[i] = false;
        }

        dfs(nameToId[from], used);

        for (int i = 0; i < G.size(); i++) {
            if (i != fromIndex) {
                pathToAll = pathToAll && used[i];
            }
        }

        delete[] used;

        return pathToAll;
    }

    std::vector<std::pair<std::string, std::string>> findDeadEnds() {

        std::vector<std::pair<std::string, std::string>> deadEnds;

        for (int i = 0; i < G.size(); i++) { // this is the id of each node
            for (Edge &edge : G[i]) {
                if (G[edge.to].size() == 0) { // the end of the current edge has no connected edges
                    deadEnds.push_back(std::make_pair(idToName[i], idToName[edge.to]));
                }
            }
        }

        return deadEnds;
    }

    std::vector<std::string> findShortestPath(const std::string from, const std::string end) {
        if (!nameToId.count(from) || !nameToId.count(end)) {
            return {};
        }
        int fromIndex = nameToId[from];
        int endIndex = nameToId[end];

        std::vector<int> path = findShortestPath(fromIndex, endIndex, {})[0];

        return transformIdToName(path);
    }

    std::vector<std::vector<std::string>> findTop3ShortestPaths(const std::string from, const std::string end) {
        if (!nameToId.count(from) || !nameToId.count(end)) {
            return {};
        }
        std::vector<std::vector<int>> shortest = findShortestPath(nameToId[from], nameToId[end], {});
        std::vector<std::vector<std::string>> ans;
        for (auto path : shortest) {
            ans.push_back(transformIdToName(path));
        }
        return ans;
    }

    std::vector<std::vector<std::string>>
    findTop3ShortestPaths(const std::string from, const std::string end, std::vector<std::string> closedList) {
        if (!nameToId.count(from) || !nameToId.count(end)) {
            return {};
        }
        std::set<int> forbiddenVertex = {};
        for (std::string closed: closedList) {
            if (nameToId.count(closed)) {
                forbiddenVertex.insert(nameToId[closed]);
            }
        }
        std::vector<std::vector<int>> shortest = findShortestPath(nameToId[from], nameToId[end], forbiddenVertex);
        std::vector<std::vector<std::string>> ans;
        for (auto path : shortest) {
            ans.push_back(transformIdToName(path));
        }
        return ans;
    }

    std::vector<std::string> findEulerianCycle() {
        if (!isEulerian()) {
            return {};
        }

        int edgeCount = 0;
        for (int i = 0; i < G.size(); i++) {
            edgeCount += G[i].size();
        }

        std::vector<int> path;

        bool **used = new bool *[G.size()];

        for (int i = 0; i < G.size(); i++) {
            used[i] = new bool[G.size()];
            for (int j = 0; j < G.size(); j++) {
                used[i][j] = 0;
            }
        }

        findEulerianCycleInternal(path, 0, used, edgeCount);

        for (int i = 0; i < G.size(); i++) {
            delete[] used[i];
        }
        delete[] used;
        return transformIdToName(path);
    }

    bool isEulerian() {
        int *inDegree = new int[G.size()];

        for (int i = 0; i < G.size(); i++) {
            inDegree[i] = 0;
        }

        for (int i = 0; i < G.size(); i++) {

            for (Edge &edge: G[i]) {
                inDegree[edge.to] += 1;
            }
        }

        bool eulerian = true;

        for (int i = 0; i < G.size(); i++) {
            if (G[i].size() != inDegree[i]) {
                eulerian = false;
                break;
            }
        }

        delete[] inDegree;

        return eulerian;
    }

};

