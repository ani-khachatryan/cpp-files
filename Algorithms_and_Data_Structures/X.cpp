#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <complex>
#include <string>
#define ld double
#define cd complex<double>
#define vcd vector<cd>
#define vii vector<int>
using namespace std;
using ll = long long;

const int maxn = 4 * 131072;
const ld pi = acos(-1);

int m;
cd roots[maxn];
int rev[maxn];
vii ans;
vcd tmp;
void fft(vcd& a)
{
    int n = a.size();
    for (int i = 0; i < n; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int len = 1, step = n / 2; len < n; len <<= 1, step >>= 1)
        for (int st = 0; st < n; st += len + len)
            for (int i = 0, root = 0; i < len; ++i, root += step)
            {
                cd u = a[st + i], v = roots[root] * a[st + len + i];
                a[st + i] = u + v;
                a[st + i + len] = u - v;
            }
}
void mult(vii& a_, const vii& b_)
{
    vcd a(a_.size());
    vcd b(b_.size());
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] = a_[i];
    }
    for (size_t i = 0; i < b.size(); ++i) {
        b[i] = b_[i];
    }
    int n = 1, h = 0;
    while (n < a.size() + b.size())
        n *= 2, ++h;
    while (a.size() < n) a.push_back(0);
    while (b.size() < n) b.push_back(0);

    rev[0] = 0;
    for (int i = 1, high = -1; i < n; ++i) {
        high += !(i & (i - 1));
        rev[i] = rev[i ^ (1 << high)] | (1 << (h - high - 1));
    }
    ld sector = 2.0 * pi / n;
    for (int i = 0; i < n; ++i) {
        roots[i] = cd(cos(sector * i), sin(sector * i));
    }
    fft(a); fft(b);
    tmp.resize(n);
    for (int i = 0; i < n; ++i)
        tmp[i] += a[i] * b[i];
}
    //cout << "\n\n";

int main() {
    cin >> m;
    string a, b;
    cin >> a >> b;
    reverse(b.begin(), b.end());
    //a.append(a.begin(), a.end());
    b.append(b.begin(), b.end());
    //cout << a << '\n' << b << '\n';
    vii a_(a.size()), b_(b.size());
    for (auto x : {'A', 'C', 'T', 'G'}) {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] == x) {
                a_[i] = 1;
            } else {
                a_[i] = 0;
            }

            if (b[i] == x) {
                b_[i] = 1;
            } else {
                b_[i] = 0;
            }
        }
        mult(a_, b_);
    }

    fft(tmp);
    reverse(tmp.begin() + 1, tmp.end());
    int n = tmp.size();
    for (cd& x : tmp)
        x /= n;
    ans.resize(n);
    for (int i = 0; i < n; i++) {
        //cout << a[i] << ' ';
        ans[i] += (tmp[i].real() + 0.5);
    }

    int ma = ans[m - 1], res = 0;
    for (int i = m; i < 2 * m - 1; i++) 
    {
        //cout << ans[i] << ' ';
        if (ans[i] + ans[i - m] > ma) {
            ma = ans[i] + ans[i - m];
            res = i - m + 1;
        }
    }
    //cout << '\n';
    cout << ma << ' ' << res;
}

