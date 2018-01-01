#include <iostream>
#include "citymap.cpp"

using namespace std;

void testAddEdge() {
    Graph graph;
    graph.addEdge("Sofia", "Burgas", 350);
    graph.addEdge("Sofia", "Kazichane", 12);
    graph.addEdge("Kazichane", "Sofia", 12);
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

int main() {
    testAddEdge();
    testHasPath();
    return 0;
}



