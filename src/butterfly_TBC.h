#pragma once
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 100000010, M = 200000010, inf = M + 5;

vector < pair < int, int > > son[N];
int n, m, L, R;
long long T;
vector <double> timeList;
struct PairNode {
    int l, r;
};
vector < vector <PairNode> > pairs;
vector <PairNode> bucTmp[N];
int bucCnt[N];

void search_pairs() {
    for (int x = 0; x < n; x++) {
        vector < pair < int, pair < vector <int>, vector <int> > > > tmp;
        for (auto &[y, w1]: son[x]) if (y > x) {
            for (auto &[z, w2] : son[y]) if (z > x) {
                bucTmp[z].push_back({min(w1, w2), max(w1, w2)});
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
    scanf("%d%d", &n, &m);
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
    for (auto [u, v, w] : allEdge) {
        son[init_pos[u]].push_back({init_pos[v], w});
        son[init_pos[v]].push_back({init_pos[u], w});
    }
}