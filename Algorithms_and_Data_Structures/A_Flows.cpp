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
int used[105][105];
ll ar[105][105];
vector<int> v[105], d;
int p[105];
queue<pair<int, ll>> q;

void solve()
{
	int n, i, j, x, y, s, t, r, z;
	cin >> n;
	if (n == 0)exit(0);
	cin >> s >> t >> r;
	for ( i = 0; i < r; i++)
	{
		cin >> x >> y >> z;
		if (!used[x][y])
		{
			v[x].push_back(y);
			v[y].push_back(x);
			used[x][y] = 1;
			used[y][x] = 1;
		}
		ar[x][y] += z;
		ar[y][x] += z;
	}
	ll oo = 1000000000000000000LL, arj = 0, ans = 0;
	while (1) 
	{
		arj = 0;
		p[s] = s;
		q.push({s, oo});
		int flag = 0;
		while (!q.empty())
		{
			pair<int, ll> g = q.front();
			q.pop();
			for (int to : v[g.first])
			{
				if (!p[to] && ar[g.first][to])
				{
					q.push({ to, min(g.second, ar[g.first][to]) });
 					p[to] = g.first;
					if (to == t)
					{
						arj = min(g.second, ar[g.first][to]);
						flag = 1;
						break;
					}
				}
			}
			if (flag)
				break;
		}
		while (!q.empty())
		{
			q.pop();
		}
		if (p[t] == 0)
			break;
		int g = t;
		d.push_back(t);
		do
		{
			d.push_back(p[g]);
			g = p[g];
		} while (g != s);
		for ( i = 0; i < int(d.size()) - 1; i++)
		{
			ar[d[i]][d[i + 1]] += arj;
			ar[d[i + 1]][d[i]] -= arj;
		}
		d.clear();
		for ( i = 1; i <= n; i++)
		{
			p[i] = 0;
		}
		ans += arj;
	}
	cout << ans << '\n';
	while (!q.empty())
	{
		q.pop();
	}
	d.clear();
	for ( i = 1; i <= n; i++)
	{
		v[i].clear();
		p[i] = 0;
		for ( j = 1; j <= n; j++)
		{
			ar[i][j] = 0;
			used[i][j] = 0;
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int tt = 1;
	while (1)
	{
		solve();
	}
	return 0;
}
