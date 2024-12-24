#include <bits/stdc++.h>
using namespace std;
chrono::steady_clock::time_point lstClock = chrono::steady_clock::now();
chrono::nanoseconds initTime, queryTime;
struct QueryBase {
    virtual pair <double, double> getQuery() = 0;
    virtual int endQuery() = 0;
} *queryPtr;
struct InputQuery : QueryBase {
    ifstream fin;
    double nxtL, nxtR;
    int endTag;
    void init(string name) {
        fin.open(name);
        endTag = 0;
        if (!(fin >> nxtL >> nxtR)) endTag = 1;
    }
     pair <double, double> getQuery() {
        pair <double, double> res{nxtL, nxtR};
        if (!(fin >> nxtL >> nxtR)) endTag = 1;
        return res;
    }
     int endQuery() {
        return endTag;
    }
} inputQuery;
struct RandQuery : QueryBase {
    mt19937_64 rnd;
    long long cnt;
    vector <double> values;
    void init(const vector <double> &vs, long long rounds, long long seed = 0) {
        values = vs;
        cnt = rounds;
        rnd.seed(seed);
    }
    pair <double, double> getQuery() {
        cnt--;
        if (rnd() % 100 == 0) {
            int l = rnd() % values.size(), r = rnd() % values.size();
            if (l > r) swap(l, r);
            return {values[l], values[r]};
        }
        else {
            int l = rnd() % max((int)values.size() / 10, 1), r = values.size() - 1 - rnd() % max((int)values.size() / 10, 1);
            if (l > r) swap(l, r);
            return {values[l], values[r]};
        }
    }
    int endQuery() {
        return cnt == 0;
    }
} randQuery;

void initFile(string name) {
    inputQuery.init(name);
    queryPtr = &inputQuery;
}
void initRand(const vector <double> &vs, long long rounds, long long seed = 0) {
    randQuery.init(vs, rounds, seed);
    queryPtr = &randQuery;
}
pair <double, double> getQuery() {
    static int tag = 1;
    if (tag) {
        tag = 0;
        chrono::steady_clock::time_point cur = chrono::steady_clock::now();
        initTime = cur - lstClock;
        lstClock = cur;
    }
    return queryPtr -> getQuery();
}
int endQuery() {
    int res = queryPtr -> endQuery();
    if (res == 1) {
        chrono::steady_clock::time_point cur = chrono::steady_clock::now();
        queryTime = cur - lstClock;
        lstClock = cur;
        fprintf(stderr, "%15s%15.3lf\n", "init time:", initTime.count() / 1e9);
        fprintf(stderr, "%15s%15.3lf\n", "query time:", queryTime.count() / 1e9);
    }
    return res;
}
void answer(long long res) {
    printf("%lld\n", res);
}