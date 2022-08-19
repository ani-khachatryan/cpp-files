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

const int N = 6e6 + 30;
const ld pi = acos(-1);
const int T = 238;
const ld e = 1e-13;

int n;
int a[N];
vcd b, c;
cd roots[N];
int rev[N];
vii ans;

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
void inv(vcd& a)
{
    fft(a);
    reverse(a.begin() + 1, a.end());
    for (cd& x : a)
        x /= a.size();
}
void mult(vcd& a, vcd& b)
{
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
    ld sector = 2. * pi / n;
    for (int i = 0; i < n; ++i) {
        roots[i] = cd(cos(sector * i), sin(sector * i));
    }
    fft(a); fft(b);
    //cout << "DD" << endl;
    for (int i = 0; i < n; ++i)
        a[i] *= b[i];
    inv(a);
    for (int i = 0; i < n; i++) {
        ans.push_back(a[i].real() + 0.5);
    }
}

int main() {
    string x, y;
    cin >> x >> y;
    int signb = 1, signc = 1;
    for (int i = (int)x.size() - 1; i >= 0; i--)
        if (x[i] != '-') {
            b.push_back(x[i] - '0');
        }
        else signb = 0;
    for (int i = (int)y.size() - 1; i >= 0; i--)
        if(y[i] != '-') {
            c.push_back(y[i] - '0');
        }
        else signc = 0;
    mult(b, c);
    int carry = 0;
    for (int i = 0; i < ans.size(); i++) {
        ans[i] += carry;
        carry = ans[i] / 10;
        ans[i] %= 10;
    }
    while (carry != 0) {
        ans.push_back(carry % 10);
        carry /= 10;
    }
    while (ans.size() >= 2 && ans.back() == 0) {
        ans.pop_back();
    }
    reverse(ans.begin(), ans.end());
    if (ans.size() == 1 && ans.back() == 0) {
        cout << 0;
        return 0;
    } 
    if (signb != signc)
        cout << '-';
    for (auto x : ans) {
        cout << x;
    }
}
