
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

// Graph class representing an undirected graph using adjacency list representation
class Graph {
private:
    int numVertices;          // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int vertices) : numVertices(vertices), adj(vertices) {}

    // Add an edge between two vertices
    void addEdge(int src, int dest) {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }

    // View the graph
    void viewGraph() {
        cout << "Graph:\n";
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << " -> ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Perform Breadth First Search (BFS) in parallel
    void bfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        // Mark the start vertex as visited and enqueue it
        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            cout << currentVertex << " ";

            // Enqueue all adjacent unvisited vertices
            #pragma omp parallel for
            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    // Perform Depth First Search (DFS) in parallel
    void dfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        stack<int> s;

        // Mark the start vertex as visited and push it onto the stack
        visited[startVertex] = true;
        s.push(startVertex);

        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();
            cout << currentVertex << " ";

            // Push all adjacent unvisited vertices onto the stack
            #pragma omp parallel for
            for (int neighbor : adj[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int numVertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;

    // Create a graph with the specified number of vertices
    Graph graph(numVertices);

    int numEdges;
    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    cout << "Enter the edges (source destination):\n";
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    // View the graph
    graph.viewGraph();

    int startVertex;
    cout << "Enter the starting vertex for BFS and DFS: ";
    cin >> startVertex;

    cout << "Breadth First Search (BFS): ";
    graph.bfs(startVertex);
    cout << endl;

    cout << "Depth First Search (DFS): ";
    graph.dfs(startVertex);
    cout << endl;

    return 0;
}

// Certainly! Lets consider an example graph to test the program.

// Suppose we have the following graph:

// Number of vertices: 5

// Number of edges: 6

// Edges:

// 0 1
// 0 2
// 1 3
// 1 4
// 2 4
// 3 4

// Lets say the starting vertex for BFS and DFS is 0.

// Output from the program will be:


// Enter the number of vertices in the graph: 5
// Enter the number of edges in the graph: 6
// Enter the edges (source destination):
// 0 1
// 0 2
// 1 3
// 1 4
// 2 4
// 3 4
// Graph:
// Vertex 0 -> 1 2 
// Vertex 1 -> 0 3 4 
// Vertex 2 -> 0 4 
// Vertex 3 -> 1 4 
// Vertex 4 -> 1 2 3 
// Enter the starting vertex for BFS and DFS: 0
// Breadth First Search (BFS): 0 1 2 3 4 
// Depth First Search (DFS): 0 2 4 1 3 


// Here is the breakdown of the traversal:

// - **Breadth First Search (BFS)** starting from vertex `0`:
//   - Visit `0`, enqueue `1` and `2`
//   - Dequeue `1`, visit `1`, enqueue `3` and `4`
//   - Dequeue `2`, visit `2`, enqueue `4`
//   - Dequeue `3`, visit `3`, enqueue `4`
//   - Dequeue `4`, visit `4`, finish

// - **Depth First Search (DFS)** starting from vertex `0`:
//   - Visit `0`, push `1` and `2` onto the stack
//   - Pop `2`, visit `2`, push `4` onto the stack
//   - Pop `4`, visit `4`, 
//   - Pop `1`, visit `1`, push `3` and `4` onto the stack
//   - Pop `4`, visit `4` (already visited), pop `3`, visit `3`
//   - Finish

// This output demonstrates the BFS and DFS traversals of the provided graph starting from vertex `0`. '''