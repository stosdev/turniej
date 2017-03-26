#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>

#define INF 1000000000

using namespace std;

class Zadanie{
public:
    int t1;
    int t2;
    int p;
};
int n, k;
Zadanie zadania[10000];
class Krawedz{
public:
    int c;
    int cc;
    int cost;
    int f;
    int doo;
    int indOd;
    Krawedz(int _c, int _cost, int _f, int _doo, int in):c(_c), cc(_cost), cost(_cost), f(_f), doo(_doo), indOd(in){}
};
vector<Krawedz> listy[4002];
int odl[4002];
bool przet[4002];
int pop[4002];
Krawedz* popK[4002];
int pot[5000];
int nDij;
int dijkstra(int pocz, int kon){
    for(int i=0;i<=nDij;i++){
        odl[i]=INF;
        przet[i]=false;
        pop[i]=-1;
        popK[i]=NULL;
    }
    odl[pocz]=0;
    priority_queue<pair<int, int>, std::vector< pair<int, int> >, std::greater<pair<int, int> > > q;
    q.push(make_pair(odl[pocz], pocz));
    while(!q.empty()){
        pair<int, int> t=q.top();
        q.pop();
        int d=t.first;
        int v=t.second;
        if(przet[v])
            continue;
        przet[v]=true;
        for(int x=0;x<listy[v].size();x++){
            if(listy[v].at(x).f<listy[v][x].c){
            int s=listy[v].at(x).doo;
            int w=listy[v].at(x).cost;
                if(d+w<odl[s]){
                    odl[s]=d+w;
                    pop[s]=v;
                    popK[s]=&(listy[v][x]);
                    q.push(make_pair(odl[s], s));
                }
            }
        }
    }
    return odl[kon];
}
int ford_bellman(int pocz, int kon){
    for(int i=0;i<=nDij;i++){
        odl[i]=INF;
        pop[i]=-1;
        popK[i]=NULL;
    }
    odl[pocz]=0;
    for(int powt=1;powt<=nDij;powt++){
        bool poprawa=false;
        for(int v=0;v<=nDij;v++){
            if(odl[v]==INF)
                continue;
            for(int x=0;x<listy[v].size();x++){
                if(listy[v].at(x).f<listy[v][x].c){
                    int s=listy[v].at(x).doo;
                    int w=listy[v].at(x).cost;
                    if(odl[v]+w<odl[s]){
                        odl[s]=odl[v]+w;
                        pop[s]=v;
                        popK[s]=&(listy[v][x]);
                        poprawa=true;
                    }
                }
            }
        }
        if(!poprawa)
            break;
    }
    return odl[kon];
}
int max_t=0;
bool odw[5000];
int min_cost_flow(){
    int nr=0;
    for(int i=1;i<max_t;i++){
        listy[i].push_back(Krawedz(k, 0, 0, i+1, listy[i+1].size()));
        listy[i+1].push_back(Krawedz(0, 0, 0, i, listy[i].size()-1));
    }
    int wejscia[4002];
    for(int i=1;i<=max_t;i++)
        wejscia[i]=0;
    nDij=max_t+n+1;
    for(int i=1;i<=n;i++){
        int v1=zadania[i].t1, v2=zadania[i].t2;
        wejscia[v2]++;
        listy[i+max_t].push_back(Krawedz(INF, -zadania[i].p, 0, v1, listy[v1].size()));
        listy[v1].push_back(Krawedz(0, zadania[i].p, 0, i+max_t, listy[i+max_t].size()-1));
        listy[i+max_t].push_back(Krawedz(INF, 0, 0, v2, listy[v2].size()));
        listy[v2].push_back(Krawedz(0, 0, 0, i+max_t, listy[i+max_t].size()-1));
        listy[0].push_back(Krawedz(1, 0, 0, i+max_t, listy[i+max_t].size()));
        listy[i+max_t].push_back(Krawedz(0, 0, 0, 0, listy[0].size()-1));
    }
    for(int i=1;i<=max_t;i++){
        if(wejscia[i]>0){
            listy[i].push_back(Krawedz(wejscia[i], 0, 0, nDij, listy[nDij].size()));
            listy[nDij].push_back(Krawedz(0, 0, 0, i, listy[i].size()-1));
        }
    }
    int flow=n;
    int cost=0;
    int przeplyw=0;
    int it=0;
    ford_bellman(0, nDij);
    while(przeplyw<flow){
        for(int v=0;v<=nDij;v++)
            pot[v]+=odl[v];
        for(int v=0;v<=nDij;v++){
            for(int x=0;x<listy[v].size();x++){
                listy[v][x].cost=listy[v][x].cc+pot[v]-pot[listy[v][x].doo];
            }
        }
        int wyn=dijkstra(0, nDij);
        int minF=INF;
        int v=nDij;
        while(true){
            int vPop=pop[v];
            Krawedz* k=popK[v];
            if(k->c-k->f<minF)
                minF=k->c-k->f;
            if(vPop==0)
                break;
            v=vPop;
        }
        v=nDij;
        przeplyw+=minF;
        while(true){
            int vPop=pop[v];
            Krawedz* k=popK[v];
            k->f+=minF;
            cost+=(minF*k->cost);
            listy[v][k->indOd].f-=minF;
            if(vPop==0)
                break;
            v=vPop;
        }
    }
    int cost2=0;
    for(int v=0;v<=nDij;v++){
            for(int x=0;x<listy[v].size();x++){
                if(listy[v][x].c>0 && listy[v][x].f>0){
                    cost2+=listy[v][x].f*listy[v][x].cc;
                }

            }
        }
        return -cost2;
}
void test(){
    scanf("%d%d", &n, &k);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d", &zadania[i].t1, &zadania[i].t2, &zadania[i].p);
        max_t=max(max_t, zadania[i].t2);
    }
    printf("%d\n", min_cost_flow());
}
int main() {
    test();
    return 0;
}
