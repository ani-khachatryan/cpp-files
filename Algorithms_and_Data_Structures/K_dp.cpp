#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <cmath>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <stack>
#include <deque>
using namespace std;
using ll = long long;
int a[1005][1005];
struct koxm
{
	int a, b, c, d;
};
koxm dp[1005][1005];

void solve()
{
	int n, i, j, l, x, oo = 1000000005;
	cin >> n >> l;
	for ( i = 0; i < n; i++)
	{
		for ( j = 0; j < n; j++)
		{
			cin >> a[i][j];
			dp[i][j].a = oo;
			dp[i][j].b = oo;
			dp[i][j].c = oo;
			dp[i][j].d = oo;
		}
	}
	if (l == 1)
	{
		for ( i = 0; i < n; i++)
		{
			for ( j = 0; j < n; j++)
			{
				cout << a[i][j] << ' ';
			}
			cout << '\n';
		}
		exit(0);
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (i % (l - 1) == 0 && j % (l - 1) == 0)
				dp[i][j].a = a[i][j];
			else if (j % (l - 1) == 0)
				dp[i][j].a = min(dp[i - 1][j].a, a[i][j]);
			else if (i % (l - 1) == 0)
				dp[i][j].a = min(dp[i][j - 1].a, a[i][j]);
			else 
				dp[i][j].a = min(a[i][j], min(dp[i - 1][j].a, dp[i][j - 1].a));
	for (i = n - 1; i >= 0; i--)
		for (j = n - 1; j >= 0; j--)
			if ((i % (l - 1) == l - 2 || i == n - 1) && (j % (l - 1) == l - 2 || j == n - 1))
				dp[i][j].d = a[i][j];
			else if ((j % (l - 1) == l - 2 || j == n - 1))
				dp[i][j].d = min(dp[i + 1][j].d, a[i][j]);
			else if ((i % (l - 1) == l - 2 || i == n - 1))
				dp[i][j].d = min(dp[i][j + 1].d, a[i][j]);
			else 
				dp[i][j].d = min(a[i][j], min(dp[i + 1][j].d, dp[i][j + 1].d));
	for (i = n - 1; i >= 0; i--)
		for (j = 0; j < n; j++)
			if ((i % (l - 1) == l - 2 || i == n - 1) && j % (l - 1) == 0)
				dp[i][j].c = a[i][j];
			else if (j % (l - 1) == 0)
				dp[i][j].c = min(dp[i + 1][j].c, a[i][j]);
			else if ((i % (l - 1) == l - 2 || i == n - 1))
				dp[i][j].c = min(dp[i][j - 1].c, a[i][j]);
			else
				dp[i][j].c = min(a[i][j], min(dp[i + 1][j].c, dp[i][j - 1].c));
	for (i = 0; i < n; i++)
		for (j = n - 1; j >= 0; j--)
			if (i % (l - 1) == 0 && (j % (l - 1) == l - 2 || j == n - 1))
				dp[i][j].b = a[i][j];
			else if ((j % (l - 1) == l - 2 || j == n - 1))
				dp[i][j].b = min(dp[i - 1][j].b, a[i][j]);
			else if (i % (l - 1) == 0)
				dp[i][j].b = min(dp[i][j + 1].b, a[i][j]);
			else 
				dp[i][j].b = min(a[i][j], min(dp[i - 1][j].b, dp[i][j + 1].b));
	for ( i = 0; i < n - l + 1; i++)
	{
		for ( j = 0; j < n - l + 1; j++)
		{
			cout << min(min(dp[i][j].d, dp[i][j + l - 1].c), min(dp[i + l - 1][j].b, dp[i + l - 1][j + l - 1].a)) << ' ';
		}
		cout << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int tt = 1;
	//cin >> tt;
	while (tt--)
	{
		solve();
	}
	return 0;
}
