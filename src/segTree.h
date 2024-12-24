#include "./butterfly.h"
#pragma once

struct SegTreeNode {
    long long ls, rs, sum;
};
vector <SegTreeNode> treeNode{{0, 0, 0}};
long long newNode(long long lstId) {
    treeNode.push_back(treeNode[lstId]);
    return treeNode.size() - 1;
}
long long treeAdd(long long x, int l, int r, int k, long long v) {
    x = newNode(x);
    treeNode[x].sum += v;
    if (l == r) return x;
    int mid = l + r >> 1;
    if (k <= mid) {
        auto tmp = treeAdd(treeNode[x].ls, l, mid, k, v);
        treeNode[x].ls = tmp;
    }
    else {
        auto tmp = treeAdd(treeNode[x].rs, mid + 1, r, k, v);
        treeNode[x].rs = tmp;
    }
    return x;
}
long long treeQuery(long long x, int l, int r, int L, int R) {
    if (l > R || L > r || x == 0) return 0;
    if (L <= l && r <= R) return treeNode[x].sum;
    int mid = l + r >> 1;
    return treeQuery(treeNode[x].ls, l, mid, L, R) + treeQuery(treeNode[x].rs, mid + 1, r, L, R);
}

vector <long long> buildTree(vector <PairNode> &a) {
    static int cnt = 0;
    cerr << ++cnt << ' ' << a.size() << endl;
    sort(a.begin(), a.end());
    vector <long long> ans{0};
    ans.reserve(a.size() + 1);
    long long rt = 0;
    for (auto i : a) {
        rt = treeAdd(rt, 0, timeList.size() - 1, i.l, i.v);
        ans.push_back(rt);
    }
    return ans;
}