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
    using ull = unsigned long long;
    static constexpr int XCNT = 12;
    static constexpr int MOVE = 5;
    static constexpr ull MASK = 0x0FFFFFFFFFFFFFFF;
public:
    long long sumScores(string s) {
        int n = s.size();
        vector<ull> data(n);
        ull d = 0;
        for (int i = 0; i < XCNT; ++i) {
            d <<= MOVE;
            if (i < n) {
                d += s[i] - 'a' + 1;
            }
        }

        for (int i = 0; i < n; ++i) {
            data[i] = d;
            d <<= MOVE;
            if (i + XCNT < n) {
                d += s[i + XCNT] - 'a' + 1;
            }
            d &= MASK;
        }

        vector<ull> target(n / XCNT + 1);
        for (int i = 0; i * XCNT < n; ++i) {
            target[i] = data[i * XCNT];
        }
        if (target.back() == 0) {
            target.back() = -1;
        } else {
            target.back() |= (1ULL << (XCNT - n % XCNT) * 5) - 1;
        }


        long long result = s.size();
        for (int i = 1; i < n; ++i) {
            int j = i;
            for (int t = 0; j < n; j += XCNT, ++t) {
                if (data[j] != target[t]) {
                    result += XCNT * t;
                    ull d1 = data[j], d2 = target[t];
                    ull m = 0x1F;
                    m <<= (XCNT - 1) * MOVE;
                    for (; (d1 & m) == (d2 & m); m >>= MOVE) {
                        ++result;
                    }
                    break;
                }
            }
            if (j == n) {
                result += n - i;
            }

            //if (s[i] == s[0])
            //    cout << i << ", result, : " << result << endl;
        }
        return result;
    }


};

class Solution1Timeout132of150 {
//class Solution {
public:
    long long sumScores(string s) {
        int n = s.size();
        long long result = s.size();
        for (int i = 1; i < n; ++i) {
            int j = i;
            for (; j < n; ++j) {
                if (s[j] != s[j - i]) break;
            }
            result += j - i;
            if (s[i] == s[0])
                cout << i << ", result, : " << result << endl;
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
    Solution s;
    auto actual = s.sumScores("babab");
    decltype(actual) expect = 9;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    Solution s;
    auto actual = s.sumScores("xtriayneymcqfmbeutgqmjygybvhpamjmksjtovkxtriayneymcqfmbeutgqmj");
    decltype(actual) expect = 84;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.sumScores("anpljtlhtcsvfxwthhbpeizuwqvvjjqfqpxfkmwdnzhxqhsmhwfhsiyhrovmrjvvnlzzmgcxosbwcluonynkkhbizlwjzwzboahimyanhpymqhylrieukfkbmrbpgyxmjuoicguufthlfmhqaignscuqptaaxfqixphjwioxjhvubgzamexmooixazvoxotagwawmsgykgpizkpscxlqanpljtlhtcsvfxwthhbpeizuwqvvjjqfqpxfkmwdnzhxqhsmhwfhsiyhrovmrjvvnlzzmgcxosbwcluonynkkhbizlwjzwzboahimyanhpymqhylrieukfkbmrbpgyxmjuoi");
    decltype(actual) expect = 489;
    EXPECT_EQ(expect, actual);
}

}
