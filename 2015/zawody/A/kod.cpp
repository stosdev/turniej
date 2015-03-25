#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

using namespace std;

int malePierwsze[100000];
int malePierwszeDo = 1100000;
unsigned char maleSito[1100001];
int ileMalePierwsze = 0;

void obliczMalePierwsze() {
    for (long i = 2; i * i <= malePierwszeDo; i++) {
        if (maleSito[i] == 1)
            continue;
        for (long j = 2 * i; j <= malePierwszeDo; j += i)
            maleSito[j] = 1;
    }
    for (long i = 2; i <= malePierwszeDo; i++)
        if (maleSito[i] == 0)
            malePierwsze[ileMalePierwsze++] = i;
}

void sitoOdDo(long long od, long long doo, unsigned char *bits) {
    long long limit = doo - od;
    if (od == 0)
        bits[0] = bits[1] = 1;
    if (od == 1)
        bits[0] = 1;
    for (long i = 0; ((long long) malePierwsze[i]) * malePierwsze[i] <= doo; i++) {
        long long pocz = od;
        long long pierwsza = malePierwsze[i];
        long long reszta = pocz % pierwsza;
        if (reszta != 0)
            pocz = pocz + pierwsza - reszta;
        if (pocz == 0)
            pocz += 2 * pierwsza;
        if (pocz == pierwsza)
            pocz += pierwsza;
        for (long long j = pocz - od; j <= limit; j += pierwsza)
            bits[j] = 1;
    }
}

unsigned char bity[11000000];
unsigned char bity2[11000000];

int ileBezpiecznych(long long od, long long doo) {
    memset(bity, 0, (doo - od) + 1);
    memset(bity2, 0, (doo - od) + 1);
    sitoOdDo(od / 2, doo / 2, bity);
    sitoOdDo(od, doo, bity2);
    int ile = 0;
    for (long long pocz = od; pocz <= doo; pocz++) {
        if (bity2[pocz - od] == 0) {
            if (bity[pocz / 2 - od / 2] == 0) {
                ile++;
            }
        }
    }
    return ile;
}

void wczytaj() {
    int ile;
    obliczMalePierwsze();
    scanf("%d", &ile);
    assert(ile >= 1 && ile <= 100);
    for (int i = 0; i < ile; i++) {
        long long od, doo;
        scanf("%lld %lld", &od, &doo);
        assert(od >= 1 && od <= 1000000000000ll && doo >= 1 && doo <= 1000000000000ll && od <= doo && od + 10000000 >= doo);
        int wyraf = ileBezpiecznych(od, doo);
        printf("%d\n", wyraf);
    }
}

int main() {
    wczytaj();
}