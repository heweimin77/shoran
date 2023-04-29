#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int domino(int n, int m, vector<vector<int>> &broken)
    {
        unsigned x = 1U << m;
        vector<int> counts(x);
        for (unsigned i = 0; i < x; ++i) {
            int r = 0;
            for (unsigned j = i; j > 0; j &= (j - 1)) {
                ++r;
            }
            counts[i] = r;
        }
        vector<int> counts2(x);
        for (unsigned i = 0; i < x; ++i) {
            int r = 0;
            for (unsigned f = 3; f < x; f <<= 1) {
                if ((f & i) == 0) {
                    ++r;
                    f <<= 1;
                }
            }
            counts2[i] = r;
        }

        vector<unsigned> brokens(n);
        for (auto &b : broken) {
            brokens[b[0]] |= 1U << b[1];
        }

        unordered_map<unsigned, int> results;
        results[0] = 0;
        for (auto b : brokens) {
            unordered_map<unsigned, int> nexts;
            for (auto &r : results) {
                if (r.first & b) continue;
                unsigned f = r.first | b;
                for (unsigned next = 0; next < x; ++next) {
                    if (f & next) continue;
                    int nr = r.second + counts[next] + counts2[f | next];
                    nexts[next] = max(nexts[next], nr);
                }
            }
            results = std::move(nexts);
        }
        return results[0];
    }
 
};

class Solution2TimeOut {
    using Flag = unsigned long long;
public:
    int domino(int n, int m, vector<vector<int>> &broken)
    {
        Flag f = (1 << n * m) - 1;
        for (auto &b : broken) {
            int p = b[0] * m + b[1];
            f &= ~(1ULL << p);
        }
        int result = 0;
        unordered_set<Flag> results = { f };
        while (!results.empty()) {
            ++result;
            unordered_set<Flag> nexts;
            for (auto d : results) {
                Flag f = 3;
                for (int i = 0; i < n * m - 1; ++i, f <<= 1) {
                    if ((i + 1) % m == 0) continue;
                    if ((d & f) == f) {
                        nexts.insert(d & ~f);
                    }
                }
                f = 1 + (1 << m);
                for (int i = 0; i < (n - 1) * m; ++i, f <<= 1) {
                    if ((d & f) == f) {
                        nexts.insert(d & ~f);
                    }
                }
            }
            results = std::move(nexts);
            //for (auto &r : results) {
            //    printf("%x ", r);
            //}
            //printf("\n");
        }
        return result - 1;
    }
};

class Solution3DfsTimeOut {
    using Flag = unsigned long long;
public:
    int domino(int n, int m, vector<vector<int>> &broken)
    {
        Flag f = 0xFFFFFFFFFFFFFFFF;
        if (n * m < 64) {
            f = (1ULL << n * m) - 1;
        }
        for (auto &b : broken) {
            int p = b[0] * m + b[1];
            f &= ~(1ULL << p);
        }
        int mresult = (n * m - broken.size()) / 2;
        int result = 0;
        unordered_set<Flag> visited;
        dfs(n, m, f, 0, (n * m - broken.size()) / 2, visited, result);
        return result;
    }
    void dfs(int n, int m, Flag d, int r, int rest, unordered_set<Flag> &visited, int &result)
    {
        if (r + rest <= result) return;
        if (visited.find(d) != visited.end()) return;

        Flag f = 3;
        for (int i = 0; i < n * m - 1; ++i, f <<= 1) {
            if ((i + 1) % m == 0) continue;
            if ((d & f) == f) {
                dfs(n, m, d & ~f, r + 1, rest - 1, visited, result);
            }
        }
        f = 1 + (1 << m);
        for (int i = 0; i < (n - 1) * m; ++i, f <<= 1) {
            if ((d & f) == f) {
                dfs(n, m, d & ~f, r + 1, rest - 1, visited, result);
            }
        }
        //printf("%x, %d, %d\n", d, r, result);
        result = max(result, r);
        visited.insert(d);
    }
};

class TestSolution :public testing::Test {
public:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};

TEST_F(TestSolution, Test1)
{
    vector<vector<int>> broken = {{1, 0}, {1, 1}};
    Solution s;
    auto actual = s.domino(2, 3, broken);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}

}
