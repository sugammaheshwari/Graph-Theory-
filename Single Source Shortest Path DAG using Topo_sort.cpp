
/*

    To find SSSP single source shortest path distance in a weighted (can be negetive) directed acyclic graph
    using TOPOLOGICAL SORT algorithm !!!
	

	SSSP - Single source shortest path algorithm 
	*Dijkstra's algorithm may fail when the edge weight are negative , because it may cause negative endless cycles.

	1 . Using Topological Sort (can be solved efficiently on DAG in O(V+E) time complexity)
		ALGORITHM 
		- Take Topological order of the vertices of the graph and then start updating the distance vector by going in the topological order itself.
		- After reaching the end of topological order you will get the SSSP result 
		- Its different from Dijkstra's because in Dijkstra's we directly did insertion of edge in priority queue and did the usual Dijkstra's algorithm thing.
	
	2.Longest Path on DAG problem 
		- On a general graph this problem is NP hard.
		- But for DAG its solvable in O(V+E). 
TRICK -> Same process to be followed as SSSP , just multiply the  edge weights by -1 then find SSSP and then multiply back the result with -1 to get Long Path in DAG solution !
	

*/


#include <iostream>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> edges;
int n=6;
vector<vector<pair<int,int>>> g(n);

int start=1;

vector<int> khans_Algo()                    // khan's algo to find topological sort
{
    vector<int> topo,indegree(n,0);

    for(auto e:edges)
    {
        indegree[e[1]]++;
    }

    queue<int> q;

    for(auto i=0;i<indegree.size();i++)
        if(indegree[i]==0)
            q.push(i);

    while(!q.empty())
    {
        int curr=q.front();q.pop();
        topo.push_back(curr);
        for(auto v:g[curr])
        {
            if(--indegree[v.first]==0)
                q.push(v.first);
        }
    }
    return topo;
}

void addEdge(int u,int v,int w)
{
    edges.push_back({u,v});
    g[u].push_back({v,w});
}


vector<int> dist(int start)
{
    vector<int> topo=khans_Algo();
    vector<int> distance(n,999999);
    distance[start]=0;

    for(int i=0;i<n;i++)
    {
        for(auto v:g[topo[i]])
        {
            if(distance[topo[i]]+v.second<distance[v.first])
                distance[v.first]=distance[topo[i]]+v.second;
        }
    }

    return distance;
}


int main()
{
    g.resize(n);

    addEdge(0, 1, 5);
    addEdge(0, 2, 3);
    addEdge(1, 3, 6);
    addEdge(1, 2, 2);
    addEdge(2, 4, 4);
    addEdge(2, 5, 2);
    addEdge(2, 3, 7);
    addEdge(3, 4, -1);
    addEdge(4, 5, -2);

    vector<int> dis=dist(start);

    for(auto x:dis)
        cout<<x<<":";

    return 0;
}
