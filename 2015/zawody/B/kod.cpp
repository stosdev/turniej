#include <iostream>
#include <sstream>

using namespace std;

class Graf {
public:
    double **A;
    int size;
    int time;
    bool b;
    int *ff;
    int *s1;

    Graf(int n) {
        size = n;
        A = new double *[n];
        for (int i = 0; i < n; ++i) {
            A[i] = new double[n];
        }
    }

    Graf(double **B, int size) : Graf(size) {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) A[i][j] = B[i][j];
    }

    void WGlab1(int *f) {
        ff = new int[size];
        int *Nowy = new int[size];
        time = 0;
        for (int i = 0; i < size; i++)
            if (Nowy[i] == 0) WG1(i, f, Nowy);
    }

    void WG1(int v, int *f, int *Nowy) {
        Nowy[v] = 1;
        for (int i = 0; i < size; i++)
            if (A[v][i] != 999 && Nowy[i] == 0) WG1(i, f, Nowy);
        f[v] = time++;
        ff[size - f[v] - 1] = v;
    }

    void WGlab2(int *k, int k1) {
        int *Nowy = new int[size];
        for (int i = 0; i < size; i++)
            if (Nowy[k[i]] == 0) {
                s1 = new int[size];
                WG2(k[i], Nowy, k1);
                if (b) break;
            }
    }

    void WG2(int v, int *Nowy, int k1) {
        s1[v] = 1;
        if (v == k1) b = true;
        Nowy[v] = 1;
        for (int i = 0; i < size; i++)
            if (A[v][i] != 999 && Nowy[i] == 0) WG2(i, Nowy, k1);
    }

    Graf transp() {
        int n = size;
        Graf *g = new Graf(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g->A[j][i] = A[i][j];
        return *g;
    }

    void SSS(int k1) {
        int *f = new int[size];
        WGlab1(f);
        Graf g = transp();
        g.WGlab2(ff, k1);
        printGraph(g);
        cout << endl;
    }

    void printGraph(Graf &graf) {
        string s = "";
        for (int i = 0; i < graf.size; i++)
            if (graf.s1[i] == 1)
                cout << i + 1 << " ";
    }

    void ZadSSS(int m, double chf, double eur, int k1, int k2) {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (m * (1 - A[i][j]) > chf - eur) A[i][j] = 1;
                else A[i][j] = 999;
        SSS(k1 - 1);
        SSS(k2 - 1);
    }
};

int main() {
    int n, m, k, t;
    double chf, eur;
    cin >> n >> m >> chf >> eur >> k >> t;
    double **graph = new double *[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new double[n];
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    Graf *g = new Graf(graph, n);
    g->ZadSSS(m, chf, eur, k, t);
    return 0;
}
