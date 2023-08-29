#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
    static constexpr int MOD = 1e9 + 7;
public:
    int numberOfCombinations(string num) {
        if (num[0] == '0') return 0;

        int n = num.size();
        vector<vector<int>> results(n, vector<int>(n));
        vector<vector<long long>> sums(n, vector<long long>(n));
        results[0][0] = 1;
        sums[0][0] = 1;
        vector<vector<int>> lcp(n, vector<int>(n));
        for (int d = 1; d < n; ++d) {
            lcp[n - d - 1][n - 1] = num[n - d - 1] == num[n - 1] ? 1 : 0;
            for (int i = n - d - 2, j = n - 2; i >= 0; --i, --j) {
                lcp[i][j] = num[i] == num[j] ? 1 + lcp[i + 1][j + 1] : 0;
            }
        }

        for (int j = 1; j < n; ++j) {
            results[0][j] = 1;
            for (int i = 1; i <= j; ++i) {
                if (num[i] == '0') {
                    results[i][j] = 0;
                    continue;
                }

                int x = i + i - j - 1;
                long long r = (x >= 0 ? sums[i - 1][i - 1] - sums[x][i - 1] : sums[i - 1][i - 1]);

                if (x >= 0 && (lcp[x][i] > j - i || num[x + lcp[x][i]] <= num[i + lcp[x][i]])) {
                    r += results[x][i - 1];
                }
                results[i][j] = r % MOD;
            }

            long long s = 0;
            for (int i = 0; i <= j; ++i) {
                s += results[i][j];
                s %= MOD;
                sums[i][j] = s;
            }
        }
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            result += results[i][n - 1];
        }
        return result % MOD;
    }
};

class Solution2Timeout256of257 {
    static constexpr int MOD = 1e9 + 7;
    struct StringRef {
        StringRef(const string& data, int start, int cnt) : d(data) {
            s = start;
            c = cnt;
        }
        const string& d;
        int s;
        int c;
    };
    struct compare {
        bool operator()(const StringRef& lhs, const StringRef& rhs) const {
            if (lhs.c != rhs.c) return lhs.c < rhs.c;
            return lexicographical_compare(lhs.d.begin() + lhs.s, lhs.d.begin() + lhs.s + lhs.c, 
                rhs.d.begin() + rhs.s, rhs.d.begin() + rhs.s + rhs.c);
        }
    } cmp;
public:
    int numberOfCombinations(string num) {
        if (num[0] == '0') return 0;

        int n = num.size();
        vector<map<StringRef, long long, compare>> results(n);
        for (int i = 0; i < n; ++i) {
            auto& now = results[i];
            now.insert({ StringRef(num, 0, i + 1), 1 });
            for (int j = 1; j <= i; ++j) {
                if (num[j] == '0') continue;
                StringRef snow(num, j, i - j + 1);
                long long cnt = 0;
                for (auto& r : results[j - 1]) {
                    if (cmp(snow, r.first)) break;
                    cnt += r.second;
                }
                now.insert({ StringRef(num, j, i - j + 1), cnt % MOD });
            }
        }

        long long result = 0;
        for (auto& r : results.back()) {
            result += r.second;
        }
        return result % MOD;
    }
};
class Solution1Timeout256of257 {
    static constexpr int MOD = 1e9 + 7;
    struct compare {
        bool operator()(const string& lhs, const string& rhs) const {
            if (lhs.size() != rhs.size()) return lhs.size() < rhs.size();
            return lhs < rhs;
        }
    } cmp;
public:
    int numberOfCombinations(string num) {
        if (num[0] == '0') return 0;

        int n = num.size();

        vector<map<string, long long, compare>> results(n);
        for (int i = 0; i < n; ++i) {
            auto& now = results[i];
            now.insert({ num.substr(0, i + 1), 1 });
            for (int j = 1; j <= i; ++j) {
                if (num[j] == '0') continue;
                string snow = num.substr(j, i - j + 1);
                long long cnt = 0;
                for (auto& r : results[j - 1]) {
                    if (cmp(snow, r.first)) break;
                    cnt += r.second;
                }
                now.insert({ num.substr(j, i - j + 1), cnt % MOD });
            }
        }

        long long result = 0;
        for (auto& r : results.back()) {
            result += r.second;
        }
        return result % MOD;
    }
};

class TestSolution :public testing::Test
{
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
    Solution s;
    auto actual = s.numberOfCombinations("327");
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.numberOfCombinations("1203");
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}
