#include <stdio.h>

#define MODULO 1000000000000000000ll

using namespace std;

long long sposoby[1000001];

void oblicz() {
    sposoby[0] = sposoby[1] = 1;
    sposoby[2] = 5;
    sposoby[3] = 11;
    for (int s = 4; s <= 1000000; s++) {
        sposoby[s] = (sposoby[s - 1] + 5 * sposoby[s - 2] + sposoby[s - 3] - sposoby[s - 4]) % MODULO;
        if (sposoby[s] < 0)
            sposoby[s] += MODULO;
    }
}

int main(int argc, char **argv) {
    oblicz();
    int N;
    scanf("%d", &N);
    while (N--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", sposoby[n]);
    }
    return 0;
}


