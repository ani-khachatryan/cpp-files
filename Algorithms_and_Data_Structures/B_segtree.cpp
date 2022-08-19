#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
const int maxn = 500'002;

struct query {
    ll l;
    ll r;
} q[maxn];
bool operator<(const query& a, const query& b) {
    return a.l < b.l;
}
bool compress(const query& a, const query& b) {
    return a.r < b.r;
}
int t[4 * maxn];
void insert(int v, int vl, int vr, int pos) {
    if (vl == vr) {
        t[v]++;
        return;
    }
    int m = (vl + vr) / 2;
    if (pos <= m)
        insert(v * 2, vl, m, pos);
    else insert(v * 2 + 1, m + 1, vr, pos);
    t[v] = t[v * 2] + t[v * 2 + 1];
}
ll getsum(int v, int vl, int vr, int l, int r) {
    if (vl == l && vr == r)
        return t[v];
    int m = (vl + vr) / 2;
    ll ans = 0;
    if (l <= m)
        ans += getsum(v * 2, vl, m, l, min(r, m));
    if (r > m)
        ans += getsum(v * 2 + 1, m + 1, vr, max(l, m + 1), r);
    return ans;
}
int ind;
int main() {
    int n;
    cin >> n;
    ll l;
    cin >> l;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        q[i].l = i;
        q[i].r = l * x + i;
    }
    sort(q, q + n, compress);
    ll prev = -1;
    for (int i = 0; i < n; i++) {
        if (q[i].r != prev) {
            prev = q[i].r;
            q[i].r = ++ind;
        } else {
            q[i].r = ind;
        }
    }
    sort(q, q + n);
    for (int i = 0; i < n; i++) {
        insert(1, 1, n, q[i].r);
        if (q[i].r != n)
            ans += getsum(1, 1, n, q[i].r + 1, n);
    }
    cout << ans << '\n';
}
