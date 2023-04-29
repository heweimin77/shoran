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

using namespace std;

namespace {

  class Solution {
  public:
    static constexpr int MAX_VAL = 0x40000000;
    unordered_map<int, pair<int, int>> results;
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
      for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] == '0') continue;
        int r = 0;
        for (int j = i; j < s.size(); ++j) {
          r <<= 1;
          if (s[j] == '1') {
            ++r;
          }
          if (r >= MAX_VAL) break;
          results[r] = { i, j };
        }
      }
      vector<vector<int>> rs;
      for (auto& q : queries) {
        auto it = results.find(q[0] ^ q[1]);
        if (it == results.end()) {
          rs.push_back({ -1, -1 });
        } else {
          rs.push_back({it->second.first, it->second.second});
        }
      }
      return rs;
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
    vector<vector<int>> queries = { {0, 5}, {1, 2} };
    Solution s;
    auto actual = s.substringXorQueries("101101", queries);
    decltype(actual) expect = { {0, 2}, {2, 3} };
    EXPECT_EQ_COMPLEX_CONTAINER(expect, actual);
  }
}

