Нека са дадени следните структури от данни, описващи граф с числа по върховете чрез списък от наследници:
struct Vertex { int u; VertexList* successors; Vertex* next; };
struct VertexList { int v; VertexList* next; };
Да се реализира функция,
VertexList* longestPath(Vertex* graph, int u, int v);
която конструира и намира най-дългият възможен ацикличен път в графа представен чрез указателя graph от връх u до връх v, ако такъв има, в противен случай връща nullptr.
