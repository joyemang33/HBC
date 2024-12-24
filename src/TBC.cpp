#include "butterfly_TBC.h"
#include "../query.h"
#include <omp.h>

vector<pair<vector<PairNode>, vector<int>>> sorted_pairs_;

void MyInit() {
    for (auto pairs : pairs) {
        vector<int> tmp;
        for (auto [l, r] : pairs) {
            tmp.push_back(l);
            tmp.push_back(r);
        }
        sort(tmp.begin(), tmp.end());
        tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
        for (auto &[l, r] : pairs) {
            l = lower_bound(tmp.begin(), tmp.end(), l) - tmp.begin();
            r = lower_bound(tmp.begin(), tmp.end(), r) - tmp.begin();
        }

        sort(pairs.begin(), pairs.end(), [](const PairNode &a, const PairNode &b) {
            return a.r < b.r;
        });
        sorted_pairs_.push_back({pairs, tmp});
    }
}

ull calc(int delta) {
    ull sum = 0;
    
	#pragma omp parallel for reduction(+:sum)
    for (auto &[pairs, vals] : sorted_pairs_) {
        vector<int> cnt(vals.size());
        int pos = 0, cur = 0;
        for (auto [l, r] : pairs) {
            if (vals[r] - vals[l] > delta) {
                continue;
            }
            while (vals[r] - vals[pos] > delta) {
                cur -= cnt[pos];
                pos++;
            }
            sum += cur;

            cur++;
            cnt[l]++;
        }
    }
    
    return sum;
}

map <string, string> args;

int main(int argc, char **argv) {
    args["thrs"] = "1";
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
    for (auto i : args) cerr << i.first << ' ' << i.second << endl;
    init();
    search_pairs();
    MyInit();
    initRand(timeList, 50, 0);

    int L = timeList.size();
    while (!endQuery()) {
        auto [l, r] = getQuery();
        answer(calc(r - l));
    }
}