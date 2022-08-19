#include <iostream>
using namespace std;
using ll = long long;
const int maxn = 3 * 10'002;
const int maxq = 100'002;
ll inf = maxn * 1LL * maxq;

int nxt;
int root;
struct Node {
    ll val = inf;
    int height = 0;
    int lson = 0, rson = 0;
    int sz = 0;
    ll sum = 0;
    ll first = -inf, last = inf;
    int decrsuff = 0, incrpref = 0;
    int decrpref = 0, incrsuff = 0;
    bool rev = false;
    ll add = inf, assign = inf;

    void assign_val(ll x) {
        rev = 0;
        add = inf;
        assign = x;
    }

    void add_val(ll x) {
        if (assign != inf)
            assign += x;
        else
            add = (add == inf) ? x : add + x;
    }

    void rvrs() {
        if (assign == inf)
            rev ^= 1;
    }

    void update_node() {
        if (val == inf) return;
        if (rev) {
            swap(decrsuff, incrpref);
            swap(decrpref, incrsuff);
            swap(rson, lson);
            swap(first, last);
        }
        if (assign != inf) {
            val = assign;
            sum = assign * sz;
            first = last = assign;
            incrpref = decrsuff = decrpref = incrsuff = sz;
        }
        if (add != inf) {
            val += add;
            sum += add * sz;
            first += add;
            last += add;
        }
    }
} avl[maxq + maxn];

int make_node(ll x) {
    avl[++nxt].val = x;
    avl[nxt].sum = avl[nxt].first = avl[nxt].last = x;
    avl[nxt].height = avl[nxt].sz = avl[nxt].decrsuff = avl[nxt].incrpref = avl[nxt].decrpref = avl[nxt].incrsuff = 1;
    return nxt;
}

void push(int a) {
    if (!a) return;
    avl[a].update_node();
    if (avl[a].lson) {
        if (avl[a].rev) avl[avl[a].lson].rvrs();
        if (avl[a].add != inf) avl[avl[a].lson].add_val(avl[a].add);
        if (avl[a].assign != inf) avl[avl[a].lson].assign_val(avl[a].assign);
    }
    if (avl[a].rson) {
        if (avl[a].rev) avl[avl[a].rson].rvrs();
        if (avl[a].add != inf) avl[avl[a].rson].add_val(avl[a].add);
        if (avl[a].assign != inf) avl[avl[a].rson].assign_val(avl[a].assign);
    }
    avl[a].add = avl[a].assign = inf;
    avl[a].rev = 0;
}

void recalc(int a) {
    if (!a) return;
    int lson = avl[a].lson;
    int rson = avl[a].rson;
    push(lson);
    push(rson);
    avl[a].height = max(avl[lson].height, avl[rson].height) + 1;
    avl[a].sz = avl[lson].sz + avl[rson].sz + 1;
    avl[a].sum = avl[lson].sum + avl[rson].sum + avl[a].val;

    avl[a].incrpref = avl[lson].incrpref;
    avl[a].decrsuff = avl[rson].decrsuff;
    if (avl[a].decrsuff == avl[rson].sz && (avl[a].val >= avl[rson].first || !rson)) {
        ++avl[a].decrsuff;
        if (avl[lson].last >= avl[a].val)
            avl[a].decrsuff += avl[lson].decrsuff;
    }
    if (avl[a].incrpref == avl[lson].sz && (avl[lson].last <= avl[a].val || !lson)) {
        ++avl[a].incrpref;
        if (avl[a].val <= avl[rson].first)
            avl[a].incrpref += avl[rson].incrpref;
    }

    avl[a].incrsuff = avl[rson].incrsuff;
    avl[a].decrpref = avl[lson].decrpref;
    if (avl[a].incrsuff == avl[rson].sz && (avl[a].val <= avl[rson].first || !rson)) {
        ++avl[a].incrsuff;
        if (avl[lson].last <= avl[a].val)
            avl[a].incrsuff += avl[lson].incrsuff;
    }
    if (avl[a].decrpref == avl[lson].sz && (avl[lson].last >= avl[a].val || !lson)) {
        ++avl[a].decrpref;
        if (avl[a].val >= avl[rson].first)
            avl[a].decrpref += avl[rson].decrpref;
    }
    if (!lson && !rson) {
        avl[a].incrsuff = avl[a].incrpref = avl[a].decrpref = avl[a].decrsuff = 1;
    }
    avl[a].last = avl[a].first = avl[a].val;
    if (lson) {
        avl[a].first = avl[lson].first;
    }
    if (rson) {
        avl[a].last = avl[rson].last;
    }
}

void newsons(int x, int a, int b) {
    if (!x) return;
    push(x);
    avl[x].lson = a;
    avl[x].rson = b;
    recalc(x);
}

void rotate_left(int b, int a) {
    push(a);
    push(b);
    int al = avl[a].lson;
    int bl = avl[b].lson;
    int br = avl[b].rson;
    newsons(a, al, bl);
    newsons(b, a, br);
}

void rotate_right(int b, int a) {
    push(a);
    push(b);
    int ar = avl[a].rson;
    int bl = avl[b].lson;
    int br = avl[b].rson;
    newsons(a, br, ar);
    newsons(b, bl, a);
}

int balance(int r) {
    if (!r) return r;
    int a = avl[r].lson;
    int b = avl[r].rson;
    push(r);
    push(a);
    push(b);
    if (avl[a].height + 2 == avl[b].height) {
        int c = avl[b].lson;
        int d = avl[b].rson;
        if (avl[c].height == avl[d].height + 1) {
            rotate_right(c, b);
            rotate_left(c, r);
            return c;
        }
        else {
            rotate_left(b, r);
            return b;
        }
    }
    else if (avl[b].height == avl[a].height + 2) {
        int c = avl[b].rson;
        int d = avl[b].lson;
        if (avl[c].height + 1 == avl[d].height) {
            rotate_left(c, b);
            rotate_right(c, r);
            return c;
        }
        else {
            rotate_right(b, r);
            return b;
        }
    }
    return r;
}

int merge_normal(int a, int x, int b) {
    push(a); push(x); push(b);
    if (avl[a].height > avl[b].height + 1) {
        int r = merge_normal(avl[a].rson, x, b);
        newsons(a, avl[a].lson, r);
        a = balance(a);
        return a;
    }
    newsons(x, a, b);
    x = balance(x);
    return x;
}

int merge_reverse(int a, int x, int b) {
    push(a); push(x); push(b);
    if (avl[b].height > avl[a].height + 1) {
        int r = merge_reverse(a, x, avl[b].lson);
        newsons(b, r, avl[b].rson);
        b = balance(b);
        return b;
    }
    newsons(x, a, b);
    x = balance(x);
    return x;
}

int merge(int a, int b, int c) {
    if (avl[a].height >= avl[c].height) {
        return merge_normal(a, b, c);
    }
    return merge_reverse(a, b, c);
}

pair<int, int> split(int a, int x) {
    if (a == 0 || x == 0) {
        return make_pair(0, a);
    }
    push(a);
    pair<int, int> ans(0, 0);
    if (avl[avl[a].lson].sz < x) {
        ans = split(avl[a].rson, x - (avl[avl[a].lson].sz + 1));
        ans.first = merge(avl[a].lson, a, ans.first);
        return ans;
    }
    ans = split(avl[a].lson, x);
    ans.second = merge(ans.second, a, avl[a].rson);
    return ans;
}

int merge(int a, int b) {
    push(a); push(b);
    if (a == 0) return b;
    if (b == 0) return a;
    auto k = split(a, avl[a].sz - 1);
    return merge(k.first, k.second, b);
}

void insert(int pos, ll x) {
    int i = make_node(x);
    auto a = split(root, pos - 1);
    root = merge(a.first, i, a.second);
}

void del(int pos) {
    auto a = split(root, pos - 1);
    auto b = split(a.second, 1);
    root = merge(a.first, b.second);
}

ll sum(int l, int r) {
    auto a = split(root, l - 1);
    auto b = split(a.second, r - l + 1);
    push(b.first);
    ll ans = avl[b.first].sum;
    b.first = merge(b.first, b.second);
    root = merge(a.first, b.first);
    return ans;
}

int pos_of_greater(int a, int x) {
    push(a); push(avl[a].rson); push(avl[a].lson);
    if (avl[a].rson && avl[avl[a].rson].first > x)
        return avl[avl[a].lson].sz + 1 + pos_of_greater(avl[a].rson, x);
    if (avl[a].val > x) return avl[avl[a].lson].sz + 1;
    return pos_of_greater(avl[a].lson, x);
}

int pos_of_smaller(int a, int x) {
    int lson = avl[a].lson;
    int rson = avl[a].rson;
    push(a); push(rson); push(lson);
    if (rson && avl[rson].first < x) {
        return avl[lson].sz + 1 + pos_of_smaller(rson, x);
    }
    if (avl[a].val < x) return avl[lson].sz + 1;
    return pos_of_smaller(lson, x);
}

void next_permutation(int l, int r) {
    auto a = split(root, l - 1);
    auto b = split(a.second, r - l + 1);
    int k = b.first;
    push(k);
    if (avl[k].decrsuff == avl[k].sz) {
        avl[k].rvrs();
        k = merge(k, b.second);
        root = merge(a.first, k);
        return;
    }
    auto s = split(k, avl[k].sz - avl[k].decrsuff);
    auto e = split(s.first, avl[s.first].sz - 1);
    int p = pos_of_greater(s.second, avl[e.second].val);

    auto t = split(s.second, p - 1);
    auto m = split(t.second, 1);
    root = merge(t.first, e.second, m.second);
    avl[root].rvrs();
    root = merge(root, b.second);

    root = merge(merge(a.first, e.first), m.first, root);
}

void prev_permutation(int l, int r) {
    auto a = split(root, l - 1);
    auto b = split(a.second, r - l + 1);
    int k = b.first;
    push(k);
    if (avl[k].incrsuff == avl[k].sz) {
        avl[k].rvrs();
        k = merge(k, b.second);
        root = merge(a.first, k);
        return;
    }
    auto s = split(k, avl[k].sz - avl[k].incrsuff);
    auto e = split(s.first, avl[s.first].sz - 1);
    int p = pos_of_smaller(s.second, avl[e.second].val);
    auto t = split(s.second, p - 1);
    auto m = split(t.second, 1);

    root = merge(t.first, e.second, m.second);
    avl[root].rvrs();

    root = merge(root, b.second);

    root = merge(merge(a.first, e.first), m.first, root);
}

void print(int a) {
    if (!a) return;
    push(a);
    print(avl[a].lson);
    cout << avl[a].val << ' ';
    print(avl[a].rson);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        insert(i + 1, x);
    }
    int q;
    cin >> q;
    while (q--) {
        int id;
        cin >> id;
        if (id == 1) {
            int l, r;
            cin >> l >> r;
            ++l; ++r;
            cout << sum(l, r) << '\n';
        }
        if (id == 2) {
            ll x; int pos;
            cin >> x >> pos;
            ++pos;
            insert(pos, x);
        }
        if (id == 3) {
            int pos;
            cin >> pos;
            ++pos;
            del(pos);
        }
        if (id == 4) {
            ll x; int l, r;
            cin >> x >> l >> r;
            ++l; ++r;
            auto a = split(root, l - 1);
            auto b = split(a.second, r - l + 1);
            avl[b.first].assign_val(x);
            a.second = merge(b.first, b.second);
            root = merge(a.first, a.second);
        }
        if (id == 5) {
            ll x; int l, r;
            cin >> x >> l >> r;
            ++l; ++r;
            auto a = split(root, l - 1);
            auto b = split(a.second, r - l + 1);
            avl[b.first].add_val(x);
            a.second = merge(b.first, b.second);
            root = merge(a.first, a.second);
        }
        if (id == 6) {
            int l, r;
            cin >> l >> r;
            ++l; ++r;
            next_permutation(l, r);
        }
        if (id == 7) {
            int l, r;
            cin >> l >> r;
            ++l; ++r;
            prev_permutation(l, r);
        }
    }
   /*while (avl[root].sz) {
        auto a = split(root, 1);
        push(a.first);
        cout << avl[a.first].val << ' ';
        root = a.second;
    }*/
    print(root);
}

