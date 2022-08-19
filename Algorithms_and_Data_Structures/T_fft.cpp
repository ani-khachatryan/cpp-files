#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <complex>
#include <string>
#define ld long double
#define cd complex<long double>
#define vcd vector<cd>
#define vii vector<int>
using namespace std;
using ll = long long;

const int maxn = 2 * 131072;
const ld pi = acos(-1);

cd roots[maxn];
int rev[maxn];

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
void mult(vii& a_)
{
    vcd a(a_.size());
    for (size_t i = 0; i < a_.size(); ++i) {
        a[i] = a_[i];
    }
    int n = 1, h = 0;
    while (n < a.size() + a.size())
        n *= 2, ++h;
    while (a.size() < n)
        a.push_back(0);

    rev[0] = 0;
    for (int i = 1, high = -1; i < n; ++i) {
        high += !(i & (i - 1));
        rev[i] = rev[i ^ (1 << high)] | (1 << (h - high - 1));
    }
    ld sector = 2. * pi / n;
    for (int i = 0; i < n; ++i) {
        roots[i] = cd(cos(sector * i), sin(sector * i));
    }
    fft(a);
    for (int i = 0; i < n; ++i)
        a[i] *= a[i];

    fft(a);
    reverse(a.begin() + 1, a.end());
    for (cd& x : a)
        x /= n;
    a_.clear();
    for (int i = 0; i < n; i++) {
        //cout << a[i] << ' ';
        a_.push_back(a[i].real() + 0.5);
    }
    //cout << "\n\n";
}

int main() {
    string a;
    cin >> a;
    vii a_(a.size());
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == '1') {
            a_[i] = 1;
        } else {
            a_[i] = 0;
        }
    }
    mult(a_);
    ll res = 0;
    for (int i = 0; i < a_.size(); i++) 
    {
        if (a_[i] % 2 == 1) {
            res += a_[i] / 2;
        }
    }
    //cout << '\n';
    cout << res << '\n';
}
