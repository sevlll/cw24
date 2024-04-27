#include "testlib.h"
#include <numeric>

using namespace std;

const int N = 200'500;
const int A = 1'000'000'000;
int w[N], par[N];
vector<int> stacks[N];

signed main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = opt<int>(1);
    int sA = opt<int>(2);
    int vA = opt<int>(3);
    int inc = opt<int>(4);
    int spoil = opt<int>(5);
    int wnx = opt<int>(6);
    int gg = opt<int>(7);

    for (int v = 2; v <= n; v++) {
        stacks[v] = {rnd.next(0, vA)};
        int parent = 1 + rnd.wnext(2, wnx);
        if (v == 2) parent = 1;
        par[v] = parent;
        stacks[parent].push_back(rnd.next(0, sA));
        w[v] = max(1, min(A, -rnd.next(0, inc) + stacks[v].back() + stacks[parent].back()));
    }
    shuffle(stacks[1].begin(), stacks[1].end());
    shuffle(stacks[2].begin(), stacks[2].end());

    for (int _ = 0; _ < spoil; _++) {
        w[rnd.next(3, n)] = rnd.next(1, A);
    }

    println(n, gg);
    for (int i = 2; i <= n; i++) {
        println(par[i], i, w[i]);
    }
    for (int v = 1; v <= n; v++) {
        println(stacks[v]);
    }

    return 0;
}
