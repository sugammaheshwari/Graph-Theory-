/*
  TO find Bridges in a graph ( Undirected Graph )
*/

#include<iostream>
#include<vector>
using namespace std;

int n=7;
vector<vector<int>> g(n);

int id=0,bridges=0;
vector<int> ids(n,-1),low(n-1);

void dfs(int u,int parent)
{
    ids[u]=low[u]=id++;

    for(auto v:g[u])
    {
        if(v==parent) continue;

        if(ids[v]==-1)
        {
            dfs(v,u);                           // discover the undiscovered node first using DFS
            low[u]=min(low[u],low[v]);          // update the low link value of current node 'u' using the newly calculated low link value of the connected vertices while backtracking !

            if(ids[u]<low[v])                 // condition to check if the current edge form u->v is a bridge
            {
                cout<<u<<"->"<<v<<endl;
                bridges++;
            }
        }
        else
            low[u]=min(low[u],ids[v]);              // reached the point of start thus we take min with ids[v]
            /*
                    i stuggled a lot here why cant we take  low[u]=min(low[u],low[v])  why is this not valid   , searched a lot on youtube
                    some say because we cant take more than one back edge (Techdose ) etc etc
                    Still not clear so  i
                        so i test the same on question : 1192. Critical Connections in a Network (LEETCODE) and it passed
                    so i guess we could use low[v] , till i don't understand this part !!! or find a test case which counters this !!!!
            */


    }
}


int find_bridges()
{
    for(int i=0;i<n;i++)
        if(ids[i]==-1)
            dfs(i,-1);

    return bridges;
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

    cout<<"ans:"<<find_bridges();
}
