#include<bits/stdc++.h>
using namespace std;

vector<int> shortestPath(vector<vector<pair<int,int>>> adjList,int n){
    priority_queue<pair<int,int>, vector<pair<int,int>>,greater<pair<int,int>> >pq;
    vector<int> dist_arr(n,INT_MAX);
    dist_arr[0] = 0;
    pq.push({0,0});

    while(!pq.empty()){
        pair<int,int>top = pq.top();
        pq.pop();
        int dist = top.first;
        int node = top.second;

        //check in adj list now 
        for(int i=0;i<adjList[node].size();i++){
            int adj_node = adjList[node][i].first;
            int dist_adj_node = adjList[node][i].second;

            //check if we can insert in the dist[]
            if(dist + dist_adj_node < dist_arr[adj_node]){
                dist_arr[adj_node] = dist + dist_adj_node;
                pq.push({dist_arr[adj_node], adj_node});
            }
        }
    }
    return dist_arr;
}


int main(){
    int n,m;
    cout<<"Enter the number of vertices: "; cin>>n ;
    cout<<"Enter the number of edges: "; cin>>m;
    
    vector<vector<pair<int,int>>> adjList(n);
    for(int i=0; i<m;i++){
        int startNode, endNode, dist;
        cout<<"Enter the start node: "; cin>>startNode;
        cout<<"Enter the end node: "; cin>>endNode;
        cout<<"Enter the distance between both: "; cin>>dist;
        adjList[startNode].push_back({endNode,dist});
    }
    vector<int> ans = shortestPath(adjList,n);

    for(int i=0;i<n;i++){
        cout<<i<<":"<<ans[i]<<endl;
    }
}
