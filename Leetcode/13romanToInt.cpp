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
    int romanToInt(string s) {
      unordered_map<char,int> tables {{'I', 1},{'V',5},{'X',10},{'L',50} ,{'C',100} ,{'D',500} ,{'M',1000}};
      int result = tables[s[0]];
      int last = result;
      for (size_t i = 1; i < s.size(); ++i) {
        int v = tables[s[i]];
        result += v;
        if (v > last) {
          result -= last + last;
        }
        last = v;
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
    auto actual = s.romanToInt("III");
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
  }
  TEST_F(TestSolution, Test2)
  {
    Solution s;
    auto actual = s.romanToInt("IV");
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
  }
  TEST_F(TestSolution, Test3)
  {
    Solution s;
    auto actual = s.romanToInt("IX"); 
    decltype(actual) expect = 9;
    EXPECT_EQ(expect, actual);
  }
  TEST_F(TestSolution, Test4)
  {
    Solution s;
    auto actual = s.romanToInt("LVIII"); 
    decltype(actual) expect = 58;
    EXPECT_EQ(expect, actual);
  }
  TEST_F(TestSolution, Test5)
  {
    Solution s;
    auto actual = s.romanToInt("MCMXCIV");
    decltype(actual) expect = 1994;
    EXPECT_EQ(expect, actual);
  }
}

