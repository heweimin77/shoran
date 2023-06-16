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
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<int> nindexes(nums1.size());
        for (int i = 0; i < nums1.size(); ++i) nindexes[i] = i;
        sort(nindexes.begin(), nindexes.end(), [&](int lhs, int rhs) {
            return nums1[lhs] > nums1[rhs];
            });
        vector<int> qindexes(queries.size());
        for (int i = 0; i < queries.size(); ++i) qindexes[i] = i;
        sort(qindexes.begin(), qindexes.end(), [&](int lhs, int rhs) {
            return queries[lhs][0] > queries[rhs][0];
            });

        map<int, int> rrs;
        int ni = 0;
        vector<int> results(queries.size());
        for (auto qi : qindexes) {
            int x = queries[qi][0];
            int y = queries[qi][1];
            for (; ni < nindexes.size() && nums1[nindexes[ni]] >= x; ++ni) {
                int i = nindexes[ni];
                int s = nums1[i] + nums2[i];
                rrs[s] = max(rrs[s], nums2[i]);
            }

            int result = -1;
            for (auto it = rrs.rbegin(); it != rrs.rend(); ++it) {
                if (it->second < y) continue;
                result = it->first;
                break;
            }
            results[qi] = result;
        }
        return results;
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
    vector<int> nums1 = { 4,3,1,2 };
    vector<int> nums2 = { 2,4,9,5 };
    vector<vector<int>> queries = { {4, 1}, {1, 3}, {2, 5} };
    Solution s;
    auto actual = s.maximumSumQueries(nums1, nums2, queries);
    decltype(actual) expect = {6, 10, 7};
    EXPECT_EQ_CONTAINER(expect, actual);
}

}
