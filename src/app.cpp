#include "butterfly.h"
#include "query.h"
#include "partTree.h"
#include <omp.h>

int st;
vector <PartTreeCnt> ptList;
PartTreeCnt partTree;

ull calc(int l, int r) {
    ull sum = 0;
    
	#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < st; i++) {
        int res = ptList[i].query(l, r);
        sum += 1ll * res * (res - 1) / 2;
    }
    
    sum += partTree.query(l, r);
    
    return sum;
}

int MaxMemory1;

void myInit() {
    ull A = 0, sumSize = 0;
    for (int i = 0; i < pairs.size(); i++) A += 1ll * pairs[i].size() * pairs[i].size(), sumSize += pairs[i].size();
    ull C = 2.5e7 * MaxMemory1;
    vector <PairNode> tmp;
    st = pairs.size();
    ull csum = 0;
    for (int i = pairs.size(); i --> 0; ) {
        // csum += pairs[i].size() * pairs[i].size();
        // if (csum > C) break;
        // st--;
        auto &a = pairs[i];
        ull tmpSize = tmp.size();
        sort(a.begin(), a.end(), [](const PairNode &a, const PairNode &b) {
            return a.r2 < b.r2;
        });
        for (int x = 0; x < a.size(); x++) {
            for (int y = x; y --> 0; ) {
                PairNode cur{min(a[x].l, a[y].l), max(a[x].r, a[y].r), 0, min(a[x].r2, a[y].r2)};
                if (cur.r >= cur.r2) break;
                tmp.push_back(cur);
                if (tmp.size() > C) break;
            }
            if (tmp.size() > C) break;
        }
        if (tmp.size() > C) {
            tmp.resize(tmpSize);
            break;
        }
        st--;
        sumSize -= a.size();
    }
    for (int i = 0; i < st; i++) {
        PartTreeCnt a;
        a.build(pairs[i]);
        ptList.push_back(a);
    }
    
    partTree.build(tmp);
}

map <string, string> args;

int main(int argc, char **argv) {
    args["thrs"] = "1";
    args["maxM"] = "400";
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            string a, b;
            for (int j = 1, len = strlen(argv[i]); j < len; j++) {
                if (argv[i][j] == '=') b = a, a = "";
                else a += argv[i][j];
            }
            args[b] = a;
        }
    }
    omp_set_num_threads(atoi(args["thrs"].c_str()));
    MaxMemory1 = atoi(args["maxM"].c_str());
    for (auto i : args) cerr << i.first << ' ' << i.second << endl;
    init();
    search_pairs();
    initRand(timeList, 5000, 0);
    myInit();

    int L = timeList.size();
    while (!endQuery()) {
        auto [l, r] = getPos(getQuery());
        answer(calc(l, r));
    }
}