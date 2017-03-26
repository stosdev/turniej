#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

int n, m, l;
char matryca[200][200][200];
char wzorce[1000][20][20][20];
bool jest[1001];
int p1=3, p2=5000011;

int odcinki[200][200][200];
int kwadraty[200][200][200];

long long potegiModulo[10000];
vector<int>* hashtable[5100000];
void sprawdz(long long sum, int i, int j, int k){
    if(hashtable[sum]!=NULL){
        for(int ind=0;ind<hashtable[sum]->size();ind++){
            int w=hashtable[sum]->at(ind);
            bool ok=true;
            for(int x=0;x<m;x++){
                 for(int y=0;y<m;y++){
                       for(int z=0;z<m;z++){
                             if(matryca[i+x][j+y][k+z]!=wzorce[w][x][y][z]){
                                  ok=false;
                                  goto koniec_petli;
                             }
                       }
                 }
           }
           koniec_petli:
           if(ok){
                 jest[w]=true;
                 hashtable[sum]->erase(hashtable[sum]->begin()+ind);
                 return;
           }
        }
    }
}
void RabinKarp(){
    potegiModulo[0]=1;
    for(int i=1;i<m*m*m;i++){
        potegiModulo[i]=(potegiModulo[i-1]*p1)%p2;
    }
    for(int w=0;w<l;w++){
        int sum=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<m;j++){
                for(int k=0;k<m;k++){
                    sum*=p1;
                    sum+=wzorce[w][i][j][k];
                    sum%=p2;
                }
            }
        }
        if(hashtable[sum]==NULL)
            hashtable[sum]=new vector<int>();
        hashtable[sum]->push_back(w);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            long long sum=0;
            for(int x=0;x<m;x++){
                sum*=p1;
                sum+=matryca[i][j][x];
                sum%=p2;
            }
            odcinki[i][j][0]=sum;

            for(int k=1;k<=n-m;k++){
                sum=sum-(potegiModulo[m-1]*matryca[i][j][k-1])%p2;
                if(sum<0)
                    sum+=p2;
                sum=((sum*p1)+matryca[i][j][k+m-1])%p2;
                odcinki[i][j][k]=sum;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int k=0;k<=n-m;k++){
            long long sum=0;
            for(int x=0;x<m;x++){
                sum*=potegiModulo[m];
                sum+=odcinki[i][x][k];
                sum%=p2;
            }
            kwadraty[i][0][k]=sum;
            for(int j=1;j<=n-m;j++){
                sum=sum-(potegiModulo[m*(m-1)]*odcinki[i][j-1][k])%p2;
                if(sum<0)
                    sum+=p2;
                sum=((sum*potegiModulo[m])+odcinki[i][j+m-1][k])%p2;
                kwadraty[i][j][k]=sum;
            }
        }
    }
    for(int j=0;j<=n-m;j++){
        for(int k=0;k<=n-m;k++){
            long long sum=0;
            for(int x=0;x<m;x++){
                sum*=potegiModulo[m*m];
                sum+=kwadraty[x][j][k];
                sum%=p2;
            }
            sprawdz(sum, 0, j, k);
            for(int i=1;i<=n-m;i++){
                sum=sum-(potegiModulo[m*m*(m-1)]*kwadraty[i-1][j][k])%p2;
                if(sum<0)
                    sum+=p2;
                sum=((sum*potegiModulo[m*m])+kwadraty[i+m-1][j][k])%p2;
                sprawdz(sum, i, j, k);
            }
        }
    }
}
void test(){
    scanf("%d%d%d", &n, &m, &l);
    char wiersz[300];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%s" , wiersz);
            for(int w=0;w<n;w++)
                matryca[i][j][w]=wiersz[w]-'0';
        }
    }
    for(int x=0;x<l;x++){
        for(int i=0;i<m;i++){
            for(int j=0;j<m;j++){
                scanf("%s" , wiersz);
                for(int w=0;w<m;w++)
                    wzorce[x][i][j][w]=wiersz[w]-'0';
            }
        }
    }
    RabinKarp();
    for(int i=0;i<l;i++)
        printf("%d", jest[i]);
}
int main() {
    test();
    return 0;
}
