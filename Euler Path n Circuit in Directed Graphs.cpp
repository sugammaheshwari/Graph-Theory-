
// TO find Euler path in a directed Graph !
// Time complexity of finding Euler path is O(v+E) ie its done in linear time complexity !

// if you feed this algorithm with a graph which has Eulerian Circuit then the outcome will be Eularian Circuit
// ie Eularian Circuit comes for free !!!!

#include<iostream>
#include<vector>
using namespace std;

int n=5,edge_count=0;
vector<vector<int>> g(n);
vector<int> indegree(n,0),outdegree(n,0),path;

void count_in_out_Degree()
{
    for(int i=0;i<n;i++)
        for(auto v:g[i])
        {
            indegree[v]++;
            outdegree[i]++;
            edge_count++;
        }
}

bool hasEularianPath()
{
    int start_nodes=0,end_nodes=0;
    for(int i=0;i<n;i++)
    {
        if(outdegree[i]-indegree[i]>1 || indegree[i]-outdegree[i]>1) return false;
        else if(indegree[i]-outdegree[i]==1) end_nodes++;
        else if(outdegree[i]-indegree[i]==1) start_nodes++;
    }

    return ( (start_nodes==1 && end_nodes==1) || (start_nodes==0 && end_nodes==0) );
}

int find_Start_node()
{
    int start=0;

    for(int i=0;i<n;i++)
    {
        if(outdegree[i]-indegree[i]==1) return i;       // if you directly find a start node , just return it !
        if(outdegree[i]>0) start=i;                  // this statement helps to avoid starting DFS at a singleton ( a node which doesnt have an outward edge !!)
    }

    return start;
}


void dfs(int u)
{
    while(outdegree[u]!=0)
        dfs(g[u][--outdegree[u]]);

    path.push_back(u);
}

int main()
{
g[1].push_back(0);
g[0].push_back(2);
g[2].push_back(1);
g[0].push_back(3);
g[3].push_back(4);
g[4].push_back(0);

//    g[0].push_back(1);
//  g[1].push_back(0);
//  g[0].push_back(2);
//    g[2].push_back(0);                                  // this edge makes the graph a Eularian circuit , Un-comment to find Eularian Circuit for the Graph !

    count_in_out_Degree();
    if(edge_count==0)
    {
        cout<<"\n no edges present in graph returning";
        return 0;
    }
    else if(!hasEularianPath())
    {
        cout<<"\n the graph doesn't have eulerian path, returning";
        return 0;
    }

    dfs(find_Start_node());

    if(path.size()!=edge_count+1){                          // need to check because there might be a case where more than one connected components exisits ie the graph may be disconnected !
        cout<<"Euler path doesn't exists!"<<endl;
        return 0;
    }

    cout<<"the Euler path is :"<<endl;

    int l=path.size();

    for(int k=l-1;k>=0;k--)
        cout<<path[k]<<"->";
    cout<<endl;

    return 0;
}
