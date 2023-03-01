
/*
    Max Flow - Ford Fulkerson Algorithm using DFS
	Time complexity : O(E*f) where f is the max flow
*/

#include<iostream>
#include<vector>
using namespace std;

long INF=999999;

int n=11;
int s=n-2;              // source
int t=n-1;              // terminate( sink )

int visitedToken=1;
vector<int> visited(n,0);
long max_Flow=0;

struct Edge{

public:
    int u;
    int v;
    long flow;
    long capacity;
    Edge *residual;

    Edge(int U,int V,long Capacity)
    {
        u=U;
        v=V;
        capacity=Capacity;
        flow=0;
    }

    bool isResidual(){
        return capacity==0;
    }

    long remCapacity(){
       return capacity-flow;
    }

    void augement(long bottleNeck)
    {
        flow+=bottleNeck;
        residual->flow-=bottleNeck;
    }
};

vector<vector<Edge *>> g(n);

void addEdge(int u,int v,long capacity)
{
   if(capacity<=0)
   {
       cout<<"Illegal capacity value , Fix it !!!"<<endl;
   }

   Edge *e1=new Edge(u,v,capacity);
   Edge *e2=new Edge(v,u,0);             // creating residual edge
   e1->residual=e2;
   e2->residual=e1;
   g[u].push_back(e1);
   g[v].push_back(e2);
}

void set_graph()
{
        // edges from source
    addEdge(s,0,10);
    addEdge(s,1,5);
    addEdge(s,2,10);

    // middle edges
    addEdge(0,3,10);
    addEdge(1,2,10);
    addEdge(2,5,15);
    addEdge(3,1,2);
    addEdge(3,6,15);
    addEdge(4,1,15);
    addEdge(4,3,3);
    addEdge(5,4,4);
    addEdge(5,8,10);
    addEdge(6,7,10);
    addEdge(7,4,10);
    addEdge(7,5,7);

    //edges to sink
    addEdge(6,t,15);
    addEdge(8,t,10);
}


void show_graph()
{

    cout<<"The Graph is Created as follows ( u,v,capacity,flow ) , please note 0-capacity represents a residual edge !!"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<i<<endl;
        for(auto e:g[i])
            cout<<e->u<<":"<<e->v<<":"<<e->capacity<<":"<<e->flow<<endl;
    }
}

long dfs(int u,long flow)
{
    if(u==t) return flow;           //base case of reaching the sink !

    visited[u]=visitedToken;

    for(auto edge:g[u])
    {
        if( visited[edge->v]!=visitedToken && edge->remCapacity()>0 )
        {
            long bottleNeck = dfs(edge->v,min(flow,edge->remCapacity()));

            if(bottleNeck>0)                                // ie we found a path which needs to be augment !
            {
                edge->augement(bottleNeck);
                return bottleNeck;
            }

        }
    }
    return 0;
}


long getMaxFlow()
{
    max_Flow=0;

    for(long f=dfs(s,INF);f!=0;f=dfs(s,INF))
    {
        visitedToken++;
        max_Flow+=f;
    }


    return max_Flow;
}


int main()
{
    set_graph();
    show_graph();
    cout<<endl<<"the max flow is :"<<getMaxFlow()<<endl
    ;
    return 0;
}

