#include <stdio.h>


void rozwiaz() {
    int od, doo;
    scanf("%d %d", &od, &doo);
    int maxDziel = 0, maxLiczba = -1;
    for (int i = od; i <= doo; i++) {
        int ile = 0;
        for (int j = 1; j <= i; j++)
            if (i % j == 0)
                ile++;
        if (ile > maxDziel) {
            maxDziel = ile;
            maxLiczba = i;
        }
    }
    printf("%d\n", maxLiczba);
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--)
        rozwiaz();

}
