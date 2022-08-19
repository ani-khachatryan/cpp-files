#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;
const int maxn = 100'002;

priority_queue<pair<int, int>> q;
int cur;
vector<pair<int, int>> ans;
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        q.push({k, i});
    }
    while (q.size() >= 2) {
        auto a = q.top();
        q.pop();
        auto b = q.top();
        q.pop();
        ans.push_back(make_pair(a.second, b.second));
        a.first--;
        b.first--;
        if (a.first)
            q.push(a);
        if(b.first)
            q.push(b);
    }
    cout << ans.size() << '\n';
    for (pair<int, int>& x: ans) {
        cout << x.first << ' ' << x.second << '\n';
    }
}
