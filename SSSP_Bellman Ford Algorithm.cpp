
/*

   SSSP - Bellman Ford Algorithm
   - slower than dijktras
   - Time complexity O(VE)
   - Simpler algorithm
   - Works on -ve weighted graph with -ve cycles too !!!!  ->  that's the main advantage !!!

   	   ALGORITHM
			1. Set every entry in Distance vector to +INF
			2. Set d[Start]=0;
			3. Relax each edge V-1 times , where V is the total number of vertices in the graph.
		*NOTE - Here order of edges doesn’t matter since we are relaxing the vertices V-1 times , the final result will be correct.


    ** TO find the nodes caught in negetive cycles
        simply rerun the algorithm with the changed condition as follows :-

        for(int i=0;i<n-1;i++)
        {
            for(auto e:edges)
            {
                if(distance[e[0]]+e[2]<distance[e[1]])                   /
                    distance[e[1]]=-99999                           // settting to -INF
            }
        }

*/


#include <iostream>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> edges;
int n=6;                                    // no of vertices of the graph
int start=0;

vector<int> dist(int start)
{
    vector<int> distance(n,999999);
    distance[start]=0;

    for(int i=0;i<n-1;i++)                      // bellman ford algorithm runs for V-1 ( no of vertices-1) times !!
    {
        for(auto e:edges)
        {
            if(distance[e[0]]+e[2]<distance[e[1]])                   // edge relaxation step !
                distance[e[1]]=distance[e[0]]+e[2];
        }
    }

    return distance;
}


vector<int> find_negetive_cycle_nodes(vector<int> distance)
{

    for(int i=0;i<n-1;i++)
    {
        for(auto e:edges)
        {
            if(distance[e[0]]+e[2]<distance[e[1]])
                distance[e[1]]=-99999  ;                         // settting to -INF
        }
    }

    return distance;
}


void addEdge(int u,int v,int w)
{
    edges.push_back({u,v,w});
}

int main()
{
    edges={ { 0, 1, -1 }, { 0, 2, 4 },
                       { 1, 2, 3 }, { 1, 3, 2 },
                       { 1, 4, 2 }, { 3, 2, 5 },
                       { 3, 1, 1 }, { 4, 3, -5 } , {0,5,10} };


    vector<int> dis=dist(start);

    for(auto d:dis)
        cout<<d<<":";
    cout<<endl;


    cout<<"finding the nodes caught in -ve cycle and setting their distance to -99999"<<endl;

    vector<int> d2=find_negetive_cycle_nodes(dis);

    for(auto d:d2)
        cout<<d<<":";

    return 0;
}
