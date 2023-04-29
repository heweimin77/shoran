#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>

#include "support.h"

using namespace std;

namespace {

    class Solution {
    public:
        int countSubstrings(string s, string t) {
            int result = 0;
            int sn = s.size(), tn = t.size();
            for (int i = 0; i < sn; ++i) {
                for (int j = 0; j < tn; ++j) {
                    if (s[i] == t[j]) continue;
                    int left = 1, right = 1;
                    for (int ii = i - 1, jj = j - 1; ii >= 0 && jj >= 0 && s[ii] == t[jj]; --ii, --jj) ++left;
                    for (int ii = i + 1, jj = j + 1; ii < sn && jj < tn && s[ii] == t[jj]; ++ii, ++jj) ++right;
                    result += left * right;
                    cout << i << ", " << j << ": " << result << endl;
                }
            }
            return result;
        }
    };

    class Solution2Slow {
    public:
        int countSubstrings(string s, string t) {
            int result = 0;
            size_t n = min(s.size(), t.size());
            for (size_t d = 1; d <= n; ++d) {
                unordered_map<string, int> counts;
                for (int i = 0; i + d <= t.size(); ++i) {
                    ++counts[string(t.begin() + i, t.begin() + i + d)];
                }
                for (int i = 0; i + d <= s.size(); ++i) {
                    string x = string(s.begin() + i, s.begin() + i + d);
                    for (int j = 0; j < x.size(); ++j) {
                        char now = x[j];
                        for (char c = 'a'; c <= 'z'; ++c) {
                            if (c == now) continue;
                            x[j] = c;
                            auto it = counts.find(x);
                            if (it != counts.end()) {
                                result += it->second;
                            }
                        }
                        x[j] = now;
                    }
                }
            }
            return result;
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
        vector<vector<int>> para = { {1,5},{1,1},{10,10},{6,7} };
        vector<int> ipara = { 0,0,2 };
        vector<int> ipara2 = { 2,3,5 };
        Solution s;
        auto actual = s.countSubstrings("abe", "bbc");
        decltype(actual) expect = 10;
        EXPECT_EQ(expect, actual);
    }
}



