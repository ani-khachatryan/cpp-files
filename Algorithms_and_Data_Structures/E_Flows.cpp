#include <iostream>
#include <vector>
using namespace std;
const int maxn = 302;

char matrix[maxn][maxn];
int help[maxn][maxn];
vector<int> mt;
vector<char> used;
vector<vector<int>> g;
int cnt, number_tiles;
bool kuhn(int v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 || kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, a, b;
    std::cin >> n >> m >> a >> b;
    int count1 = 0, count2 = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
            if (matrix[i][j] == '*')
                number_tiles++;
            if (((i + j)%2 == 0) && matrix[i][j] == '*') {
                help[i][j] = count1;
                count1++;
            }
            if (((i + j)%2 == 1) && matrix[i][j] == '*') {
                help[i][j] = count2;
                count2++;
            }
        }
    }
    g.resize(count2);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i + j) % 2 == 1 && matrix[i][j] == '*') {
                if (i - 1 >= 0 && matrix[i - 1][j] == '*') {
                    g[help[i][j]].push_back(help[i - 1][j]);
                }
                if (j + 1 < m && matrix[i][j + 1] == '*') {
                    g[help[i][j]].push_back(help[i][j + 1]);
                }
                if (i + 1 < n && matrix[i + 1][j] == '*') {
                    g[help[i][j]].push_back(help[i + 1][j]);
                }
                if (j - 1 >= 0 && matrix[i][j - 1] == '*') {
                    g[help[i][j]].push_back(help[i][j - 1]);
                }
            }
        }
    }
    bool used1[count2 + 1];
    for (int i = 0; i < count2; i++)
    {
        used1[i] = false;
    }
    
    mt.assign(count1, -1);
    for (int i = 0; i < count2; ++i)
        for (int j = 0; j < g[i].size(); j++)
        {
            if(mt[g[i][j]] == -1) {
                mt[g[i][j]] = i;
                used1[i] = true;
                break;
            }
        }
    for (int i = 0; i < count2; i++)
    {
        if (used1[i])
            continue;
        used.assign(count2, false);
        kuhn(i);
    }
    
    for (size_t i = 0; i < mt.size(); ++i) {
        if (mt[i] != -1) {
            cnt++;
        }
    }
    if (2 * b <= a) {
        std::cout << number_tiles * b;
    }
    else {
        int ans = a * cnt + (number_tiles - 2 * cnt) * b;
        std::cout << ans;
    }
    //std::cout << cnt;
}
