/*
    TO find articulation point in an undirected graph !
*/

#include<iostream>
#include<vector>
using namespace std;

int n=8;
vector<vector<int>> g(n);

int id=0,articulation_count=0,root_child_count=0;
vector<int> ids(n,-1),low(n-1),is_articulation(n,false);

void dfs(int root,int u,int parent)
{
    ids[u]=low[u]=id++;
    if(parent==root) root_child_count++;

    for(auto v:g[u])
    {
        if(v==parent) continue;
        if(ids[v]==-1)
        {
            dfs(root,v,u);
            low[u]=min(low[u],low[v]);

            if(ids[u]<=low[v])
                is_articulation[u]=true;
        }
        else
            low[u]=min(low[u],ids[v]);
    }
}


int find_articulation_points()
{
    for(int i=0;i<n;i++)
        if(ids[i]==-1)
        {
            root_child_count=0;
            dfs(i,i,-1);
            if(root_child_count>1)
                is_articulation[i]=true;
            else
                is_articulation[i]=false;
        }

    for(auto b:is_articulation)
        if(b)
            articulation_count++;

    return articulation_count;
}

void addedge(int u,int v)
{
    g[u].push_back(v);
    g[v].push_back(u);

}

int main()
{
    addedge(0,1);
    addedge(0,2);
    addedge(2,1);
    addedge(1,6);
    addedge(1,4);
    addedge(1,3);
    addedge(3,5);
    addedge(4,5);
    addedge(0,7);

    cout<<"ans:"<<find_articulation_points()<<endl;;

    for(auto x:is_articulation)
        cout<<x<<":";

}
