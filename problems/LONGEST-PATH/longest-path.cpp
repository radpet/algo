#include<iostream>
#include<vector>

using namespace std;

struct VertexList {
    int v;
    VertexList *next;
};

struct Vertex {
    int u;
    VertexList *successors;
    Vertex *next;
};

bool inList(int a, vector<int> &b) {
    for (int i:b) {
        if (i == a) {
            return true;
        }
    }
    return false;
}

void solve(Vertex *graph, vector<int> &path, vector<int> &bestPath, int current, int final) {
    if (current == final) {
        if (path.size() > bestPath.size()) {
            bestPath = path;
        }
    }

    Vertex *begin = graph;

    bool found = false;
    while (begin != nullptr && begin->u != current) {
        begin = begin->next;
    }

    //begin->u != nullptr;

    VertexList *children = begin->successors;

    while (children != nullptr) {

        if (!inList(children->v, path)) {
            path.push_back(children->v);
            solve(graph, path, bestPath, children->v, final);
            path.pop_back();
        }

        children = children->next;
    }

}

VertexList *longestPath(Vertex *graph, int u, int v) {

    vector<int> path = {u};
    vector<int> bestPath = {u};

    solve(graph, path, bestPath, u, v);

    VertexList *result = new VertexList();

    VertexList *constr = result;
    for (int i = 0; i < bestPath.size(); i++) {
        constr->v = bestPath[i];
        if (i < bestPath.size() - 1) {
            constr->next = new VertexList();
        } else {
            constr->next = nullptr;
        }
        constr = constr->next;
        //cout << bestPath[i] << " ";
    }
    //cout << endl;

    return result;

}


void printList(Vertex *graph) {
    while (graph != nullptr) {
        cout << "Node with id: " << graph->u;

        VertexList *children = graph->successors;
        cout << "[ ";
        while (children != nullptr) {
            cout << children->v << " ";
            children = children->next;
        }
        cout << " ]" << endl;
        graph = graph->next;
    }
}

int main() {

    Vertex *graph = new Vertex();
    graph->u = 0;

    VertexList *_0_s = new VertexList();
    _0_s->v = 1;

    VertexList *_0_s_2 = new VertexList();
    _0_s_2->v = 2;
    _0_s_2->next = nullptr;

    _0_s->next = _0_s_2;

    graph->successors = _0_s;

    Vertex *_1 = new Vertex();
    _1->u = 1;

    VertexList *_1_s_2 = new VertexList();
    _1_s_2->v = 2;

    VertexList *_1_s_3 = new VertexList;
    _1_s_3->v = 3;
    _1_s_3->next = nullptr;
    _1_s_2->next = _1_s_3;

    _1->successors = _1_s_2;

    Vertex *_2 = new Vertex();
    _2->u = 2;
    _2->successors = nullptr;

    Vertex *_3 = new Vertex();
    _3->u = 3;

    VertexList *_3_2 = new VertexList();
    _3_2->v = 2;
    _3_2->next = nullptr;

    _3->successors = _3_2;

    graph->next = _1;
    _1->next = _2;
    _2->next = _3;
    _3->next = nullptr;

    VertexList *path = longestPath(graph, 0, 2);

    VertexList *tmp = path;
    while (tmp != nullptr) {
        cout << tmp->v << " ";
        tmp = tmp->next;
    }
    cout << endl;
    printList(graph);
}
