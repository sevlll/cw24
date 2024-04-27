#include "testlib.h"
#include <numeric>

using namespace std;

const int N = 200'500;
const int A = 1'000'000'000;
int w[N]; // w[i] --- weight of edge between 1 and i
vector<int> stacks[N];

signed main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int n = opt<int>(1);
    int sA = opt<int>(2);
    int vA = opt<int>(3);
    int inc = opt<int>(4);
    int spoil = opt<int>(5);
    int gg = opt<int>(6);

    for (int v = 2; v <= n; v++) {
        stacks[v] = {rnd.next(0, vA)};
        stacks[1].push_back(rnd.next(0, sA));
        w[v] = max(1, min(A, -rnd.next(0, inc) + stacks[v].back() + stacks[1].back()));
    }
    shuffle(stacks[1].begin(), stacks[1].end());

    for (int _ = 0; _ < spoil; _++) {
        w[rnd.next(2, n)] = rnd.next(1, A);
    }

    println(n, gg);
    for (int i = 2; i <= n; i++) {
        println(1, i, w[i]);
    }
    for (int v = 1; v <= n; v++) {
        println(stacks[v]);
    }

    return 0;
}
