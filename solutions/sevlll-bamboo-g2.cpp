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

void solve_bamboo() {
    input();
    stacks[1].pb(-INF);
    stacks[n].pb(-INF);
    vector<array<bool, 2>> dp(n + 1);
    dp[1][1] = true;
    for (int i = 2; i <= n; i++) {
        if (dp[i - 1][1] && stacks[i - 1][0] + stacks[i][0] >= edges[i - 1].w) {
            dp[i][0] = true;
        }
        if (dp[i - 1][0] && stacks[i - 1][1] + stacks[i][0] >= edges[i - 1].w) {
            dp[i][0] = true;
        }
        if (dp[i - 1][1] && stacks[i - 1][0] + stacks[i][1] >= edges[i - 1].w) {
            dp[i][1] = true;
        }
        if (dp[i - 1][0] && stacks[i - 1][1] + stacks[i][1] >= edges[i - 1].w) {
            dp[i][1] = true;
        }
    }
    if (!dp[n][0]) {
        cout << "No\n";
        return;
    }
    int cur = 0;
    vector<int> t00, t01, t10, t11;
    for (int i = n; i >= 2; i--) {
        if (dp[i - 1][1] && stacks[i - 1][0] + stacks[i][cur] >= edges[i - 1].w) {
            if (cur == 0) {
                t00.pb(i - 1);
            } else {
                t01.pb(i - 1);
            }
            cur = 1;
        } else {
            if (cur == 0) {
                t10.pb(i - 1);
            } else {
                t11.pb(i - 1);
            }
            cur = 0;
        }
    }
    reverse(all(t01));

    cout << "Yes\n";
    for (auto x : t11) {
        cout << x << ' ';
    }
    for (auto x : t01) {
        cout << x << ' ';
    }
    for (auto x : t10) {
        cout << x << ' ';
    }
    for (auto x : t00) {
        cout << x << ' ';
    }
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve_bamboo();
}
