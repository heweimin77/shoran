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
    string intToRoman(int num) {
      string result;
      for (int base = 1000, b = 3; b >= 0; base /= 10, --b) {
        result += intToRoman(num / base % 10, b);
      }
      return result;
    }

    string intToRoman(int num, int b) {
      array<array<char, 3>, 4> table = {{
        { 'I', 'V', 'X' },
        { 'X', 'L', 'C' },
        { 'C', 'D', 'M' },
        { 'M', '?', '?' }
      }};

      auto& items = table[b];
      if (num == 0) return "";
      if (num == 4) return string(1, items[0]) + string(1, items[1]);
      if (num == 9) return string(1, items[0]) + string(1, items[2]);
      if (num >= 5) return items[1] + string(num - 5, items[0]);
      return string(num, items[0]);
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
    auto actual = s.intToRoman(3);
    decltype(actual) expect = "III";
    EXPECT_EQ(expect, actual);
  }
  TEST_F(TestSolution, Test2)
  {
    Solution s;
    auto actual = s.intToRoman(4);
    decltype(actual) expect = "IV";
    EXPECT_EQ(expect, actual);
  }
  TEST_F(TestSolution, Test3)
  {
    Solution s;
    auto actual = s.intToRoman(9);
    decltype(actual) expect = "IX";
    EXPECT_EQ(expect, actual);
  }
  TEST_F(TestSolution, Test4)
  {
    Solution s;
    auto actual = s.intToRoman(58);
    decltype(actual) expect = "LVIII";
    EXPECT_EQ(expect, actual);
  }
  TEST_F(TestSolution, Test5)
  {
    Solution s;
    auto actual = s.intToRoman(1994);
    decltype(actual) expect = "MCMXCIV";
    EXPECT_EQ(expect, actual);
  }
}

