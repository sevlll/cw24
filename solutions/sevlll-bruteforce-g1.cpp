#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back

struct edge {
    int a = 0, b = 0, w = 0;

    edge() = default;

    edge(int a_, int b_, int w_) {
        a = a_;
        b = b_;
        w = w_;
    }
};

const int N = 200500;
const int INF = (int) 3e9;
int n;
edge edges[N];
int sz[N];
vector<int> g[N], stacks[N];

void input() {
    int __;
    cin >> n >> __;
    for (int i = 1; i < n; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = (edge) {a, b, w};
        g[a].pb(i);
        g[b].pb(i);
    }
    for (int v = 1; v <= n; v++) {
        sz[v] = (int) g[v].size();
        stacks[v].assign(sz[v], 0);
        for (int i = 0; i < sz[v]; i++) {
            cin >> stacks[v][i];
        }
    }
}

void solve_brute() {
    input();

    while (n >= 12) {}
    // to make sure n! first int32, to get TL for all big cases

    vector<int> order(n - 1);
    iota(all(order), 1);
    int fct = 1;
    for (int x = 1; x <= n - 1; x++) fct *= x;

    for (int _ = 0; _ < fct; _++) {
        next_permutation(all(order));
        vector<int> pt(n + 1);
        bool ban = false;
        for (auto i : order) {
            int val = stacks[edges[i].a][pt[edges[i].a]] + stacks[edges[i].b][pt[edges[i].b]];
            pt[edges[i].a]++;
            pt[edges[i].b]++;
            if (val < edges[i].w) {
                ban = true;
                break;
            }
        }
        if (!ban) {
            cout << "Yes\n";
            reverse(all(order));
            for (auto i : order) {
                cout << i << ' ';
            }
            cout << '\n';
            return;
        }
    }
    cout << "No\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve_brute();
}
