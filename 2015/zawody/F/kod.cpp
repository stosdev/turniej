#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Tulibajt {
public:
    string *S1;
    int n;
    string s = "";

    Tulibajt(string B[], int tabSize) {
        n = (tabSize + 1) / 2;
        S1 = new string[2 * n];
        for (int i = 0; i < 2 * n; i++) S1[i] = B[i];
    }

    void ZadTB() {
        string s1, s2;
        int l;
        for (int i = 0; i < n; i++) {
            s1 = S1[2 * i];
            s2 = S1[2 * i + 1];
            l = TAB_NWP(s1, s2);
            ostringstream ss;
            ss << l;
            string str = ss.str();
            s += str;
            s += " ";
        }
        cout << s << endl;
    }

    int TAB_NWP(string s1, string s2) {
        const int r1 = s1.length();
        const int r2 = s2.length();
        int S[1000][1000];
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                S[i][j] = 0;
            }
        }

        for (int i = 1; i <= r1; i++)
            for (int j = 1; j <= r2; j++)
                if (s1[i - 1] == s2[j - 1]) S[i][j] = S[i - 1][j - 1] + 1;
                else if (S[i - 1][j] >= S[i][j - 1]) S[i][j] = S[i - 1][j];
                else S[i][j] = S[i][j - 1];
        return S[s1.length()][s2.length()];
    }
};

int main() {
    int tabSize;
    cin >> tabSize;
    string tab[tabSize * 2];
    for (int i = 0; i < tabSize * 2; i++) {
        cin >> tab[i];
    }
    Tulibajt *tb = new Tulibajt(tab, tabSize * 2);
    tb->ZadTB();
    return 0;
}
