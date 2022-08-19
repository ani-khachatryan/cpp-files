#include <iostream>
using namespace std;
using ll = long long;
const int maxn = 100002;

struct el {
    ll val;
    int pos;
    operator ll() {
        return this->val;
    }    
};
el heap[maxn];
int sz;

void swap(int a, int b) {
    el tmp = heap[a];
    heap[a] = heap[b];
    heap[b] = tmp;    
}
void siftdown(int i) {
        if (2 * i + 1 <= sz && heap[2 * i + 1] < heap[2 * i])
            if (heap[2 * i + 1] < heap[i]) {
                swap(2 * i + 1, i);
                siftdown(2 * i + 1);
            }
        if (2 * i <= sz && heap[2 * i] < heap[i]) {
            swap(2 * i, i);
            siftdown(2 * i);
        }
}
void siftup(int i) {
    while (i / 2)
        if (heap[i] < heap[i / 2])
        {
            swap(i, i / 2);
            i /= 2;
        }
        else break;
}
void insert(int x) {
    ++sz;
    heap[sz] = {x, sz};
    siftup(sz);
}
el extractmin() {
    el mn = heap[1];
    heap[1] = heap[sz--];
    siftdown(1);
    return mn;
}

ll dp[maxn];
el a[maxn];
bool mark[maxn];
int main() 
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ll x;
        cin >> x;
        insert(x);
    }
    int i = 0;
    while (++i <= n)
        a[i] = extractmin();
    int p = 0;
    dp[1] = a[1];
    dp[2] = dp[1] + a[2];

    ll ma, ind = 1;
    if (dp[1] >= dp[2])
        ma = dp[1];
    else ma = dp[2];
    for (int i = 3; i <= n; i++)
    {
        dp[i] = a[i] + dp[i - 1];
        while (p + 1 < i && a[p] + a[p + 1] < a[i])
            dp[i] -= a[p++];
        if (dp[i] > ma)
        {
            ma = dp[i];
            ind = p;
        }
    }
    cout << ma << '\n';
    while (ma > 0) {
        mark[a[ind].pos] = 1;
        ma -= a[ind];
        ind++;
    }
    for (int i = 1; i <= n; i++)
        if (mark[i])
            cout << i << ' ';
}

