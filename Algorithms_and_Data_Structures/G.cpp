using namespace std;
using ll = long long;
const int maxn = 150'002;
const int inf = 2147483647;

int a[maxn];
int t[4 * maxn];
void build(int v, int vl, int vr) {
    if (vl == vr) {
        t[v] = a[vl];
        return;
    }
    int m = (vl + vr) / 2;
    build(v * 2, vl, m);
    build(v * 2 + 1, m + 1, vr);
    t[v] = min(t[v * 2], t[v * 2 + 1]);
}
ll getmin(int v, int vl, int vr, int l, int r) {
    if (vl == l && vr == r)
        return t[v];
    int m = (vl + vr) / 2;
    ll ans = inf;
    if (l <= m)
        ans = min(ans, getmin(v * 2, vl, m, l, min(r, m)));
    if (r > m)
        ans = min(ans, getmin(v * 2 + 1, m + 1, vr, max(l, m + 1), r));
    return ans;
}

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(1, 0, n - 1);
    for (int i = k - 1; i < n; i++)
        cout << getmin(1, 0, n - 1, i - k + 1, i) << '\n';
}
