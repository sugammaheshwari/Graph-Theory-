
/*
    Tarjan's Algo to find the no of strongly connected components in a directed graph !

*/

#include<stack>
#include<iostream>
#include<vector>
using namespace std;

int n=8;
vector<vector<int>> g(n);

int id=0;

vector<int> ids(n,-1);              // -1 representing unvisited/unassigned id's initially
stack<int> st;
vector<bool> onStack(n,false);
vector<int> low(n,-1);                  // initiallised low link values with -1

int count_SCC=0;

void addEdge(int u,int v)
{
    g[u].push_back(v);
}

void dfs(int u)
{
    ids[u]=low[u]=id++;
    st.push(u);
    onStack[u]=true;

    for(auto v:g[u])
    {
        if(ids[v]==-1) dfs(v);                     // if unvisited simply make the DFS call
        if(onStack[v]) low[u]=min(low[u],low[v]);        // update the low[u] will backtracking
    }

    if(ids[u]==low[u])                  // Ie: Starting node of current strongly connected component is found
    {
        int top=st.top();
        while(top!=u)
        {
            st.pop();
            onStack[top]=false;
            low[top]=ids[u];
            cout<<top<<",";
            top=st.top();
        }
        cout<<top<<endl;onStack[top]=false;
        st.pop();
        count_SCC++;
    }
}


int Tarjans_Algo()                  // algo to find SCC in a directed graph !
{
    for(int i=0;i<n;i++)
        if(ids[i]==-1)
            dfs(i);

    return count_SCC;
}


int main()
{
    addEdge(0,1);
    addEdge(1,2);
    addEdge(2,0);
    addEdge(3,4);
    addEdge(3,7);
    addEdge(4,5);;
    addEdge(5,0);
    addEdge(5,6);
    addEdge(6,0);addEdge(6,2);addEdge(6,4);
    addEdge(7,3);addEdge(7,5);

    cout<<"The no of SCC are:"<<Tarjans_Algo()<<endl;

}
