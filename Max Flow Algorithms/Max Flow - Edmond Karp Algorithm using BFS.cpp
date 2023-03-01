
/*
    Max Flow - Edmonds Karp Algorithm
    Based on BFS
    Time complexity : O(E*V^2)
*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

long INF=999999;

int n=11;
int s=n-2;              // source
int t=n-1;              // terminate( sink )

int visitedToken=1;
vector<int> visited(n,0);

struct Edge{

    int u;
    int v;
    long capacity;
    long flow;
    Edge *residual;

    Edge(int u,int v,long capacity)
    {
        this->capacity=capacity;
        this->u=u;
        this->v=v;
        this->flow=0;
    }

    void augment(long bottleNeck)
    {
        flow+=bottleNeck;
        residual->flow-=bottleNeck;
    }

    long getCapacity(){
        return capacity-flow;
    }

};

vector<vector<Edge *>> g(n);
long max_Flow=0;


void addEdge(int u,int v,long capacity)
{
    Edge *e1=new Edge(u,v,capacity);
    Edge *e2=new Edge(v,u,0);                   // residual edge creation

    e1->residual=e2;
    e2->residual=e1;
    g[u].push_back(e1);
    g[v].push_back(e2);
}

void set_graph()
{
    //  addEdge(0,1,15);
    //  addEdge(1,2,10);
     // addEdge(0,3,15);
     // addEdge(3,4,15);
     // addEdge(2,5,10);
     // addEdge(4,5,15);

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

    //edges to sink/
    addEdge(6,t,15);
    addEdge(8,t,10);

}

void Edmonds_Karp_Algo()
{
    while(1)
    {
        Edge *e=new Edge(-1,s,INF);
        queue<Edge *> q;
        q.push(e);
        vector<Edge*> prev(n,NULL);

        while(!q.empty())
        {
            Edge *e=q.front();q.pop();
            if(e->v==t) {prev[t]=e;break;}
            if(visited[e->v]==visitedToken) continue;
            visited[e->v]=visitedToken;

            for(auto x:g[e->v])
                if(visited[x->v]!=visitedToken && x->getCapacity()>0)
                {
                    q.push(x);
                    prev[e->v]=e;
                }
        }

        if(prev[t]==NULL) break;

        long bottleneck=INF;int x=t;
        while(x!=s)
        {
            bottleneck=min(bottleneck,prev[x]->getCapacity());
            x=prev[x]->u;
        }

        x=t;
        while(x!=s)
        {
            prev[x]->augment(bottleneck);
            x=prev[x]->u;
        }

        cout<<"Augment Path #:"<<visitedToken<<"  + Max Flow -> "<<bottleneck<<endl;
        max_Flow+=bottleneck;visitedToken++;
    }

    cout<<endl<<"The total max flow is "<<max_Flow<<endl;
}


void show_graph()
{
    cout<<"The graph is :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"node i"<<endl;
        for(auto e:g[i])
            cout<<e->u<<":"<<e->v<<":"<<e->capacity<<":"<<e->flow<<endl;
    }
}


int main()
{
    set_graph();
    Edmonds_Karp_Algo();
    return 0;
}

