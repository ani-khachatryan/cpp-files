#include <iostream>
using namespace std;
using ll = long long;
const int maxn = 3 * 10'002;
const int maxq = 100'002;
const ll inf = maxn * 1LL * maxq;

int nxt;
int root;
struct query {
    bool rev = false;
    ll add = inf, assign = inf;
};
struct node {
    int val;
    int height;
    int lson, rson;
    int sz;
    // ll sum;
    // int dsuf;
    // int isuf;
    // bool p = false;
    // query q;
} avl[maxq + maxn];

int make_node(int x) {
    avl[++nxt].val = x;
    avl[nxt].height = avl[nxt].sz = 1;
    return nxt;
}

void newsons(int x, int a, int b) {
    //cout << "newsons " << x << ' ' << a << ' ' << b << '\n';
    avl[x].lson = a;
    avl[x].rson = b;
    avl[x].height = max(avl[a].height, avl[b].height) + 1;
    avl[x].sz = avl[a].sz + avl[b].sz + 1;
}

void rotate_left(int b, int a) {
    int al = avl[a].lson;
    int bl = avl[b].lson;
    int br = avl[b].rson;
    newsons(a, al, bl);
    newsons(b, a, br);
}

void rotate_right(int b, int a) {
    int ar = avl[a].rson;
    int bl = avl[b].lson;
    int br = avl[b].rson;
    newsons(a, br, ar);
    newsons(b, bl, a);
}

int balance(int r) {
    int a = avl[r].lson;
    int b = avl[r].rson;
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
    } else if (avl[b].height == avl[a].height + 2) {
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

int merge(int a, int x, int b) {
    if (avl[a].height > avl[b].height + 1) {
        int r = merge(avl[a].rson, x, b);
        newsons(a, avl[a].lson, r);
        a = balance(a);
        return a;
    }
    newsons(x, a, b);
    x = balance(x);
    return x;
}


//string tab = "";
pair<int, int> split(int a, int x) {
    //cout << tab << "split(" << x << ", " << x << ")\n";
    //if (tab.size() < 100)
    //tab += "  ";
    if (a == 0 || x == 0) {
    //    if(tab.size())tab.pop_back(),tab.pop_back();
        return make_pair(0, a);
    }
    pair<int, int> ans(0, 0);
    if (avl[avl[a].lson].sz < x) {
        //cout << avl[a].rson << '\n';
        ans = split(avl[a].rson, x - (avl[avl[a].lson].sz + 1));
        ans.first = merge(avl[a].lson, a, ans.first);
        //cout << a << ":: " << ans.first << " | sz = " << avl[ans.first].sz << '\n';
    //    if(tab.size())tab.pop_back(),tab.pop_back();
        return ans;
    }
    ans = split(avl[a].lson, x);
    ans.second = merge(ans.second, a, avl[a].rson);
    //if(tab.size())tab.pop_back(),tab.pop_back();
    return ans;
}

int merge(int a, int b) {
    auto k = split(a, avl[a].sz - 1);
    //cout << "merge(" << k.first << "->" << k.second << "<-" << b << ")\n";
    return merge(k.first, k.second, b);
}

void insert(int pos, ll x) {
    //cout << "insert(" << pos << ", " << x << ')' << '\n';
    int i = make_node(x);
    auto a = split(root, pos - 1);
    root = merge(a.first, i, a.second);
}
void del(int pos) {
    auto a = split(root, pos - 1);
    auto b = split(a.second, 1);
    root = merge(a.first, b.second);
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        insert(i, i);
    //for (int i = 1; i <= n; i++)
    //        cout << avl[i].sz << '\n';
    //cout << "--------------------\n";    
    while(m--) {
        int l, r;
        cin >> l >> r;
        auto k = split(root, l - 1);
        auto p = split(k.second, r - l + 1);
    //    cout << "SPLITTED " << l << ".." << r << '\n';
        //for (int i = 1; i <= n; i++)
        //    cout << avl[i].lson << ' ' << avl[i].rson << '\n';
        //cout << m << ' ';
        //cout << p.first << ' ' << k.first;
    //    cout << "MERGE DEMI ERKUSY\n";
        int g = merge(p.first, k.first);
    //    for (int i = 1; i <= n; i++)
    //        cout << avl[i].lson << ' ' << avl[i].rson << '\n';
        root = merge(g, p.second);
    //    cout << "FINAL MERGE\n";
    //    for (int i = 1; i <= n; i++)
    //        cout << avl[i].lson << ' ' << avl[i].rson << '\n';
    //    cout << "done\n";
    }
    //for (int i = 1; i <= n; i++)
    //    cout << avl[i].sz << ' ';
    //cout << '\n';
    //cout << "root " << avl[root].val << ' ' << avl[root].sz << '\n';
    for (int i = 1; i <= n; i++) {
        auto k = split(root, 1);
        root = k.second;
        //cout << "sz " << avl[root].sz << '\n';
        cout << avl[k.first].val << ' ';
    }
}
// int sum(int l, int r) {
//     auto a = split(root, l - 1);
//     auto b = split(a.second, r);
//     push(b.first);
//     int ans = t.sum;
//     b.first = merge(b.first, b.second);
//     root = merge(a.first, b.first);
//     return t.sum;
// }

// // void assign(int l, int r, ll x) {
// //     split(root, l - 1);
// //     t = split(avlr, r);//t, zibil
// //     p = 1;
// //     t.q.rev = 0;
// //     t.q.add = 0;
// //     t.q.assign = x;
// //     root = merge(avll, merge(t, zibil));
// // }

// // void add(int l, int r, ll x) {
// //     split(root, l - 1);//avll avlr
// //     split(avlr, r);//t, zibil
// //     if (p == 0) {
// //         p = 1;
// //         t.q.add = x;
// //         return;
// //     }
// //     if (t.q.assign != inf)
// //         t.q.assign += x;
// //     else t.q.add += x;
// // }

// void next_permutation(int l, int r) {
//     auto a = split(root, l - 1);//a.l a.r
//     auto b = split(a.r, r);//t - b.l, b.r

// }

// void prev_permutation(int l, int r) {

// }
