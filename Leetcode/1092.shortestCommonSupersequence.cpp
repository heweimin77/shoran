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
        string shortestCommonSupersequence(string str1, string str2) {
            int n1 = str1.size(), n2 = str2.size();
            vector<string> results(n2 + 1);
            string lastr;
            for (int j = 0; j <= n2; ++j) {
                results[j] = string(str2.begin(), str2.begin() + j);
            }
            for (int i = 1; i <= n1; ++i) {
                char c1 = str1[i - 1];
                lastr = str1.substr(0, i);
                lastr.swap(results[0]);
                for (int j = 1; j <= n2; ++j) {
                    
                    char c2 = str2[j - 1];
                    if (c1 == c2) {
                        lastr = lastr + c1;
                    } else {
                        if (results[j].size() <= results[j-1].size()) {
                            lastr = results[j] + c1;
                        }
                        else {
                            lastr = results[j - 1] + c2;
                        }
                    }
                    lastr.swap(results[j]);
                }
            }
            return results.back();
        }
    };

    class Solution2Slow {
    public:
        string shortestCommonSupersequence(string str1, string str2) {
            int n1 = str1.size(), n2 = str2.size();
            vector<string> results(n2 + 1);
            for (int j = 0; j <= n2; ++j) {
                results[j] = string(str2.begin(), str2.begin() + j);
            }
            for (int i = 1; i <= n1; ++i) {
                vector<string> nexts(n2 + 1);
                char c1 = str1[i - 1];
                nexts[0] = string(str1.begin(), str1.begin() + i);
                for (int j = 1; j <= n2; ++j) {
                    char c2 = str2[j - 1];
                    if (c1 == c2) {
                        nexts[j] = results[j - 1] + c1;
                    }
                    else {
                        if (nexts[j - 1].size() <= results[j].size()) {
                            nexts[j] = nexts[j - 1] + c2;
                        }
                        else {
                            nexts[j] = results[j] + c1;
                        }
                    }
                }
                results = std::move(nexts);
            }
            return results.back();

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
        vector<vector<int>> para = { {1,2},{2,4}};
        vector<int> ipara = { 0,0,2 };
        vector<int> ipara2 = { 2,3,5 };
        Solution s;
        auto actual = s.shortestCommonSupersequence("abac", "cab");
        decltype(actual) expect = "cabac";
        EXPECT_EQ(expect, actual);
    }
}



