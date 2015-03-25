#include <stdio.h>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int kandydaci[100003];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &(kandydaci[i]));
    sort(kandydaci, kandydaci + n);
    int srednia = (kandydaci[n - 1] + kandydaci[n - 2] + kandydaci[n - 3] + kandydaci[n - 4] + kandydaci[n - 5]) / 5;
    printf("%d\n", srednia);

}
