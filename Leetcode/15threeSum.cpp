#include <string>
#include <array>
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
    vector<vector<int>> threeSum(vector<int>& nums) {
      if (nums.size() < 3) return {};
      sort(nums.begin(), nums.end());
      vector<vector<int>> results;
      for (auto ia = nums.begin(); ia != nums.end() && *ia <= 0; ++ia) {
        if (ia != nums.begin() && *ia == *(ia - 1)) continue;
        if (*ia > 0) break;

        auto ic = nums.end() - 1;
        for (auto ib = ia + 1; ib < ic; ++ib) {
          if (ib != ia + 1 && *ib == *(ib - 1)) continue;

          while (*ia + *ib + *ic > 0 && ic != ib) --ic;
          if (ic != ib && *ia + *ib + *ic == 0) {
            results.push_back({ *ia, *ib, *ic });
          }
        }
      }

      return results;
    }
  };


  //n*n*logn, 比较慢，9%
  class Solution2 {
  public:
    vector<vector<int>> threeSum(vector<int>& nums) {
      if (nums.size() < 3) return {};
      sort(nums.begin(), nums.end());
      int la = nums[0] - 1;
      vector<vector<int>> results;
      for (auto ia = nums.begin(); ia != nums.end() && *ia <= 0; ++ia) {
        while (ia != nums.end() && *ia == la) ++ia;
        if (ia == nums.end()) break;
        la = *ia;
        int lb = *ia - 1;
        for (auto ib = ia + 1; ib != nums.end(); ++ib) {
          while (ib != nums.end() && *ib == lb) ++ib;
          if (ib == nums.end()) break;
          lb = *ib;
          int c = -*ia - *ib;
          if (c < *ib) break;
          auto ic = lower_bound(ib + 1, nums.end(), c);
          if (ic != nums.end() && *ic == c) {
            results.push_back({ *ia, *ib, *ic });
          }

        }
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


  TEST_F(TestSolution, Test1)
  {
    Solution s;
    vector<int> nums = { -1,0,1,2,-1,-4};
    auto actual = s.threeSum(nums);
    decltype(actual) expect = {{-1,-1,2},{-1,0,1}};
    EXPECT_EQ_COMPLEX_CONTAINER(expect, actual);
  }
  TEST_F(TestSolution, Test2)
  {
    Solution s;
    vector<int> nums = {0};
    auto actual = s.threeSum(nums);
    decltype(actual) expect = {};
    EXPECT_EQ_COMPLEX_CONTAINER(expect, actual);
  }

}

