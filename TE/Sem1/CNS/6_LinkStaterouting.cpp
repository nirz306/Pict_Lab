#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define INF INT_MAX

class Graph {
public:
    int V; 
    vector<vector<int>> adjMatrix;

    Graph(int V) {
        this->V = V;
        adjMatrix.resize(V, vector<int>(V, INF));

        for (int i = 0; i < V; i++) {
            adjMatrix[i][i] = 0;
        }
    }

    void addEdge(int u, int v, int distance) {
        adjMatrix[u][v] = distance;
        adjMatrix[v][u] = distance; // For undirected graph
    }

    int minDistance(vector<int>& dist, vector<bool>& visited) {
        int min = INF, min_index = -1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }
        return min_index;
    }

    void printPath(vector<int>& parent, int j) {
        if (parent[j] == -1)
            return;

        printPath(parent, parent[j]);
        cout << j << " ";
    }

    void dijkstra(int src) {
        vector<int> dist(V, INF);   
        vector<bool> visited(V, false); 
        vector<int> parent(V, -1); // To store the shortest path tree

        dist[src] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, visited); 

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (!visited[v] && adjMatrix[u][v] != INF && dist[u] != INF
                    && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    parent[v] = u; // Set u as the predecessor of v
                }
            }
        }

        // Display the results
        cout << "Node \t Distance from Source \t Path" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " \t\t " << dist[i] << " \t\t\t\t\t\t " << src << " ";
            printPath(parent, i);
            cout << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "Routers count? ";  cin >> V;

    Graph g(V);

    cout << "Links count? "; cin >> E;

    cout << "Enter links(start end distance):\n";
    for (int i = 0; i < E; i++) {
        int u, v, distance;
        cin >> u >> v >> distance;
        g.addEdge(u, v, distance);
    }

    int source;
    cout << "Source router?- ";
    cin >> source;

    g.dijkstra(source);

    return 0;
}
