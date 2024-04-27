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

void solve_g5() {
    input();

    for (int v = 1; v <= n; v++) {
        reverse(all(stacks[v]));
    }

    vector<bool> deleted(n, false);
    vector<int> ans;

    for (int _ = 0; _ < n - 1; _++) {
        int nxt = -1;
        for (int i = 1; i < n; i++) {
            if (deleted[i]) continue;
            if (stacks[edges[i].a].back() + stacks[edges[i].b].back() >= edges[i].w) {
                nxt = i;
                break;
            }
        }
        if (nxt == -1) {
            cout << "No\n";
            return;
        }
        ans.pb(nxt);
        stacks[edges[nxt].a].pop_back();
        stacks[edges[nxt].b].pop_back();
        deleted[nxt] = true;
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
    solve_g5();
}
