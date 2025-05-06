#include<bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int n ;
    vector<vector<int>> adjList;
    
    public:
    Graph(int n):n(n),adjList(n){}

    void buildGraph();
    void bfs();
    void dfs_recurssive();
    void dfs_iterative();
    void dfs_helper(int node, vector<bool>&vis);


};

void Graph::buildGraph(){
    cout<<"press -1 to exit "<<endl;
    while(true){
        int startNode, endNode;
        cout<<"Enter the start node: "; cin>>startNode;
        cout<<"Enter the end node: "; cin>>endNode;

        if(startNode==-1 || endNode==-1) break;
        else{
            if(startNode>=0 && startNode<n && endNode>=0 && endNode<n){
                adjList[startNode].push_back(endNode);
                adjList[endNode].push_back(startNode);
            }
            else{
                cout<<"Enter valid inputs!!!"<<endl;
            }
        }
    }
}

void Graph::bfs(){
    vector<bool> vis(n, false);
    queue<int> que;
    que.push(0);
    vis[0] = true; // mark as visited when pushing into the queue

    while(!que.empty()){
        int levelSize = que.size();  // number of nodes at current level
        
        // Print all nodes at this level
        for(int i = 0; i < levelSize; i++){
            int node = que.front();
            que.pop();
            cout << node << " ";

            for(int neighbor : adjList[node]){
                if(!vis[neighbor]){
                    vis[neighbor] = true;  // mark as visited when enqueued
                    que.push(neighbor);
                }
            }
        }

        cout << endl; // move to the next line after each level
    }
}

void Graph::dfs_helper(int node, vector<bool>&vis){
    cout<<node<<" ";
    vis[node] = true;
    //recurssive calls
    for(int i=0;i<adjList[node].size();i++){ 
        int num = adjList[node][i];
        if(!vis[num]){
           dfs_helper(num,vis);
        }
    }
}

void Graph::dfs_recurssive(){
    //declare a visited array 
    vector<bool>vis(n,false);
    dfs_helper(0,vis);
}

void Graph::dfs_iterative(){
    //using stack 
    vector<bool>visited(n,false);
    stack<int>st;
    st.push(0);
    visited[0]=true;

    while(!st.empty()){
        int node = st.top();
        st.pop();
        cout<<node<<" ";
        //if not visited then push in stack 
        for(int i=adjList[node].size()-1;i>=0;i--){ 
            int num = adjList[node][i];
            if(!visited[num]){
                visited[num]=true;
                st.push(num);
            }
        }
    }
}

int main(){
    int n =6;
    Graph G(n);
    G.buildGraph();
    cout<<"BFS traversal: "<<endl;
    G.bfs();
    cout<<"Recurssive DFS: "<<endl;
    G.dfs_recurssive();
    cout<<"\nIterative DFS: "<<endl;
    G.dfs_iterative();

}
