#include <iostream>
#include <cstring>
#include "citymap.cpp"

using namespace std;

/**
 * The city map is represented as a weighted undirected graph.
 * The roads are edges and each crossroad is a vertex (node).
 * In order to simplify the understanding of the following code I tried
 * to name everything with its literature name.
 */


void testAddEdge() {
    cout << "###############" << endl;
    cout << "Test for addEdge" << endl;
    Graph graph;
    graph.addEdge("Sofia", "Burgas", 350);
    graph.addEdge("Sofia", "Kazichane", 12);
    graph.addEdge("Kazichane", "Sofia", 12);
    cout << "passed" << endl;
    cout << "###############" << endl;
}


void testHasPath() {
    cout << "###############" << endl;
    cout << "Test for hasPath {Real, Expected}" << endl;
    Graph graph;
    graph.addEdge("Sofia", "Burgas", 350);
    graph.addEdge("Sofia", "Kazichane", 12);
    graph.addEdge("Kazichane", "Sofia", 0);
    graph.addEdge("Kazichane", "Busmanci", 4);
    graph.addEdge("Burgas", "Busmanci", 320);

    cout << graph.hasPath("Sofia", "Burgas") << " should be 1" << endl;
    cout << graph.hasPath("Kazichane", "Burgas") << " should be 1" << endl;
    cout << graph.hasPath("Kazichane", "Busmanci") << " should be 1" << endl;
    cout << graph.hasPath("Burgas", "Kazichane") << " should be 0" << endl;

    cout << "###############" << endl;
}

void testDeadEnds() {
    cout << "###############" << endl;
    cout << "Test for findDeadEnds {Real, Expected}" << endl;
    Graph graph;
    graph.addEdge("Sofia", "Burgas", 350);
    graph.addEdge("Sofia", "Lozen", 20);
    graph.addEdge("Sofia", "Pernik", 70);
    graph.addEdge("Sofia", "Samokov", 70);
    graph.addEdge("Samokov", "Borovec", 5);
    graph.addEdge("Borovec", "Sofia", 75);


    vector<pair<string, string>> deadEnds = graph.findDeadEnds();

    vector<string> testAns = {"Sofia Burgas", "Sofia Lozen", "Sofia Pernik"};

    cout << "There was dead end between:" << endl;
    bool error = false;
    int i = 0;
    for (auto edge:deadEnds) {
        if ((edge.first + " " + edge.second).compare(testAns[i++]) != 0) {
            cout << edge.first << " " << edge.second << " real ans is " << testAns[i - 1] << endl;
        }
    }
    if (!error) {
        cout << "Passed" << endl;
    }
    cout << "###############" << endl;
}

void testHasCycle() {
    cout << "###############" << endl;
    cout << "Test for hasCycle" << endl;
    Graph g;
    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Sofia", 70);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Burgas", 450);

    cout << g.hasCycle("Sofia") << " should be 1" << endl;
    cout << g.hasCycle("Samokov") << " should be 1" << endl;
    cout << g.hasCycle("Bistrica") << " should be 0" << endl;
}

void testHasPathToAllOthers() {
    cout << "###############" << endl;
    cout << "Test for has path to all others" << endl;

    Graph g;
    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Sofia", 70);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Burgas", 450);
    g.addEdge("Burgas", "Bistrica", 450);

    cout << g.hasPathToAllOthers("Sofia") << " should be 1" << endl;
    cout << g.hasPathToAllOthers("Borovec") << " should be 1" << endl;
    cout << g.hasPathToAllOthers("Burgas") << " should be 0" << endl;

    g.addEdge("Mars", "Luna", 1);

    cout << g.hasPathToAllOthers("Mars") << " should be 0" << endl;
    cout << "###############" << endl;
}


void testShortestPath1() {
    cout << "###############" << endl;
    cout << "Test for shortest path 1" << endl;
    Graph g;

    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Sofia", 65);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Sofia", 3);
    g.addEdge("Bistrica", "Burgas", 450);
    g.addEdge("Burgas", "Bistrica", 450);

    vector<string> shortestPath = g.findShortestPath("Borovec", "Sofia");

    vector<string> testAns = {"Borovec", "Samokov", "Bistrica", "Sofia"};

    bool passed = true;
    for (int i = 0; i < shortestPath.size(); i++) {
        passed = passed && !shortestPath[i].compare(testAns[i]);
    }

    if (passed) {
        cout << "passed" << endl;
    } else {
        cout << "failed" << endl;
        for (int i = 0; i < shortestPath.size(); i++) {
            cout << shortestPath[i] << " ";
        }
        cout << endl;
    }
    cout << "###############" << endl;
}

void testShortestPath2() {
    cout << "###############" << endl;
    cout << "Test for shortest path 2" << endl;
    Graph g;

    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Sofia", 65);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Sofia", 3);
    g.addEdge("Bistrica", "Burgas", 450);
    g.addEdge("Burgas", "Bistrica", 450);
    g.addEdge("Borovec", "Mars", 3);
    g.addEdge("Mars", "Samokov", 0);
    g.addEdge("Mars", "Burgas", 3);
    g.addEdge("Burgas", "Luna", 1);
    g.addEdge("Luna", "Sofia", 2);

    vector<string> shortestPath = g.findShortestPath("Borovec", "Sofia");

    vector<string> testAns = {"Borovec", "Mars", "Burgas", "Luna", "Sofia"};

    bool passed = true;
    for (int i = 0; i < shortestPath.size(); i++) {
        passed = passed && !shortestPath[i].compare(testAns[i]);
    }

    if (passed) {
        cout << "passed" << endl;
    } else {
        cout << "failed" << endl;
        for (int i = 0; i < shortestPath.size(); i++) {
            cout << shortestPath[i] << " ";
        }
        cout << endl;
    }
    cout << "###############" << endl;
}

void testShortestPath3() {
    cout << "###############" << endl;
    cout << "Test for shortest path 3" << endl;
    Graph g;

    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Luna", "Mars", 0);

    vector<string> shortestPath = g.findShortestPath("Luna", "Sofia");

    cout << shortestPath.size() << " should be 0" << endl;
    cout << "###############" << endl;
}

void testTop3ShortestPaths1() {
    cout << "###############" << endl;
    cout << "Test for top 3 shortest path 1" << endl;
    Graph g;

    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Sofia", 3);
    g.addEdge("Bistrica", "Burgas", 450);

    vector<vector<string>> shortestPaths = g.findTop3ShortestPaths("Borovec", "Sofia");

    vector<vector<string>> testAns = {{"Borovec", "Samokov", "Bistrica", "Sofia"},
                                      {},
                                      {}};
    bool passed = true;
    for (int i = 0; i < shortestPaths.size(); i++) {
        passed = passed && shortestPaths[i] == testAns[i];
    }

    if (passed) {
        cout << "passed" << endl;
    } else {
        cout << "failed" << endl;
        for (int i = 0; i < shortestPaths.size(); i++) {
            if (shortestPaths[i].size() == 0) {
                cout << "NO PATH";
            }
            for (auto v: shortestPaths[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "###############" << endl;
}

void testTop3ShortestPaths2() {
    cout << "###############" << endl;
    cout << "Test for top 3 shortest path 2" << endl;
    Graph g;

    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Sofia", 65);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Sofia", 3);
    g.addEdge("Bistrica", "Burgas", 450);
    g.addEdge("Burgas", "Bistrica", 450);

    vector<vector<string>> shortestPaths = g.findTop3ShortestPaths("Borovec", "Sofia");

    vector<vector<string>> testAns = {{"Borovec", "Samokov", "Bistrica", "Sofia"},
                                      {"Borovec", "Samokov", "Sofia"},
                                      {"Borovec", "Samokov", "Bistrica", "Burgas", "Bistrica", "Sofia"}};
    bool passed = true;
    for (int i = 0; i < shortestPaths.size(); i++) {
        passed = passed && shortestPaths[i] == testAns[i];
    }

    if (passed) {
        cout << "passed" << endl;
    } else {
        cout << "failed" << endl;
        for (int i = 0; i < shortestPaths.size(); i++) {
            if (shortestPaths[i].size() == 0) {
                cout << "NO PATH";
            }
            for (auto v: shortestPaths[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "###############" << endl;
}


void testTop3ShortestPaths3() {
    cout << "###############" << endl;
    cout << "Test for top 3 shortest path 3" << endl;
    Graph g;

    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Sofia", 65);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Sofia", 3);
    g.addEdge("Bistrica", "Burgas", 450);
    g.addEdge("Burgas", "Bistrica", 450);
    g.addEdge("Borovec", "Mars", 3);
    g.addEdge("Mars", "Samokov", 0);
    g.addEdge("Mars", "Burgas", 3);
    g.addEdge("Burgas", "Luna", 1);
    g.addEdge("Luna", "Sofia", 2);

    vector<vector<string>> shortestPaths = g.findTop3ShortestPaths("Borovec", "Sofia");

    vector<vector<string>> testAns = {{"Borovec", "Mars", "Burgas",  "Luna",     "Sofia"},
                                      {"Borovec", "Mars", "Samokov", "Bistrica", "Sofia"},
                                      {"Borovec", "Mars", "Samokov", "Sofia"}};
    bool passed = true;
    for (int i = 0; i < shortestPaths.size(); i++) {
        passed = passed && shortestPaths[i] == testAns[i];
    }

    if (passed) {
        cout << "passed" << endl;
    } else {
        cout << "failed" << endl;
        for (int i = 0; i < shortestPaths.size(); i++) {
            if (shortestPaths[i].size() == 0) {
                cout << "NO PATH";
            }
            for (auto v: shortestPaths[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "###############" << endl;
}

void testTop3ShortestPathsClosed() {
    cout << "###############" << endl;
    cout << "Test for top 3 shortest path with closed vertex" << endl;
    Graph g;

    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Sofia", 65);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Sofia", 3);
    g.addEdge("Bistrica", "Burgas", 450);
    g.addEdge("Samokov", "Burgas", 470);
    g.addEdge("Burgas", "Bistrica", 450);
    g.addEdge("Burgas", "Sofia", 400);

    vector<string> closed = {"Bistrica"};
    vector<vector<string>> shortestPaths = g.findTop3ShortestPaths("Borovec", "Sofia", closed);

    vector<vector<string>> testAns = {{"Borovec", "Samokov", "Sofia"},
                                      {"Borovec", "Samokov", "Burgas", "Sofia"},
                                      {}};
    bool passed = true;
    for (int i = 0; i < shortestPaths.size(); i++) {
        passed = passed && shortestPaths[i] == testAns[i];
    }

    if (passed) {
        cout << "passed" << endl;
    } else {
        cout << "failed" << endl;
        for (int i = 0; i < shortestPaths.size(); i++) {
            if (shortestPaths[i].size() == 0) {
                cout << "NO PATH";
            }
            for (auto v: shortestPaths[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << "###############" << endl;
}

void testIsEulerian() {
    cout << "###############" << endl;
    cout << "Test for is eulerian" << endl;
    Graph g;

    g.addEdge("Sofia", "Burgas", 0);
    g.addEdge("Burgas", "Varna", 0);
    g.addEdge("Varna", "Sofia", 0);

    cout << g.isEulerian() << " should be 1" << endl;

    vector<string> path = g.findEulerianCycle();
    for (string vertex: path) {
        cout << vertex << " ";
    }
    cout << endl;

    g.addEdge("Sofia", "Pleven", 0);
    cout << g.isEulerian() << " should be 0" << endl;
    cout << "###############" << endl;

}

class Executor {
private:
    Graph *graph;
    string current;
    vector<string> closed;

    void printPath(vector<string> &path) {
        for (string node: path) {
            cout << node << " ";
        }
        cout << endl;
    }

public:
    Executor() {
        current = "";
    }

    Executor(Graph *g) {
        graph = g;
        current = "";
    }

    void execute(string command) {
        cout << "Received " << command << endl;
        if (command.compare("location") == 0) {
            cout << current << endl;
        } else if (command.compare("change") == 0) {
            string param;
            cin.get();
            cin >> param;
            current = param;
        } else if (command.compare("neighbours") == 0) {
            vector<string> neighbours = graph->getNeighbours(current);
            execute("location");
            printPath(neighbours); // neighbours look like path
        } else if (command.compare("move") == 0) {
            string param;
            cin.get();
            cin >> param;
            if (!graph->hasPath(current, param)) {
                cout << "No path between " << current << " and " << param << endl;
            } else {
                vector<string> path = graph->findShortestPath(current, param, closed);
                printPath(path);
                current = param;
            }

        } else if (command.compare("close") == 0) {
            string param;
            cin.get();
            cin >> param;
            closed.push_back(param);

        } else if (command.compare("open") == 0) {
            string param;
            cin.get();
            cin >> param;
            int index = -1;
            for (int i = 0; i < closed.size(); i++) {
                if (param.compare(closed[i]) == 0) {
                    index = i;
                    break;
                }
            }
            if (index != -1) {
                closed.erase(closed.begin() + index);
            }
        } else if (command.compare("closed") == 0) {
            printPath(closed);//closed again has the same struct as a path
        } else if (command.compare("tour") == 0) {
            if (graph->isEulerian()) {
                vector<string> path = graph->findEulerianCycle();//not really sure if the cycle should start with the current node
                printPath(path);
            } else {
                cout << "Sorry cannot do it";
            }
        } else {
            cout << "Invalid command" << endl;
        }
    }
};

class Cli {
private:
    Executor *executor;
public:
    Cli() {
        executor = new Executor();
    }

    Cli(Graph *g) {
        executor = new Executor(g);
    }

    ~Cli() {
        delete executor;
    }

    void readCommand() {
        string cmd;
        cin >> cmd;
        executor->execute(cmd);
    }
};

void runInInteraction() {
    cout << "Interactive mode" << endl;
    Graph g;
    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Sofia", 65);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Sofia", 3);
    g.addEdge("Bistrica", "Burgas", 450);
    g.addEdge("Samokov", "Burgas", 470);
    g.addEdge("Burgas", "Bistrica", 450);
    g.addEdge("Burgas", "Sofia", 400);
    Cli cli(&g);
    while (true) {
        cli.readCommand();
    }
}

int main(int argc, char *argv[]) {
//    testAddEdge();
//    testHasPath();
//    testDeadEnds();
//    testHasCycle();
//    testHasPathToAllOthers();
//    testShortestPath1();
//    testShortestPath2();
//    testShortestPath3();
//    testTop3ShortestPaths1();
//    testTop3ShortestPaths2();
//    testTop3ShortestPaths3();
//    testTop3ShortestPathsClosed();
//    testIsEulerian();

    if (argc > 0) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-i") == 0) {
                runInInteraction();
            }
        }
    }
    return 0;
}



