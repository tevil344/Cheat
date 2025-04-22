#include<iostream>
#include<climits>
#include<queue>
using namespace std;

# define MAX 1000

int graph[MAX][MAX];
int dist[MAX];
bool visited[MAX];

void djikstra(int nodes, int source){
    for(int i = 0;i<nodes;i++){
        dist[i]=INT_MAX;
        visited[i]=false;
    }

    dist[source]=0;

    for(int i=0;i<nodes - 1;++i){
        int u = -1;
        
        for(int j=0;j<nodes;++j){
            if(!visited[j] && (u==-1||dist[j]<dist[u])){
                u=j;
            }
        }
        if(dist[u]==INT_MAX){
            break;
        }
        visited[u]=true;

        for(int v=0;v<nodes;++v){
            if(graph[u][v] && !visited[v]){
                int newdist = dist[u]+graph[u][v];
                if(newdist < dist[v]){
                    dist[v]=newdist;
                }
            }
        }
    }
    cout << "\nShortest distances from location " << source << ":\n";
    for (int i = 0; i < nodes; ++i) {
        if (dist[i] == INT_MAX)
            cout << "Location " << i << ": Unreachable\n";
        else
            cout << "Location " << i << ": " << dist[i] << " units\n";
    }
}

int main(){
    int nodes, edges;
    cout << "Enter number of locations: ";
    cin >> nodes;

    // Initialize graph with 0s
    for (int i = 0; i < nodes; ++i) {
        for (int j = 0; j < nodes; ++j) {
            graph[i][j] = 0;
        }
    }

    cout << "Enter number of transport links: ";
    cin >> edges;

    cout << "Enter each link in the format: from to distance\n";
    for (int i = 0; i < edges; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;

        // Update the adjacency matrix
        graph[from][to] = weight;
        graph[to][from] = weight; // Since the graph is undirected
    }

    int source;
    cout << "Enter the starting location: ";
    cin >> source;

    djikstra(nodes, source);

    return 0;
}
