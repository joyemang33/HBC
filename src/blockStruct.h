#include "./butterfly.h"

struct BlockStructure {
    int blockSize, blockCnt, n;
    vector < vector <ull> > res;
    vector <PairNode> aL, aR;
    vector <int> ban;
    void build(vector <PairNode> &qwq, vector <int> &deg, int B) {
        if (qwq.empty()) return;
        aL.swap(qwq);
        aR = aL;
        n = aL.size();
        ban.resize(n, 0);
        for (int i = 0; i < n; i++) aL[i].r = i, aR[i].l = i;
        sort(aL.begin(), aL.end(), [](const PairNode &a, const PairNode &b) {
            return a.l > b.l;
        });
        sort(aR.begin(), aR.end(), [](const PairNode &a, const PairNode &b) {
            return a.r < b.r;
        });
        blockCnt = B;
        blockSize = n / B + 1;
        while ((blockCnt - 1) * blockSize > n) blockCnt--;
        vector <int> able(n, 0);
        res.resize(blockCnt);
        cerr << n << ' ' << blockCnt << endl;
        for (int i = 0; i < blockCnt; i++) {
            if (i) for (int j = (i - 1) * blockSize; j < i * blockSize; j++) able[aL[j].r] = 1;
            vector < vector <int> > cnt(deg.size());
            for (int i = 0; i < deg.size(); i++) cnt[i].resize(deg[i], 0);
            vector <ull> cur(deg.size(), 0);
            ull curSum = 0;
            for (int j = i * blockSize; j < min((i + 1) * blockSize, n); j++) ban[aL[j].l2]++;
            res[i].reserve(blockCnt);
            for (int t = 0; t < blockCnt; t++) {
                if (t) for (int j = (t - 1) * blockSize; j < t * blockSize; j++)
                    if (able[aR[j].l] && ban[aR[j].l2] == 0) {
                        if (cnt[aR[j].l2][aR[j].r2]++ == 0) {
                            curSum += cur[aR[j].l2]++;
                        }
                    }
                for (int j = t * blockSize; j < min((t + 1) * blockSize, n); j++)
                    if (ban[aR[j].l2]++ == 0)
                        curSum -= 1ull * cur[aR[j].l2] * (cur[aR[j].l2] - 1) / 2;
                res[i].push_back(curSum);
                for (int j = t * blockSize; j < min((t + 1) * blockSize, n); j++)
                    if (--ban[aR[j].l2] == 0)
                        curSum += 1ull * cur[aR[j].l2] * (cur[aR[j].l2] - 1) / 2;
            }
            for (int j = i * blockSize; j < min((i + 1) * blockSize, n); j++) ban[aL[j].l2]--;
            cerr << i << " OK" << endl;
        }
    }
    pair < ull, vector <int> > query(int l, int r) {
        if (aL.empty()) return {0, {}};
        l = upper_bound(aL.begin(), aL.end(), PairNode{l, r}, [](const PairNode &a, const PairNode &b) {
            return a.l > b.l;
        }) - aL.begin();
        r = upper_bound(aR.begin(), aR.end(), PairNode{l, r}, [](const PairNode &a, const PairNode &b) {
            return a.r < b.r;
        }) - aR.begin();
        vector <int> ans;
        int lid = l / blockSize;
        int rid = r / blockSize;
        for (int i = lid * blockSize; i < min(n, (lid + 1) * blockSize); i++) if (ban[aL[i].l2]++ == 0) ans.push_back(aL[i].l2);
        for (int i = rid * blockSize; i < min(n, (rid + 1) * blockSize); i++) if (ban[aR[i].l2]++ == 0) ans.push_back(aR[i].l2);
        for (int i = lid * blockSize; i < min(n, (lid + 1) * blockSize); i++) ban[aL[i].l2]--;
        for (int i = rid * blockSize; i < min(n, (rid + 1) * blockSize); i++) ban[aR[i].l2]--;
        return {res[lid][rid], ans};
    }
};