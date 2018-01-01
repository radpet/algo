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
    cout << "There was dead end between:" << endl;
    for (auto edge:deadEnds) {
        cout << edge.first << " " << edge.second << endl;
    }
    cout << "###############" << endl;
}

int main() {
    testAddEdge();
    testHasPath();
    testDeadEnds();
    return 0;
}



