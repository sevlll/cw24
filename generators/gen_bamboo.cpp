#include "testlib.h"
#include <numeric>
#include <deque>

using namespace std;

const int N = 200'500;
const int A = 1'000'000'000;
vector<int> g[N], stacks[N];
int deg[N];

struct edge {
    int a = 0, b = 0, w = 0;

    edge() = default;

    edge(int a_, int b_, int w_) {
        a = a_;
        b = b_;
        w = w_;
    }
};

edge edges[N];
int par[N], ind[N];


vector<int> order_from_bottom() {
    deque<int> q = {1};
    vector<int> order;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        order.push_back(v);
        for (auto i : g[v]) {
            auto[a, b, w] = edges[i];
            int u = a ^ b ^ v;
            if (u == par[v]) continue;
            ind[u] = i;
            par[u] = v;
            q.push_back(u);
        }
    }
    reverse(order.begin(), order.end());
    order.pop_back();
    return order;
}


signed main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = opt<int>(1);
    int fails = opt<int>(2);
    int inc = opt<int>(3);
    int gg = opt<int>(4);

    for (int i = 2; i <= n; i++) {
        int w = rnd.next(1, A);
        edges[i - 1] = (edge) {i - 1, i, w};
    }

    for (int i = 1; i <= n - 1; i++) {
        auto[a, b, _] = edges[i];
        g[a].push_back(i);
        g[b].push_back(i);
        deg[a]++;
        deg[b]++;
    }

    for (int v = 1; v <= n; v++) {
        stacks[v].resize(deg[v]);
    }

    vector<int> order = order_from_bottom();

    vector<vector<int>> rest_nums(n + 1);
    vector<int> pt(n + 1);
    for (int v = 1; v <= n; v++) {
        for (int i = 0; i < (int) stacks[v].size(); i++) {
            rest_nums[v].push_back(i);
        }
        shuffle(rest_nums[v].begin(), rest_nums[v].end());
    }
    for (auto v : order) {
        int u = par[v];
        int edge_id = ind[v];
        int weight = edges[edge_id].w;
        int vi = rest_nums[v][pt[v]++];
        int ui = rest_nums[u][pt[u]++];

        int cA = rnd.next(0, weight);
        int cB = weight - cA;

        if (edge_id <= fails) {
            cB -= rnd.next(0, inc);
        } else {
            cB += rnd.next(0, inc);
        }

        cA = max(0, min(A, cA));
        cB = max(0, min(A, cB));

        stacks[v][vi] = cA;
        stacks[u][ui] = cB;
    }

    println(n, gg);

    for (int i = 1; i <= n - 1; i++) {
        auto[a, b, w] = edges[i];
        println(a, b, w);
    }

    for (int i = 1; i <= n; i++) {
        println(stacks[i]);
    }


    return 0;
}
