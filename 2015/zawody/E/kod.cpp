#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <set>
#include <queue>
#include <time.h>
#include <algorithm>
#include <stack>

#define INF 1000000000
using namespace std;

class Krawedz {
public:
    int sasiad;
    int waga;
    int oplata;
};

int V, K, O;
int odleglosci2D[3005][3001];
bool przetworzony2D[3005][3001];
vector<Krawedz> listy[3005];

int odleglosci[3001];
bool przetworzony[3001];
int koszta[3001];

void init2D() {
    for (int i = 1; i <= V; i++) {
        listy[i].erase(listy[i].begin(), listy[i].end());
        for (int j = 0; j <= O; j++) {
            odleglosci2D[i][j] = INF;
            przetworzony2D[i][j] = false;
        }
    }
}

int ileOp = 0;
int ileIt = 0;

class Comp {
public:
    bool operator()(pair<int, pair<int, int> > &t, pair<int, pair<int, int> > &r) {
        if (t.first > r.first)
            return true;
        if (t.first < r.first)
            return false;
        if (t.second.first > r.second.first)
            return true;
        if (t.second.first < r.second.first)
            return false;
        if (t.second.second > r.second.second)
            return true;
        return false;
    }
};

class Comp2 {
public:
    bool operator()(pair<int, int> &t, pair<int, int> &r) {
        if (odleglosci[t.first] > odleglosci[r.first])
            return true;
        if (odleglosci[t.first] < odleglosci[r.first])
            return false;

        if (koszta[t.first] > koszta[r.first])
            return true;
        if (koszta[t.first] < koszta[r.first])
            return false;
        if (t.first > r.first)
            return true;
        if (t.first < r.first)
            return false;
    }
};

void optymalny2(int pocz) {
    odleglosci2D[pocz][0] = 0;
    int najkrotsza[3001];
    for (int v = 1; v <= V; v++)
        najkrotsza[v] = INF;
    for (int pien = 0; pien <= O; pien++) {
        for (int wierz = 1; wierz <= V; wierz++) {
            if (odleglosci2D[wierz][pien] == INF)
                continue;
            if (najkrotsza[wierz] <= odleglosci2D[wierz][pien])
                continue;
            else
                najkrotsza[wierz] = odleglosci2D[wierz][pien];
            int rozm = listy[wierz].size();
            for (int it = 0; it < rozm; it++) {
                Krawedz kr = listy[wierz][it];
                int pienNowy = pien + kr.oplata;
                if (pienNowy <= O) if (odleglosci2D[wierz][pien] + kr.waga < odleglosci2D[kr.sasiad][pienNowy])
                    odleglosci2D[kr.sasiad][pienNowy] = odleglosci2D[wierz][pien] + kr.waga;
            }
        }
    }
}

bool odwiedzone_back[3001][3001];
int najkrotsza_back = INF;
int oplata_back = 0;
int odl_back = 0;
int koncowy_back;
bool odwiedzone1_back[3001];

int odleglosciKopia[3003][3003];
int odleglosciKopia2[3003][3003];

void rozwiaz() {
    scanf("%d %d %d", &V, &K, &O);
    init2D();
    int od, doo, odl, op;
    while (K--) {
        scanf("%d %d %d %d", &od, &doo, &odl, &op);
        Krawedz k;
        k.sasiad = doo;
        k.waga = odl;
        k.oplata = op;
        listy[od].push_back(k);
        Krawedz k2;
        k2.sasiad = od;
        k2.waga = odl;
        k2.oplata = op;
        listy[doo].push_back(k2);
    }

    int pocz, kon;
    scanf("%d %d", &pocz, &kon);

    optymalny2(pocz);

    int najkP = 0;
    for (int i = 1; i <= O; i++) {
        if (odleglosci2D[kon][najkP] > odleglosci2D[kon][i]) {
            najkP = i;
        }

    }
    if (odleglosci2D[kon][najkP] == INF)
        printf("NIE\n");
    else {
        printf("%d\n", odleglosci2D[kon][najkP]);
    }
}

int main(int argc, char **argv) {
    rozwiaz();
    return 0;
}


