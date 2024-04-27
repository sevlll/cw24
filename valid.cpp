#include "testlib.h"

using namespace std;

const int MAXN = 200'000;
const int C = 1'000'000'000;

int a[MAXN + 7], b[MAXN + 7], w[MAXN + 7];
int deg[MAXN + 7];
vector<int> c[MAXN + 7], g[MAXN + 7];

const int limN[10] = {MAXN, 10, MAXN, MAXN, MAXN, 1000, 1000, MAXN, 1000, MAXN};

int group;
int n;

bool check_tree() {
    vector<bool> used(n + 1, false);
    used[1] = true;
    vector<int> s = {1};
    while (!s.empty()) {
        int v = s.back();
        s.pop_back();
        for (auto u:g[v]) {
            if (used[u])continue;
            used[u] = true;
            s.push_back(u);
        }
    }
    for (int v = 1; v <= n; v++) {
        if (!used[v]) {
            return false;
        }
    }
    return true;
}

bool check_g2() {
    for (int i = 1; i <= n - 1; i++) {
        if (a[i] != i) {
            return false;
        }
        if (b[i] != i + 1) {
            return false;
        }
    }
    return true;
}

bool check_g3() {
    for (int i = 1; i <= n - 1; i++) {
        if (a[i] != 1) {
            return false;
        }
        if (b[i] != i + 1) {
            return false;
        }
    }
    return true;
}

bool check_g4() {
    for (int i = 1; i <= n - 1; i++) {
        if (a[i] > 2) {
            return false;
        }
        if (b[i] != i + 1) {
            return false;
        }
    }
    return true;
}

bool check_g5() {
    for (int v = 1; v <= n; v++) {
        if (!is_sorted(c[v].begin(), c[v].end())) {
            return false;
        }
    }
    return true;
}

bool check_g6() {
    for (int v = 1; v <= n; v++) {
        for (int j = 1; j < deg[v]; j++) {
            if (c[v][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool check_g7() {
    long long csum = 0, wsum = 0;
    for (int v = 1; v <= n; v++) {
        for (int j = 0; j < deg[v]; j++) {
            csum += (long long) c[v][j];
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        wsum += (long long) w[i];
    }
    if (csum != wsum) {
        return false;
    }
    return true;
}

signed main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    group = validator.group().empty() ? 0 : atoi(validator.group().c_str());

    n = inf.readInt(2, limN[group], "n");
    inf.readSpace();
    int group_input = inf.readInt(0, 9, "group_input");
    ensuref(group_input == group, "Wrong group of tests in input!\n");
    inf.readEoln();

    for (int i = 1; i <= n - 1; i++) {
        a[i] = inf.readInt(1, n, "a_i");
        inf.readSpace();
        b[i] = inf.readInt(1, n, "b_i");
        inf.readSpace();
        w[i] = inf.readInt(1, C, "w_i");
        inf.readEoln();
    }

    for (int i = 1; i <= n - 1; i++) {
        g[a[i]].push_back(b[i]);
        g[b[i]].push_back(a[i]);
        deg[a[i]]++;
        deg[b[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        c[i] = inf.readInts(deg[i], 0, C, "c_{i, j}");
        inf.readEoln();
    }

    ensuref(check_tree(), "Given graph is not a tree!\n");

    if (group == 2) {
        ensuref(check_g2(), "Not a bamboo!\n");
    }

    if (group == 3) {
        ensuref(check_g3(), "Not a star!\n");
    }

    if (group == 4) {
        ensuref(check_g4(), "Not a star-star!\n");
    }

    if (group == 5) {
        ensuref(check_g5(), "Not increasing c_{i,j}!\n");
    }

    if (group == 6) {
        ensuref(check_g6(), "Not zeros after c_{i,0}!\n");
    }

    if (group == 7) {
        ensuref(check_g7(), "Sum c_{i,j} != Sum w_i!\n");
    }

    inf.readEof();
}
