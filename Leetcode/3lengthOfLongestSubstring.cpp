#include <string>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

namespace {

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        size_t result = 0;
        int start = -1;
        unordered_map<int, int> indexes;
        
        for (size_t i = 0; i < s.size(); ++i) {
            auto it = indexes.find(s[i]);
            if (it != indexes.end() && it->second > start) {
                start = it->second;
            } else {
                result = max(result, i - start);
            }
            indexes[s[i]] = i;
        }
        return result;            
    }
};

class TestSolution3 :public testing::Test
{
public:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};


TEST_F(TestSolution3, Test1)
{
    //vector<int> para1 = { 4,5,6,7,0,1,2 };
    int expect = 4;

    Solution s;
    auto actual = s.lengthOfLongestSubstring("abcabcbb");
    EXPECT_EQ(3, actual);
}
TEST_F(TestSolution3, Test2)
{
    //vector<int> para1 = { 4,5,6,7,0,1,2 };
    //int expect = 4;

    Solution s;
    auto actual = s.lengthOfLongestSubstring("tmmzuxt");
    EXPECT_EQ(6, actual);
}
}
