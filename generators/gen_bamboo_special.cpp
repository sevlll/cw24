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

signed main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = opt<int>(1);
    int inc = opt<int>(2);
    int swaps = opt<int>(3);
    bool rev = opt<int>(4);
    int gg = opt<int>(5);

    int bigL = A / 10;
    int bigR = 9 * bigL;

    int smallL = 1;
    int smallR = A / 10;

    for (int i = 2; i <= n; i++) {
        edges[i - 1] = (edge) {i - 1, i, 0};
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

    stacks[1][0] = rnd.next(smallL, smallR);

    for (int v = 2; v <= n - 1; v++) {
        stacks[v][0] = rnd.next(bigL, bigR);
        stacks[v][1] = rnd.next(smallL, smallR);
    }

    stacks[n][0] = rnd.next(bigL, bigR);

    for (int i = 1; i <= n - 1; i++) {
        int s1 = stacks[i][1 - (i == 1)], b1 = stacks[i + 1][0];
        edges[i].w = min(A, max(1, s1 + b1 - rnd.next(0, inc)));
    }

    for (int _ = 0; _ < swaps; _++) {
        int i = rnd.next(2, n - 1);
        swap(stacks[i][0], stacks[i][1]);
    }

    if (rev) {
        for (int v = 1; v <= n; v++) {
            reverse(stacks[v].begin(), stacks[v].end());
        }
    }

    println(n, gg);
    for (int i = 1; i <= n - 1; i++) {
        println(edges[i].a, edges[i].b, edges[i].w);
    }
    for (int v = 1; v <= n; v++) {
        println(stacks[v]);
    }

    return 0;
}
