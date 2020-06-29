/* C++ program to print DFS traversal from 
*a given vertex in a given graph */ 

#include<bits/stdc++.h> 
using namespace std; 
  
// Graph class represents a directed graph 
class Graph 
{ 
    int V;    //Number of vertices 
  
    //Pointer to an array containing 
    //adjacency lists 
    list<int> *adj; 
  
    //recursive function used by DFS 
    void DFSUtil(int v, bool visited[]); 
public: 
    Graph(int V);   //constructor 
  
    //add an edge to graph 
    void addEdge(int v, int w); 
  
    void DFS(int v); 
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); //add w to v’s list. 
} 
  
void Graph::DFSUtil(int v, bool visited[]) 
{ 
    //mark current node as visited and print it
    visited[v] = true; 
    cout << v << " "; 
  
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            DFSUtil(*i, visited); 
} 
  
//DFS traversal of the vertices reachable from v
void Graph::DFS(int v) 
{ 
    //mark all the vertices as unvisited
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    //call the recursive function to print DFS traversal 
    DFSUtil(v, visited); 
} 
  
//test code 
int main() 
{ 
    //creating a graph 
    Graph g(4); 
    g.addEdge(0, 1); 
    g.addEdge(0, 2); 
    g.addEdge(1, 2); 
    g.addEdge(2, 0); 
    g.addEdge(2, 3); 
    g.addEdge(3, 3); 
  
    cout << "Following is Depth First Traversal"
            " (starting from vertex 2) \n"; 
    g.DFS(2); 
  
    cout << endl;
  
    system("pause");
    cout << endl;
} 