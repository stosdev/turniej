#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
int n;
int wymiary[100];
unsigned long long tab_hash[5000000];
int podstawa;
unsigned long long sposoby(){
    int maks=0;
    int maxW;
    int hash=0;
    for(int w=n-1;w>=0;w--){
        if(wymiary[w]>maks){
            maks=wymiary[w];
            maxW=w;
        }
        hash*=podstawa;
        hash+=wymiary[w];
    }
    if(maks==0)
        return 1;
    if(tab_hash[hash]!=0)
        return tab_hash[hash];
    int ile=1, tmpW=maxW-1;
    while(tmpW>=0 && wymiary[tmpW]==maks){
        ile++;
        tmpW--;
    }
    unsigned long long wynik=0;
    for(int x=1;x<=ile;x++){
        for(int y=1;y<=maks;y++){
            for(int z=0;z<x;z++)
                wymiary[maxW-z]--;
            wynik+=sposoby();
        }
        for(int z=0;z<x;z++)
            wymiary[maxW-z]+=maks;
    }
    tab_hash[hash]=wynik;
    return (tab_hash[hash]);
}
void test(){
    n=0;
    podstawa=0;
    for(int i=0;i<100;i++)
        wymiary[i]=0;
    tab_hash[0]=1;
    char kod[100];
    scanf("%s", kod);
    int len=strlen(kod);
    int przes=0;
    for(int i=0;i<len;i+=2){
        char kier=kod[i];
        int ile=kod[i+1]-'0';
        if(kier=='P')
            przes+=ile;
        else if(kier=='L')
            przes-=ile;
        else if(kier=='D'){
            if(przes>podstawa)
                podstawa=przes;
            while(ile--)
                wymiary[n++]=przes;
        }
    }
    podstawa++;
    printf("%llu\n", sposoby());
}
int main() {
    test();
    return 0;
}
