#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100; // Max number of vertices

class Graph {
private:
    int adj[MAX][MAX]; // Adjacency matrix
    int vertices;

public:
    Graph(int v) {  
        vertices = v;
        for (int i = 0; i < vertices; i++)
            for (int j = 0; j < vertices; j++)
                adj[i][j] = 0;
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1; // Remove this line for directed graph
    }

    void BFS(int start) {
        bool visited[MAX] = {false};
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int i = 0; i < vertices; i++) {
                if (adj[node][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int v, e;
    cout << "Enter number of vertices: ";
    cin >> v;
    Graph g(v);

    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting node for BFS: ";
    cin >> start;

    g.BFS(start);

    return 0;
}
