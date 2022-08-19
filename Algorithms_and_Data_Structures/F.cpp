#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;
using ll = long long;
const int maxn = 100'002;

priority_queue<long double> q;
int cur;
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        q.push(-k);
    }
    long double ans = 0;
    while (q.size() >= 2) {
        auto a = -q.top();
        q.pop();
        auto b = -q.top();
        q.pop();
        ans += (a + b) * 0.05;
        q.push(-(a + b));
    }
    cout << fixed << setprecision(2) << ans << '\n';
}
