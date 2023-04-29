#include <string>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

namespace {

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) return s;
        vector<string> results(numRows);
        size_t i = 0; 
        while (i < s.size()) {
            for (int j = 0; i < s.size() && j < numRows; ++j, ++i) {
                results[j] += s[i];
            }
            for (int j = numRows - 2; i < s.size() && j > 0; --j, ++i) {
                results[j] += s[i];
            }
        }

        string result;
        for (auto& r : results) {
            result += r;
        }
        return result;
    }
};

class TestSolution6 :public testing::Test
{
public:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};


TEST_F(TestSolution6, Test1)
{
    vector<int> para = {1,3 };
    vector<int> para2 = {2};
    //int expect = 4;

    Solution s;
    auto actual = s.convert("PAYPALISHIRING", 3);
    EXPECT_EQ("PAHNAPLSIIGYIR", actual);
}

}


