#include <iostream>
#include "citymap.cpp"

using namespace std;

/**
 * The city map is represented as a weighted undirected graph.
 * The roads are edges and each crossroad is a vertex (node).
 * In order to simplify the understanding of the following code I tried
 * to name everything with its abstract (math) name.
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
    cout << "Test for shortest path 1" << endl;
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
    cout << "Test for shortest path 2" << endl;
    Graph g;

    g.addEdge("Sofia", "Borovec", 75);
    g.addEdge("Borovec", "Samokov", 5);
    g.addEdge("Samokov", "Sofia", 65);
    g.addEdge("Samokov", "Bistrica", 60);
    g.addEdge("Bistrica", "Sofia", 3);
    g.addEdge("Bistrica", "Burgas", 450);
    g.addEdge("Burgas", "Bistrica", 450);
    g.addEdge("Borovec", "Sofia", 500);

    vector<vector<string>> shortestPaths = g.findTop3ShortestPaths("Borovec", "Sofia");

    vector<vector<string>> testAns = {{"Borovec", "Samokov", "Bistrica", "Sofia"},
                                      {"Borovec", "Sofia"},
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


void testTop3ShortestPaths3() {
    cout << "###############" << endl;
    cout << "Test for shortest path 3" << endl;
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

    vector<vector<string>> testAns = {{"Borovec", "Mars",    "Burgas",   "Luna", "Sofia"},
                                      {"Borovec", "Samokov", "Sofia"},
                                      {"Borovec", "Samokov", "Bistrica", "Sofia"}};
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

int main() {
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
    testTop3ShortestPaths3();
    return 0;
}



