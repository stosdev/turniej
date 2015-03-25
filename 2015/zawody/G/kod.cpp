#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define INF 1000000000

using namespace std;
bool czyByl[11][1000001];

void rozwiaz() {
    int n, m;
    vector<pair<int, int> > przejazdy[20];
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        assert(a <= m && b >= 1 && b <= 1000000 && c >= 1 && c <= 1000000);
        assert(czyByl[a][c] == false);
        czyByl[a][c] = true;
        przejazdy[a].push_back(make_pair(c, b));
    }
    for (int i = 1; i <= m; i++) {
        sort(przejazdy[i].begin(), przejazdy[i].end());
        int minimalny = INF;
        int ile = 0;
        for (unsigned int j = 0; j < przejazdy[i].size(); j++) {
            if (przejazdy[i][j].second < minimalny) {
                minimalny = przejazdy[i][j].second;
                ile++;
            }
        }
        printf("%d\n", ile);
    }
}

int main(int argc, char **argv) {
    rozwiaz();
    return 0;
}


