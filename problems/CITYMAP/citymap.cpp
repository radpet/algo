#include <vector>
#include <utility>
#include <unordered_map>

struct Edge {

    int to;
    int cost;

    Edge(int _to, int _cost) : to(_to), cost(_cost) {

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
        G[k];
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


public:
    void addEdge(const std::string from, const std::string to, int cost) {
        //there was no such node so far as starting point
        tryAddNewNode(from);

        // there was no such node so far for ending
        tryAddNewNode(to);

        addEdgeInternal(nameToId[from], nameToId[to], cost);

    }


    bool hasPath(const std::string from, const std::string to) {
        return hasPathInternal(nameToId[from], nameToId[to]);
    }

    bool hasEulerPath() {

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
};

