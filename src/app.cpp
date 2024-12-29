#include "./butterfly.h"
#include "./query.h"
#include "./partTree.h"
#include <omp.h>

double MaxMemory1;
double ALPHA, BETA;

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
    sum = sum / (BETA * BETA);
    
    sum += partTree.query(l, r) / ALPHA;
    
    return sum;
}

bool RandWithP(double p) {
    static mt19937_64 rnd((random_device())());
    return (long double)rnd() / ULLONG_MAX <= p;
}

void myInit() {
    ull sumSize = 0;
    for (int i = 0; i < pairs.size(); i++) sumSize += pairs[i].size();
    ull C = 2.5e7 * MaxMemory1;
    vector <PairNode> tmp;
    st = pairs.size();
    ull csum = 0;
    for (int i = pairs.size(); i --> 0; ) {
        auto &a = pairs[i];
        ull tmpSize = tmp.size();
        sort(a.begin(), a.end(), [](const PairNode &a, const PairNode &b) {
            return a.r2 < b.r2;
        });
        for (int x = 0; x < a.size(); x++) {
            for (int y = x; y --> 0; ) {
                PairNode cur{min(a[x].l, a[y].l), max(a[x].r, a[y].r), 0, min(a[x].r2, a[y].r2)};
                if (cur.r >= cur.r2) break;
                if (!RandWithP(ALPHA)) continue;
                tmp.push_back(cur);
                if (tmp.size() > C) break;
            }
            if (sumSize * BETA + tmp.size() > C) break;
        }
        if (sumSize * BETA + tmp.size() > C) {
            tmp.resize(tmpSize);
            break;
        }
        st--;
        sumSize -= a.size();
    }
    cerr << st << ' ' << pairs.size() << endl;
    
    ull memory_usage = 0;
    
    for (int i = 0; i < st; i++) {
        PartTreeCnt a;
        vector <PairNode> tmp;
        for (auto j : pairs[i]) {
            if (RandWithP(BETA)) {
                tmp.push_back(j);
            }
        }
        a.build(tmp);
        memory_usage += a.memoryUsage();
        ptList.push_back(a);
    }
    
    partTree.build(tmp);
    memory_usage += partTree.memoryUsage();
    
    cerr << memory_usage / 1024 / 1024 << "M" << endl;
}

map <string, string> args;

int main(int argc, char **argv) {
    args["thrs"] = "1";
    args["maxM"] = "400";
    args["alpha"] = "1";
    args["beta"] = "1";
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
    MaxMemory1 = atof(args["maxM"].c_str());
    ALPHA = atof(args["alpha"].c_str());
    BETA = atof(args["beta"].c_str());
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