#include <cstdio>
#include <algorithm>

using namespace std;

class DrzewoPrzedzialowe2D {
private:
    int** wartosci;
    int potegaX;
    int potegaY;
    int (*f)(int, int);
    int n;
    int m;
public:
    int get(int x, int y){
        return wartosci[x][y];
    }
    DrzewoPrzedzialowe2D(int nn, int mm, int (*ff)(int, int), int v) {
        n=nn;
        m=mm;
        potegaX = potegaY = 2;
        while (n>potegaX)
            potegaX*= 2;
        while (m>potegaY)
            potegaY*= 2;
        f=ff;
        wartosci=new int*[potegaX*2];
        for(int i=0;i<potegaX*2;i++)
            wartosci[i]=new int[potegaY*2];
        for(int i=0;i<potegaX*2;i++)
            for(int j=0;j<potegaY*2;j++)
                wartosci[i][j]=v;
    }
    void inicjuj(int teren[][1000]){
        for(int x=0;x<n;x++){
            int v=potegaX+x;
            for(int y=0;y<m;y++){
                int vv=potegaY+y;
                wartosci[v][vv]=teren[x][y];
            }
            for(int vv=potegaY-1;vv>0;vv--)
                wartosci[v][vv]=f(wartosci[v][2*vv], wartosci[v][2*vv+1]);
        }
        for(int v=potegaX-1;v>0;v--){
            for(int vv=1;vv<potegaY+m;vv++)
                wartosci[v][vv]=f(wartosci[2*v][vv], wartosci[2*v+1][vv]);
        }
    }
    int maksimum1D(int* w, int a, int b) {
        int va=potegaY+a, vb=potegaY+b;
        int wyn=f(w[va], w[vb]);
        while (va/2!=vb/2) {
            if (va%2==0)
                wyn=f((int)wyn, (int)w[va + 1]);
            if (vb%2==1)
                wyn=f(wyn, w[vb - 1]);
            va/=2;
            vb/=2;
        }
        return wyn;
    }
    int maksimum2D(int xOd, int yOd, int xDo, int yDo) {
        int va=potegaX+xOd, vb=potegaX+xDo;
        int wyn=f(maksimum1D(wartosci[va], yOd, yDo), maksimum1D(wartosci[vb], yOd, yDo));
        while (va/2!=vb/2) {
            if (va%2==0)
                wyn=f((int)wyn, (int)maksimum1D(wartosci[va + 1], yOd, yDo));
            if (vb%2==1)
                wyn=f((int)wyn, (int)maksimum1D(wartosci[vb - 1], yOd, yDo));
            va/=2;
            vb/=2;
        }
        return wyn;
    }
    int maks_wartosc_drzewo(int od_x, int od_y, int do_x, int do_y) {
        return maksimum2D(od_x, od_y, do_x, do_y);
    }
};
int teren[1000][1000];
int n, m, nn, mm, k;
int ma(int i, int j){
    return max(i, j);
}
int mi(int i, int j){
    return min(i, j);
}
void test(){
    scanf("%d%d%d", &n, &m, &k);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d", &(teren[i][j]));
        }
    }
    DrzewoPrzedzialowe2D dMax(n, m, ma, -1);
    DrzewoPrzedzialowe2D dMin(n, m, mi, 1000000);
    dMax.inicjuj(teren);
    dMin.inicjuj(teren);
    for(int x=0;x<k;x++){
        int i1, j1, i2, j2;
        scanf("%d%d%d%d", &i1, &j1, &i2, &j2);
        int mii=dMin.maks_wartosc_drzewo(i1-1, j1-1, i2-1, j2-1);
        int maa=dMax.maks_wartosc_drzewo(i1-1, j1-1, i2-1, j2-1);
        printf("%d\n", maa-mii);
    }
}
int main() {
    test();
    return 0;
}
