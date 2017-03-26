#include <cmath>
#include <iostream>

using namespace std;

class TROJKAT {
private:
public: // User declarations
    char ***T;
    int N, l;
    string S, W;

    TROJKAT(int n, string w, string s);

    void szescian();

    void kwadratA0(int k, int n, int w);

    void kwadratA1(int k, int n, int w);

    void kwadratB0(int w);

    void kwadratB1(int w);

    string trojkat1();

    string trojkat2();

    string trojkat3();

    string trojkat4();
};
//

int main() {
    int n;
    string a, b;
    cin >> n;
    cin >> a >> b;
//    TROJKAT *F = new TROJKAT(6, "AA", "ABCDEFGHIJKLMNOPQRSTU");
    TROJKAT *F = new TROJKAT(n, a, b);
    F->szescian();
    string s = "";
    s += F->trojkat1();
    s += F->trojkat2();
    s += F->trojkat3();
    s += F->trojkat4();
    cout << s << endl;
    return 0;
}

TROJKAT::TROJKAT(int n, string w, string s) {
    S = s;
    N = n;
    l = 0;
    W = w;
    T = new char **[n];
    for (int i = 0; i < n; i++) {
        T[i] = new char *[n];
        for (int j = 0; j < n; j++)
            T[i][j] = new char[n];
    }
}

//---------------------------------------------------------------------------
void TROJKAT::kwadratA0(int k, int n, int w) {
    if (n <= 0)return;
    for (int j = k; j < n + k; j++)T[k][j][w] = S[(l++) % S.length()];
    if (n == 1)return;
    for (int i = k + 1; i < n + k - 1; i++)T[i][n - 1 + k][w] = S[(l++) % S.length()];
    for (int j = n + k - 1; j > k - 1; j--)T[n - 1 + k][j][w] = S[(l++) % S.length()];
    for (int i = n + k - 2; i > k; i--)T[i][k][w] = S[(l++) % S.length()];
    kwadratA0(k + 1, n - 2, w);
}

//---------------------------------------------------------------------------
void TROJKAT::kwadratA1(int k, int n, int w) {
    if (n > N)return;
    if (n == 1) {
        T[k][k][w] = S[(l++) % S.length()];
        kwadratA1(k - 1, n + 2, w);
        return;
    }
    if (n == 2) {
        for (int j = k; j <= k + 1; j++)T[k + 1][j][w] = S[(l++) % S.length()];
        for (int j = k + 1; j >= k; j--)T[k][j][w] = S[(l++) % S.length()];
        kwadratA1(k - 1, n + 2, w);
        return;
    }
    for (int i = k + 1; i < n + k; i++)T[i][k][w] = S[(l++) % S.length()];
    for (int j = k + 1; j < n + k; j++)
        T[n - 1 + k][j][w] = S[(l++) % S.length()];
    for (int i = n + k - 2; i > k - 1; i--)T[i][n - 1 + k][w] = S[(l++) % S.length()];
    for (int j = n + k - 2; j > k - 1; j--)T[k][j][w] = S[(l++) % S.length()];
    kwadratA1(k - 1, n + 2, w);
}

//---------------------------------------------------------------------------
void TROJKAT::kwadratB0(int w) {
    for (int j = 0; j < N; j++) {
        if (j % 2 == 0)for (int k = 0; k < N; k++) T[k][j][w] = S[(l++) % S.length()];
        else for (int k = N - 1; k >= 0; k--) T[k][j][w] = S[(l++) % S.length()];
    }
}

//---------------------------------------------------------------------------
void TROJKAT::kwadratB1(int w) {
    for (int j = N - 1; j >= 0; j--)
        if (j % 2 == 1)for (int k = 0; k < N; k++) T[k][j][w] = S[(l++) % S.length()];
        else for (int k = N - 1; k >= 0; k--) T[k][j][w] = S[(l++) % S.length()];
}

//---------------------------------------------------------------------------
string TROJKAT::trojkat1() {
    string s = "";
    for (int i = 0; i < N; i++)s += T[0][i][i];
    s += " ";
    for (int i = 0; i < N; i++)s += T[i][N - 1][N - 1 - i];
    s += " ";
    for (int i = N - 1; i >= 0; i--)s += T[i][i][0];
    s += "\n";
    return s;
}

//---------------------------------------------------------------------------
string TROJKAT::trojkat2() {
    string s = "";
    for (int i = 0; i < N; i++)s += T[i][0][i];
    s += " ";
    for (int i = 0; i < N; i++)s += T[N - 1][i][N - 1 - i];
    s += " ";
    for (int i = N - 1; i >= 0; i--)s += T[i][i][0];
    s += "\n";
    return s;
}

//---------------------------------------------------------------------------
string TROJKAT::trojkat3() {
    string s = "";
    for (int i = 0; i < N; i++)s += T[0][i][i];
    s += " ";
    for (int i = 0; i < N; i++)s += T[i][N - 1 - i][N - 1];
    s += " ";
    for (int i = N - 1; i >= 0; i--)s += T[i][0][i];
    s += "\n";
    return s;
}

//---------------------------------------------------------------------------
string TROJKAT::trojkat4() {
    string s = "";
    for (int i = 0; i < N; i++)s += T[0][i][i];
    s += " ";
    for (int i = 0; i < N; i++)s += T[i][N - 1][N - 1];
    s += " ";
    for (int i = N - 1; i >= 0; i--)s += T[i][i][i];
    s += "\n";
    return s;
}

//---------------------------------------------------------------------------
void TROJKAT::szescian() {
    int i = 0, n1;
    while (i < N)
        if (i % 4 == 0)
            switch (W[0]) {
                case 'A':
                    kwadratA0(0, N, i++);
                    break;
                case 'B':
                    kwadratB0(i++);
                    break;
            }
        else if (i % 4 == 1)
            switch (W[0]) {
                case 'A':
                    n1 = ((N % 2) == 1) ? 1 : 2;
                    kwadratA1((N + 1) / 2 - 1, n1, i++);
                    break;
                case 'B':
                    kwadratB1(i++);
                    break;
            }
        else if (i % 4 == 2)
            switch (W[1]) {
                case 'A':
                    kwadratA0(0, N, i++);
                    break;
                case 'B':
                    kwadratB0(i++);
                    break;
            }
        else if (i % 4 == 3)
            switch (W[1]) {
                case 'A':
                    n1 = ((N % 2) == 1) ? 1 : 2;
                    kwadratA1((N + 1) / 2 - 1, n1, i++);
                    break;
                case 'B':
                    kwadratB1(i++);
                    break;
            }
}
