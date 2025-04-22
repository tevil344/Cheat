#include<iostream>
#include<climits>
#include<queue>
using namespace std;

class disjoint{
    int parent[1000];

    public:

    void makeset(int n){
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    void unite(int x, int y){
        int xr = find(x);
        int yr = find(y);
        if(xr!=yr){
            parent[xr]=yr;
        }
    }
};

class Edge{
    public:
    int src, dest, weight;
};

void sortEdges(Edge edges[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(edges[j].weight > edges[j+1].weight){
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
}

void kruskal(int matrix[100][100], int V){
    Edge edges[1000];
    int edgeCount = 0;

    for(int i=0;i<V;i++){
        for(int j=i+1;j<V;j++){
            if(matrix[i][j] != 0 && matrix[i][j] != INT_MAX){
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = matrix[i][j];
                edgeCount++;
            }
        }
    }
    
    sortEdges(edges, edgeCount);

    disjoint ds;
    ds.makeset(V);
    int totalcost = 0;

    for(int i =0;i<edgeCount;i++){
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;

        if(ds.find(u)!=ds.find(v)){
            cout<<u<<"--"<<v<<"=="<<w<<endl;
            totalcost+=w;
            ds.unite(u,v);
        }
    }
        cout<<"Total Cost of MST is "<<totalcost<<endl;
}

int main(){
    int V;
    int adjmat[100][100];
    cout<<"Enter the number of vertices : "<<endl;
    cin>>V;

    cout << "Enter adjacency matrix (use 0 if no edge, " << INT_MAX << " for infinity):\n";
    for(int i = 0; i < V; ++i)
        for(int j = 0; j < V; ++j)
            cin >> adjmat[i][j];
    
    kruskal(adjmat,V);
    return 0 ;
}


