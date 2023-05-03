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
    bool isValid(string s)
    {
        char *ss = (char *)malloc(s.size());
        char *p = ss;
        for (auto ch : s) {
            if (ch == 'a') {
                *p++ = ch;
            } else if (ch == 'b') {
                if (p - ss >= 1 && *(p - 1) == 'a') {
                    *p++ = 'b';
                } else {
                    return false;
                }
            } else {
                if (p - ss >= 2 && *(p - 1) == 'b' && *(p - 2) == 'a') {
                    p -= 2;
                } else {
                    return false;
                }
            }
        }
        return p == ss;
    }
};

class Solution2 {
public:
    bool isValid(string s)
    {
        vector<char> ss;
        for (auto ch : s) {
            if (ch != 'c') {
                ss.push_back(ch);
            } else {
                if (ss.size() >= 2 && ss.back() == 'b' && ss[ss.size() - 2] == 'a') {
                    ss.pop_back();
                    ss.pop_back();
                } else {
                    return false;
                }
            }
        }
        return ss.empty();
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
    auto actual = s.isValid("aabcbc");
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}

}
