#pragma once
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 100000010, M = 200000010, inf = M + 5;

vector < pair < int, vector <int> > > son[N];
int n, m, L, R;
long long T;
vector <double> timeList;
struct PairNode {
    int l, r, l2, r2;
};
vector < vector <PairNode> > pairs;
vector <PairNode> bucTmp[N];
int bucCnt[N];

pair <int, int> getPos(pair <double, double> a) {
    int l = lower_bound(timeList.begin(), timeList.end(), a.first) - timeList.begin();
    int r = upper_bound(timeList.begin(), timeList.end(), a.second) - timeList.begin() - 1;
    return {l, r};
}
vector <PairNode> calcPairs(const vector <int> &a, const vector <int> &b) {
    vector <PairNode> res;
    int x = 0, y = 0;
    if (a[x] < b[y]) x = upper_bound(a.begin(), a.end(), b[y]) - a.begin() - 1;
    else y = upper_bound(b.begin(), b.end(), a[x]) - b.begin() - 1;
    while (1) {
        res.push_back({min(a[x], b[y]), max(a[x], b[y])});
        int lstx = x, lsty = y;
        if (a[x] < b[y]) x++;
        else y++;
        if (x == a.size() || y == b.size()) break;
        if (a[x] < b[y]) x = upper_bound(a.begin(), a.end(), b[y]) - a.begin() - 1;
        else y = upper_bound(b.begin(), b.end(), a[x]) - b.begin() - 1;
    }
    for (int i = 0; i < res.size(); i++) res[i].l2 = i == 0 ? -1 : res[i - 1].l;
    for (int i = 0; i < res.size(); i++) res[i].r2 = i + 1 == res.size() ? inf : res[i + 1].r;
    return res;
}

void search_pairs() {
    for (int x = 0; x < n; x++) {
        vector < pair < int, pair < vector <int>, vector <int> > > > tmp;
        for (auto &[y, w1]: son[x]) if (y > x) {
            for (auto &[z, w2] : son[y]) if (z > x) {
                auto res = calcPairs(w1, w2);
                bucTmp[z].insert(bucTmp[z].end(), res.begin(), res.end());
                bucCnt[z]++;
            }
        }
        for (auto& [y, w1]: son[x]) if (y > x) {
            for (auto &[z, w2] : son[y]) if (z > x) {
                if (bucCnt[z] >= 2) {
                    pairs.push_back(bucTmp[z]);
                    T += bucTmp[z].size();
                }
                bucCnt[z] = 0;
                bucTmp[z].clear();
            }
        }
    }
    sort(pairs.begin(), pairs.end(), [](const auto &a, const auto &b) {
        return a.size() > b.size();
    });
}
int init_pos[N], init_id[N], init_d[N];
vector < tuple <int, int, double> > allEdge;
void init() {
    scanf("%d", &m);
    L = 0, R = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        scanf("%d%d%lf", &u, &v, &w);
        L = max(L, u);
        R = max(R, v);
        u--, v--;
        allEdge.push_back({u, v, w});
    }
    sort(allEdge.begin(), allEdge.end(), [](const tuple <int, int, double> &a, const tuple <int, int, double> &b) {
        return get<2>(a) < get<2>(b);
    });
    if (L > R) {
        for (auto &i : allEdge) swap(get<0>(i), get<1>(i));
        swap(L, R);
    }
    for (auto &[u, v, w] : allEdge) {
        init_d[u]++, init_d[v += L]++;
        timeList.push_back(w);
    }
    n = L + R;
    for (int i = 0; i < n; i++) init_id[i] = i;
    sort(init_id, init_id + n, [&](int a, int b) {
        return init_d[a] > init_d[b];
    });
    for (int i = 0; i < n; i++) init_pos[init_id[i]] = i;
    int w = 0;
    for (auto [u, v, qwq] : allEdge) {
        son[init_pos[u]].push_back({init_pos[v], {w}});
        son[init_pos[v]].push_back({init_pos[u], {w}});
        w++;
    }
    for (int i = 0; i < n; i++) {
        vector < pair < int, vector <int> > > tmp;
        sort(son[i].begin(), son[i].end());
        for (auto [j, w] : son[i]) {
            if (tmp.empty() || tmp.back().first != j) tmp.push_back({j, w});
            else tmp.back().second.push_back(w[0]);
        }
        son[i] = tmp;
    }
}