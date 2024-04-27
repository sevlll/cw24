from sys import stdin, stdout

input, print = stdin.readline, stdout.write


def main():
    n, __ = map(int, input().split())
    g = [0] * (n + 1)
    stacks = [0] * (n + 1)
    sz = [0] * (n + 1)
    a = [0] * (n + 1)
    b = [0] * (n + 1)
    w = [0] * (n + 1)
    par = [0] * (n + 1)
    ind = [0] * (n + 1)

    for v in range(n + 1):
        g[v] = []

    for i in range(1, n):
        ai, bi, wi = map(int, input().split())
        a[i], b[i], w[i] = ai, bi, wi
        g[ai].append(i)
        g[bi].append(i)

    for v in range(1, n + 1):
        sz[v] = len(g[v])
        stacks[v] = list(map(int, input().split()))

    q = [1]
    uk = 0
    order = []
    while uk < len(q):
        v = q[uk]
        uk += 1
        order.append(v)
        for i in g[v]:
            u = a[i] ^ b[i] ^ v
            if u == par[v]:
                continue
            ind[u] = i
            par[u] = v
            q.append(u)
    order = order[::-1]
    match = [0] * (n + 1)
    rest_nums = [0] * (n + 1)
    for v in range(1, n + 1):
        match[v] = [-1] * sz[v]
        rest_nums[v] = []
        for i in range(sz[v]):
            rest_nums[v].append([stacks[v][i], i])
    for i in range(n - 1):
        v = order[i]
        u = par[v]
        edge_id = ind[v]
        wg = w[edge_id]
        vi = rest_nums[v][0][1]
        rest_nums[v] = []
        mix = [10 ** 10, 10 ** 10]
        for val, index in rest_nums[u]:
            if val < wg - stacks[v][vi]:
                continue
            mix = min(mix, [val, index])
        if mix[0] == 10 ** 10:
            print("No")
            exit(0)
        ui = mix[1]
        rest_nums[u].pop(rest_nums[u].index(mix))
        match[v][vi] = match[u][ui] = edge_id
    edge_cnt = [0] * n
    process = []
    pt = [0] * (n + 1)
    for v in range(1, n + 1):
        edge_id = match[v][pt[v]]
        pt[v] += 1
        if edge_cnt[edge_id] == 1:
            process.append(edge_id)
        edge_cnt[edge_id] ^= 1
    ans = []
    for _ in range(n - 1):
        edge_id = process[-1]
        process.pop()
        ans.append(edge_id)
        for v in [a[edge_id], b[edge_id]]:
            if pt[v] == sz[v]:
                continue
            next_edge_id = match[v][pt[v]]
            pt[v] += 1
            if edge_cnt[next_edge_id] == 1:
                process.append(next_edge_id)
            edge_cnt[next_edge_id] ^= 1
    ans = ans[::-1]
    print("Yes\n")
    print(' '.join(list(map(str, ans))))


main()
