#include "testlib.h"

using namespace std;

const int MAXN = 200'000;
const int C = 1'000'000'000;

int n;
int a[MAXN + 7], b[MAXN + 7], w[MAXN + 7];
int deg[MAXN + 7];
vector<int> c[MAXN + 7], g[MAXN + 7];
int ptr[MAXN + 7];

bool is_permutation(vector<int> arr) {
    sort(arr.begin(), arr.end());
    for (int i = 0; i < (int) arr.size(); i++) {
        if (arr[i] != i + 1) {
            return false;
        }
    }
    return true;
}

bool check(InStream &in) {
    string answer_exists = in.readToken("[a-zA-Z]{2,3}", "ans token");
    if (upperCase(answer_exists) != "YES" && upperCase(answer_exists) != "NO") {
        in.quit(_wa, "Unknown token instead of YES or NO");
    }
    if (upperCase(answer_exists) == "NO") {
        return false;
    }
    vector<int> order = in.readInts(n - 1, 1, n - 1, "delete order");
    if (!is_permutation(order)) {
        in.quitf(_wa, "Deleting order is not a permutation");
    }

    reverse(order.begin(), order.end());
    fill(ptr, ptr + MAXN + 7, 0);

    for (auto i : order) {
        int weight = w[i];
        int val = c[a[i]][ptr[a[i]]] + c[b[i]][ptr[b[i]]];
        ptr[a[i]]++;
        ptr[b[i]]++;
        if (val < weight) {
            in.quitf(_wa, format("Can't delete edge %d, %d < %d", i, val, weight).c_str());
        }
    }

    return true;
}

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);

    int __;
    n = inf.readInt();
    __ = inf.readInt();

    for (int i = 1; i <= n - 1; i++) {
        a[i] = inf.readInt();
        b[i] = inf.readInt();
        w[i] = inf.readInt();
    }

    for (int i = 1; i <= n - 1; i++) {
        g[a[i]].push_back(b[i]);
        g[b[i]].push_back(a[i]);
        deg[a[i]]++;
        deg[b[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        c[i] = inf.readInts(deg[i]);
    }

    bool pa = check(ouf);
    bool ja = check(ans);

    if (pa && !ja) {
        quitf(_fail, "Participant found answer but jury didn't");
    }
    if (!pa && ja) {
        quitf(_wa, "Participant didn't find answer but jury did");
    }

    quitf(_ok, "OK");
}
