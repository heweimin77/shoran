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
    int maxArea(vector<int>& height) {
      int area = 0;
      auto left = height.begin(), right = height.end() - 1;
      while (left < right) {
        int diff = right - left;
        if (*left > *right) {
          area = max(area, *right * diff);
          --right;
        } else {
          area = max(area, *left * diff);
          ++left;
        }
      }

      return area;
    }
  };

  class Solution2 {
  public:
    int maxArea(vector<int>& height) {
      int r1 = maxArea(height.begin(), height.end());
      int r2 = maxArea(height.rbegin(), height.rend());
      return max(r1, r2);
    }
    template<typename Iterator> 
    int maxArea (Iterator first, Iterator last) {
      map<int,int> hs;
      int area = 0;
      for (int i = 0; first != last; ++first, ++i) {
        auto it = hs.lower_bound(*first);
        if (it == hs.end()) {
          hs.insert({*first, i});
        } else {
          area = max(area, *first * (i - it->second));
        }
      }
      return area;
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
    vector<int> height = {1,8,6,2,5,4,8,3,7};
    auto actual = s.maxArea(height);
    decltype(actual) expect = 49;
    EXPECT_EQ(expect, actual);
  }

}

