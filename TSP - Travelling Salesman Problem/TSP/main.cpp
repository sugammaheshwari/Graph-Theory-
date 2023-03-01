
#include<iostream>
#include<vector>
#include<math.h>
#include<limits.h>
using ll=long long;
using namespace std;

vector<vector<ll>> M={ { 0, 10, 15, 20 },                   // adjacency list of the graph for TSP
                       { 10, 0, 35, 25 },
                       { 15, 35, 0, 30 },
                       { 20, 25, 30, 0 } };
vector<int> combs;

int N=M.size();                                              // stores no of nodes of the graph of the given problem
vector<vector<ll>> dp(N,vector<ll>(pow(2,N),LONG_MAX));

int start=0;

void combi(int r,int n,int a)
{
    if(r==0) combs.push_back(a);
    if(n==0) return;

    a<<=1;
    combi(r,n-1,a);

    if(r>0)
    {
        a+=1;
        combi(r-1,n-1,a);
    }
}

void combination(int r,int n)
{
    combs.clear();

    int ans=1;
    combi(r-1,n-1,ans);
}


void setup()
{
    for(int i=0;i<N;i++)
    {
        if(i==start) continue;
        dp[i][ 1<<start | 1<<i ] = M[start][i];
    }
}

bool notIn(int i,int subset)
{
    return ( (1<<i) & subset ) == 0;
}


void solve()
{
    for(int r=3;r<=N;r++)
    {
        combination(r,N);
        for(auto subset:combs)
        {
            if(notIn(start,subset)) continue;

            for(int next=0;next<N;next++)
            {
                if(next==start || notIn(next,subset)) continue;

                int state = subset ^ (1<<next);                              // subset state without next node
                ll minDist=LONG_MAX;

                for(int e=0;e<N;e++)
                {
                    if(e==start || e==next || notIn(e,subset)) continue;
                    ll new_dis=dp[e][state] + M[e][next];
                    if(new_dis<minDist)
                        minDist=new_dis;
                }
                dp[next][subset]=minDist;
            }
        }
    }
}

ll TSP_minCost()
{
    int end_state=(1<<N)-1;

    ll minTourCost=LONG_MAX;


    for(int e=0;e<N;e++)
    {
        if(e==start) continue;
        ll tourCost=dp[e][end_state]+M[e][start];
        if(tourCost<minTourCost)
            minTourCost=tourCost;
    }

    return minTourCost;
}

vector<int> findOptimalTour()
{
    int lastIndex=start;
    int state=(1<<N)-1;     // end state
    vector<int> tour(N+1);

    for(int i=N-1;i>=1;i--)
    {
        int index=-1;
        for(int j=0;j<N;j++)
        {
            if(j==start ||notIn(j,state)) continue;
            if(index==-1) index=j;
            ll minDist=dp[index][state] + M[index][lastIndex];
            ll newDist=dp[j][state] + M[j][lastIndex];
            if(newDist<minDist)
                index=j;
        }
        lastIndex=index;
        tour[i]=index;
        state^=(1<<index);
    }
    tour[0]=tour[N]=start;
    return tour;
}



int main()
{

    int start=0;
    setup();
    solve();

    cout<<"the minimum cost is :"<<TSP_minCost()<<endl;

    cout<<"the optimal tour is as follows :"<<endl;
    vector<int> tourPath=findOptimalTour();

    for(auto p:tourPath)
        cout<<p<<":";
    cout<<endl;

}
