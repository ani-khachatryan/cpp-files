#include <iostream>
#include <vector>
using namespace std;

const int maxn = 302;
const int oo = 1'000'000'000;

int a[maxn][maxn], u[maxn], v[maxn];
bool used[maxn];
int mincolumn[maxn], match[maxn], minind[maxn];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    for (int i = 1; i <= n; i++)
    {
        match[0] = i;
        int freej = 0;
        for (int k = 0; k <= n; k++)
        {
            mincolumn[k] = oo;
            used[k] = false;
        }
        while (1) {
            used[freej] = true;
            int curi = match[freej],  delta = oo,  curj = 0;
            for (int j = 0; j <= n; j++)
                if (!used[j]) {
                    int cur = a[curi][j] - u[curi] - v[j];
                    if (cur < mincolumn[j]) {
                        mincolumn[j] = cur;
                        minind[j] = freej;
                    }
                    if (mincolumn[j] < delta) {
                        delta = mincolumn[j];
                        curj = j;
                    }
                }
            
            for (int j = 0; j <= n; j++)
            {
                if (used[j]) {
                    u[match[j]] += delta;
                    v[j] -= delta;
                } else  {
                    mincolumn[j] -= delta;
                }
            }
            freej = curj;
            if (match[freej] == 0)
                break;
        }
        do {
            int j1 = minind[freej];
            match[freej] = match[j1];
            freej = j1;
        } while (freej);
    }
    vector<int> ans(n + 1);
    for (int j = 1; j <= n; j++)
	    ans[match[j]] = j;
    cout << -v[0] << '\n';
    for (int j = 1; j <= n; j++)
    {
        cout << j << ' ' << ans[j] << '\n';
    }
        
}
