#pragma once
#include "./butterfly.h"
struct PartTreeNode {
    ull stPos;
};
struct PreSum {
    vector <ull> sum, val;
    ull len, csum;
    PreSum() {
        len = csum = 0;
        sum.push_back(0);
        val.push_back(0);
    }
    void add(ull k) {
        val.back() |= k << (len % 64);
        csum += k;
        len++;
        if (len % 64 == 0) sum.push_back(csum), val.push_back(0);
    }
    ull calc(ull r) {
        return sum[r / 64] + __builtin_popcountll(val[r / 64] & ((1ull << (r % 64)) - 1));
    }
    void reserve(ull n) {
        sum.reserve(n / 64 + 1);
        val.reserve(n / 64 + 1);
    }
};

vector <int> ttmp;
struct PartTreeCnt {
    vector <PreSum> pre[2];
    vector <PairNode> pairs;
    vector <int> vals[2];
    int dep;
    ull build(ull x, ull l, ull r, int dep) {
        if (l > r) return 0;
        if (l == r) return vals[1][l] != inf;
        ull mid = min(r, l + (1ull << dep) - 1);
        ull l0 = build(x << 1, l, mid, dep - 1);
        ull l1 = build(x << 1 | 1, mid + 1, r, dep - 1);

        ull p0 = l, p1 = mid + 1;
        while (p0 <= mid || p1 <= r) {
            if (p0 == mid + 1 || p1 != r + 1 && vals[0][p1] < vals[0][p0]) {
                ttmp.push_back(vals[0][p1++]);
                pre[0][dep].add(1);
            }
            else {
                ttmp.push_back(vals[0][p0++]);
                pre[0][dep].add(0);
            }
        }
        for (ull i = l; i <= r; i++) vals[0][i] = ttmp[i - l];
        ttmp.clear();

        p0 = l, p1 = mid + 1;
        while (p0 < l + l0 || p1 < mid + 1 + l1) {
            if (p0 == l + l0 || p1 != mid + 1 + l1 && vals[1][p1] < vals[1][p0]) {
                ttmp.push_back(vals[1][p1++]);
                pre[1][dep].add(1);
            }
            else {
                ttmp.push_back(vals[1][p0++]);
                pre[1][dep].add(0);
            }
        }
        while (p0 < mid + 1) p0++, pre[1][dep].add(0);
        while (p1 < r + 1) p1++, pre[1][dep].add(1);
        for (ull i = l; i < l + l0 + l1; i++) vals[1][i] = ttmp[i - l];
        ttmp.clear();
        
        return l0 + l1;
    }
    ull query(ull x, ull l, ull r, ull L, ull R, ull p0, ull p1, int dep) {
        if (l > R || L > r || p0 == 0) return 0;
        if (L <= l && r <= R) return p0 - p1;
        ull tmp0 = pre[0][dep].calc(l + p0) - l / 2;
        ull tmp1 = pre[1][dep].calc(l + p1) - l / 2;
        ull mid = min(r, l + (1ull << dep) - 1);
        return query(x << 1, l, mid, L, R, p0 - tmp0, p1 - tmp1, dep - 1) + query(x << 1 | 1, mid + 1, r, L, R, tmp0, tmp1, dep - 1);
    }
    void build(vector <PairNode> &a) {
        if (a.empty()) return;
        pairs.swap(a);
        ull l = 1;
        dep = 0;
        while (l < pairs.size()) l <<= 1, dep++;
        pre[0].resize(dep);
        for (auto &i : pre[0]) i.reserve(pairs.size());
        pre[1].resize(dep);
        for (auto &i : pre[1]) i.reserve(pairs.size());
        sort(pairs.begin(), pairs.end(), [](const PairNode &a, const PairNode &b) {
            return a.l < b.l;
        });
        vals[0].reserve(pairs.size());
        vals[1].reserve(pairs.size());
        for (auto i : pairs) vals[0].push_back(i.r);
        for (auto i : pairs) vals[1].push_back(i.r2);
        ttmp.reserve(pairs.size());
        ull len = build(1, 0, pairs.size() - 1, dep - 1);
        vals[1].resize(len);
    }
    ull query(int ql, int qr) {
        ull p0 = lower_bound(pairs.begin(), pairs.end(), PairNode{ql}, [](const PairNode &a, const PairNode &b) {
            return a.l < b.l;
        }) - pairs.begin();
        if (p0 == pairs.size()) return 0;
        ull p1 = upper_bound(vals[0].begin(), vals[0].end(), qr) - vals[0].begin();
        ull p2 = upper_bound(vals[1].begin(), vals[1].end(), qr) - vals[1].begin();
    
        return query(1, 0, pairs.size() - 1, p0, pairs.size() - 1, p1, p2, dep - 1);
        
        // ull x = 1, l = 0, r = pairs.size() - 1, ans = 0;
        // int curDep = dep - 1;
        // while (l != r) {
        //     ull tmp0 = pre[0][curDep].calc(l + p1) - l / 2;
        //     ull tmp1 = pre[1][curDep].calc(l + p2) - l / 2;
        //     ull mid = min(r, l + (1ull << curDep) - 1);
        //     if (p0 <= mid) {
        //         ans += tmp0 - tmp1;
        //         x <<= 1;
        //         r = mid;
        //         p1 -= tmp0;
        //         p2 -= tmp1;
        //     }
        //     else {
        //         x = x << 1 | 1;
        //         l = mid + 1;
        //         p1 = tmp0;
        //         p2 = tmp1;
        //     }
        //     curDep--;
        // }
        // return ans + p1 - p2;
    }
};