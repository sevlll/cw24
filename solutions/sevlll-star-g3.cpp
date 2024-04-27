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

void solve_star() {
    input();
    vector<pair<int, int>> order1, order2;
    for (int i = 2; i <= n; i++) {
        order1.pb({edges[i - 1].w - stacks[i][0], i});
    }
    for (int i = 0; i < n - 1; i++) {
        order2.pb({stacks[1][i], i});
    }
    sort(all(order1));
    sort(all(order2));
    vector<int> ans(n - 1);
    for (int i = 0; i < n - 1; i++) {
        if (order1[i].first - order2[i].first > 0) {
            cout << "No\n";
            return;
        }
        ans[order2[i].second] = order1[i].second - 1;
    }
    reverse(all(ans));
    cout << "Yes\n";
    for (auto x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve_star();
}
