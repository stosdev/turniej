#include <iostream>

using namespace std;

class Prezes {
public:
    int *W;
    int n, zysk, o1, o2;

    Prezes(int A[], int tabSize) {
        n = tabSize;
        W = new int[n];
        for (int i = 0; i < n; i++) W[i] = A[i];
    }

    void Okres() {
        int Max = 0, max = 0;
        for (int i = 0; i < n; i++) {
            max += W[i];
            if (max < 0) max = 0;
            else if (Max < max) {
                Max = max;
                o2 = i;
            }
        }
        max = Max;
        o1 = o2;
        while (max > 0) {
            max -= W[o1];
            o1--;
        }
        o1 += 2;
        o2++;
        zysk = Max;
    }
};

int main() {
    int tabSize;
    cin >> tabSize;
    int tab[tabSize];
    for (int i = 0; i < tabSize; i++) {
        cin >> tab[i];
    }
    Prezes *pr = new Prezes(tab, tabSize);
    pr->Okres();
    cout << pr->o1 << " " << pr->o2 << " " << pr->zysk << endl;
    return 0;
}
