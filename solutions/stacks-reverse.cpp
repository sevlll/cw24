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
        reverse(all(stacks[v]));
    }
}

void solve_full() {
    input();
    deque<int> q = {1};
    vector<int> order, par(n + 1), ind(n + 1);
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        order.pb(v);
        for (auto i : g[v]) {
            auto &[a, b, w] = edges[i];
            int u = a ^ b ^ v;
            if (u == par[v]) continue;
            ind[u] = i;
            par[u] = v;
            q.pb(u);
        }
    }
    reverse(all(order));
    vector<vector<int>> match(n + 1);
    for (int v = 1; v <= n; v++) {
        match[v].assign(sz[v], -1);
    }
    vector<set<array<int, 2>>> rest_nums(n + 1);
    for (int v = 1; v <= n; v++) {
        for (int i = 0; i < (int) stacks[v].size(); i++) {
            rest_nums[v].insert({stacks[v][i], i});
        }
    }
    for (int i = 0; i < n - 1; i++) {
        int v = order[i];
        int u = par[v];
        int edge_id = ind[v];
        int w = edges[edge_id].w;
        assert(rest_nums[v].size() == 1);
        int vi = (*rest_nums[v].begin())[1];
        rest_nums[v].erase(rest_nums[v].begin());
        assert(!rest_nums[u].empty());
        if ((*rest_nums[u].rbegin())[0] < w - stacks[v][vi]) {
            cout << "No\n";
            return;
        }
        int ui = (*rest_nums[u].lower_bound({w - stacks[v][vi], -1}))[1];
        rest_nums[u].erase({stacks[u][ui], ui});
        match[v][vi] = match[u][ui] = edge_id;
    }
    vector<int> edge_cnt(n), process, pt(n + 1);
    for (int v = 1; v <= n; v++) {
        int edge_id = match[v][pt[v]];
        pt[v]++;
        if (edge_cnt[edge_id] == 1) {
            process.pb(edge_id);
        }
        edge_cnt[edge_id] ^= 1;
    }
    vector<int> ans;
    for (int _ = 0; _ < n - 1; _++) {
        assert(!process.empty());
        int edge_id = process.back();
        process.pop_back();
        ans.pb(edge_id);
        auto[a, b, __] = edges[edge_id];
        for (auto v : {a, b}) {
            assert(pt[v] <= sz[v]);
            if (pt[v] == sz[v]) continue;
            int next_edge_id = match[v][pt[v]];
            pt[v]++;
            if (edge_cnt[next_edge_id] == 1) {
                process.pb(next_edge_id);
            }
            edge_cnt[next_edge_id] ^= 1;
        }
    }
    cout << "Yes\n";
    for (auto x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve_full();
}
