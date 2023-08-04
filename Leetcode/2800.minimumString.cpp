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
    string minimumString(string a, string b, string c) {
        string result = a + b + c;
        minimumStringImpl(result, a, b, c);
        minimumStringImpl(result, a, c, b);
        minimumStringImpl(result, b, a, c);
        minimumStringImpl(result, b, c, a);
        minimumStringImpl(result, c, a, b);
        minimumStringImpl(result, c, b, a);
        return result;
    }
    void minimumStringImpl(string& result, string& a, string& b, string& c) {
        string r = merge(a, b);
        r = merge(r, c);
        if (r.size() < result.size() || (r.size() == result.size() && r < result)) {
            result = r;
        }
    }
    string merge(const string& a, const string& b) {
        if (a.size() > b.size()) {
            if (string::npos != a.find(b)) {
                return a;
            }
        } else {
            if (string::npos != b.find(a)) {
                return b;
            }
        }

        for (int i = min(a.size(), b.size()); i > 0; --i) {
            if (equal(a.begin() + a.size() - i, a.end(), b.begin(), b.begin() + i)) {
                return a + string(b.begin() + i, b.end());
            }
        }
        return a + b;
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

TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.minimumString("abc", "bca", "aaa");
    decltype(actual) expect = "aaabca";
    EXPECT_EQ(expect, actual);
}
}
