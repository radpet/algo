#include <vector>
#include <utility>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>

struct Edge {

    int to;
    int cost;

    Edge() {

    }

    Edge(int _to, int _cost) : to(_to), cost(_cost) {

    }

    bool operator()(Edge a, Edge b) {
        return a.cost > b.cost;
    }
};

class Graph {
private:
    // a entry for each node holding vector for edges starting from it
    std::vector<std::vector<Edge> > G;

    std::unordered_map<std::string, int> nameToId;
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

    static std::vector<int>
    findShortestPath(int from, int to, std::vector<std::vector<Edge>> &G, std::set<int> forbiddenVertex) {

        int dist[G.size()];
        int pred[G.size()];

        for (int i = 0; i < G.size(); i++) {
            dist[i] = 1 << 30;
            pred[i] = i;
        }
        std::priority_queue<Edge, std::vector<Edge>, Edge> Q;

        Q.push(Edge(from, 0));
        bool found = false;

        while (!Q.empty()) {
            Edge current = Q.top();
            Q.pop();
            if (forbiddenVertex.count(current.to)) {
                continue;
            }
            if (current.to == to) {
                found = true;
                break;
            }

            for (Edge &edge: G[current.to]) {
                if (dist[edge.to] > current.cost + edge.cost) {
                    pred[edge.to] = current.to;
                    dist[edge.to] = current.cost + edge.cost;
                    Q.push(Edge(edge.to, current.cost + edge.cost));
                }

            }
        }


        std::vector<int> result;
        if (found) {
            int start = to;
            while (start != from) {
                result.push_back(start);
                start = pred[start];
            }
            result.push_back(from);
            std::reverse(std::begin(result), std::end(result));
        }

        return result;
    }

    std::vector<std::string> transformIdToName(std::vector<int> &ids) {
        std::vector<std::string> result;
        for (int vertex:ids) {
            result.push_back(idToName[vertex]);
        }
        return result;
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

    bool hasPathToAllOthers(const std::string from) {
        if (nameToId.count(from) == 0) {
            return false;
        }
        int fromIndex = nameToId[from];

        bool pathToAll = true;

        for (int i = 0; i < G.size(); i++) {
            if (i != fromIndex) {
                pathToAll = pathToAll && hasPathInternal(fromIndex, i);
            }
        }

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
        int fromIndex = nameToId[from];
        int endIndex = nameToId[end];

        std::vector<int> path = findShortestPath(fromIndex, endIndex, G, {});

        return transformIdToName(path);
    }

    std::vector<std::string>
    findShortestPath(const std::string from, const std::string end, std::vector<std::string> closed) {
        int fromIndex = nameToId[from];
        int endIndex = nameToId[end];

        std::set<int> forbiddenVertex = {};

        for (std::string closedV: closed) {
            forbiddenVertex.insert(nameToId[closedV]);
        }

        std::vector<int> path = findShortestPath(fromIndex, endIndex, G, forbiddenVertex);

        return transformIdToName(path);
    }

    std::vector<std::vector<std::string>> findTop3ShortestPaths(const std::string from, const std::string end) {
        std::set<int> forbiddenVertex = {};
        std::vector<int> first = findShortestPath(nameToId[from], nameToId[end], G, {});
        std::vector<std::vector<Edge>> g = G;

        for (int i = 0; i < first.size() - 1; i++) {

            std::vector<Edge> currentNeigh = g[first[i]];
            int delPos = -1;
            for (int j = 0; j < currentNeigh.size(); j++) {
                if (currentNeigh[j].to == first[i + 1]) {
                    delPos = j;
                    break;
                }
            }

            if (delPos != -1) {
                currentNeigh.erase(currentNeigh.begin() + delPos);
            }

            g[first[i]] = currentNeigh;
        }

        std::vector<int> second = findShortestPath(nameToId[from], nameToId[end], g, {});
        if (second.size() <= 2) {
            return {transformIdToName(first), transformIdToName(second), {}};
        }

        for (int i = 0; i < second.size() - 1; i++) {
            std::vector<Edge> currentNeigh = g[second[i]];
            int delPos = -1;
            for (int j = 0; j < currentNeigh.size(); j++) {
                if (currentNeigh[j].to == second[i + 1]) {
                    delPos = j;
                    break;
                }
            }

            if (delPos != -1) {
                currentNeigh.erase(currentNeigh.begin() + delPos);
            }

            g[second[i]] = currentNeigh;
        }

        std::vector<int> third = findShortestPath(nameToId[from], nameToId[end], g, {});

        return {transformIdToName(first), transformIdToName(second), transformIdToName(third)};

    }


};

