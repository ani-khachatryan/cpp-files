#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
const int maxn = 100'002;

struct el {
    int ind;
    ll d, a;
};
ll b = -1;
vector<el> a, bb, c;
int main() {
    int n;
    ll cur;
    cin >> n >> cur;
    //cerr << n << ' ' << cur << '\n';
    for (int i = 0; i < n; i++) {
        ll d, a;
        cin >> d >> a;
        //cerr << a[i].d << ' ' << a[i].a << '\n';
        if (d > a)
            c.push_back({i + 1, d, a});
        if (d < a)
            ::a.push_back({i + 1, d, a});
        if (d - a == 0)
            b = max(b, d), bb.push_back({i + 1, d, a});
    }
    sort(::a.begin(), ::a.end(),
        [] (const el& x, const el& y) {
            return x.d < y.d;
        }
    );
    sort(c.begin(), c.end(),
        [] (const el& x, const el& y) {
            return x.a > y.a;
        }
    );
    bool ok = true;
    for (auto i : ::a) {
        cur -= i.d;
        if (cur <= 0) {
            ok = false;
            break;
        }
        cur += i.a;
    }
    if (cur <= b)
        ok = false;
    for (auto i : c) {
        cur -= i.d;
        if (cur <= 0) {
            ok = false;
            break;
        }
        cur += i.a;
    }
    if(!ok) {
        cout << "NIE\n";
        return 0;
    }
    cout << "TAK\n";
    for (auto i: ::a)
        cout << i.ind << ' ';
    for (auto i: bb)
        cout << i.ind << ' ';
    for (auto i: c)
        cout << i.ind << ' ';
}
