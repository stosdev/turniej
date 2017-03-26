#include <iostream>

using namespace std;

string pr = "", od = "";

char xorr(char b1, char b2) {
    if (b1 != b2) {
        return '1';
    }
    return '0';
}

string Xor(string s1, string s2) {
    string s = "";
    if (s1.length() == s2.length()) {
        for (int i = 0; i <= s1.length() - 1; i++) {
            s += xorr(s1[i], s2[i]);
        }
    }
    return s;
}

string nextBin(string s) {
    int i;
    if (s[s.length() - 1] == '0') {
        s[s.length() - 1] = '1';
    } else {
        if (s[0] == '1') {
            s = "0" + s;
        }
        s[s.length() - 1] = '0';
        i = 2;
        while (s[s.length() - i] != '0') {
            s[s.length() - i] = '0';
            i++;
        }
        s[s.length() - i] = '1';
    }
    i = 0;
    while (s[i] == '0') {
        i++;
    }
    s = s.substr(i, s.length());
    return s;
}

string TMult2(string a) {
    string ilo = string({a[0]});
    for (int i = 1; i < a.length(); i++)ilo = ilo + "0" + a[i];
    return ilo;
}

string toGFM2(string x, string f) {
    int xl = (int) x.length();
    int m = (int) (f.length() - 1);
    if (xl != m) {
        if (xl < m) {
            for (int i = 1; i <= m - xl; i++) {
                x = "0" + x;
            }
        } else {
            string pr1 = x.substr(0, xl - m);
            if (pr1 != pr) {
                pr = pr1;
                od = x;
                f = f.substr(1, f.length() - 1);
                for (int i = 0; i < xl - m; i++)
                    if (od[0] != '1') {
                        od = od.substr(1, od.length() - 1);
                    } else {
                        od = Xor(od.substr(1, f.length()), f) + od.substr(m + 1, od.length() - m - 1);
                    }
            }
            x = Xor(od, x.substr(xl - m, m));
        }
    }
    return x;
}

string Turniej01(string sa, string sb, string sp) {
    string g = sa, g2 = "", g2p = "", zero = toGFM2("0", sp), s2 = "";
    int i = 0;
    while (sb[i] == '0')i++;
    sb = sb.substr(i, sb.length());
    do {
        g = nextBin(g);
        g2 = TMult2(g);
        g2p = toGFM2(g2, sp);
        if (g2p == toGFM2(g, sp)) {
            s2 += toGFM2(g, sp) + " a2\n";
        } else if (g2p == zero) {
            s2 += toGFM2(g, sp) + " 0\n";
        }
    } while (g != sb);
    return s2;
}


int main() {
    string a, b, p;
    cin >> a >> b >> p;
    auto res = Turniej01(a, b, p);
    cout << res << endl;
}
