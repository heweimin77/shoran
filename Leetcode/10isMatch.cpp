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
    struct Matcher {
      string reg;
      string fix;
    };
  public:
    bool isMatch(string s, string p) {
      vector<Matcher> matchers;
      for (size_t i = 0; i < p.size(); ) {
        Matcher matcher;
        bool isDot = false;
        while (i + 1 < p.size() && p[i + 1] == '*') {
          if (p[i] == '.') isDot = true;
          matcher.reg += p[i];
          i += 2;
        }
        if (isDot) {
          matcher.reg = ".";
        }

        while (i < p.size() && (i + 1 == p.size() || p[i + 1] != '*')) {
          matcher.fix += p[i++];
        }
        matchers.push_back(matcher);
      }

      auto & lastfix = matchers.back().fix;
      if (lastfix.size() > s.size() ||  !isMatchFix(s.end() - lastfix.size(), s.end(), lastfix)) {
        return false;
      }
      size_t len = 0;
      for (auto& m : matchers) {
        len += m.fix.size();
      }

      return isMatch(s.begin(), s.end(), matchers, 0, len);
    }
    bool isMatch(string::const_iterator b, string::const_iterator e, vector<Matcher> &matchers, size_t i, size_t len) {
      auto &m = matchers[i];
      if (i == matchers.size() - 1) {
        return e - len == isMatchReg(b, e - len, m.reg);
      }
      string::const_iterator next = isMatchReg(b, e - len, m.reg);
      for (; b <= next; ++b) {
        if (isMatchFix(b, b + m.fix.size(), m.fix)) {
          if (isMatch(b + m.fix.size(), e, matchers, i + 1, len - m.fix.size())) {
            return true;
          }
        }
      }
      return false;

    }
    bool isMatchFix(string::const_iterator b, string::const_iterator e, const string& fix) {
      if (e - b != fix.size()) return false;
      string::const_iterator it = fix.begin();
      for (; b != e; ++b, ++it) {
        if (*it != '.' && *b != *it) {
          return false;
        }
      }
      return true;
    }
    string::const_iterator isMatchReg(string::const_iterator b, string::const_iterator e, const string& reg) {
      if (reg == ".") {
        return e;
      }

      string::const_iterator it = reg.begin();
      while (b != e) {
        while (it != reg.end() && *it != *b) ++it;
        if (it == reg.end()) break;
        while (b != e && *b == *it) ++b;
      }
      return b;
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


  //TEST_F(TestSolution, Test1)
  //{
  //  Solution s;
  //  auto actual = s.isMatch("aa", "a");
  //  decltype(actual) expect = false;
  //  ASSERT_EQ(expect, actual);
  //}
  //TEST_F(TestSolution, Test2)
  //{
  //  Solution s;
  //  auto actual = s.isMatch("aa", "a*");
  //  decltype(actual) expect = true;
  //  ASSERT_EQ(expect, actual);
  //}
  //TEST_F(TestSolution, Test3)
  //{
  //  Solution s;
  //  auto actual = s.isMatch("ab", ".*");
  //  decltype(actual) expect = true;
  //  ASSERT_EQ(expect, actual);
  //}
  //TEST_F(TestSolution, Test4)
  //{
  //  Solution s;
  //  auto actual = s.isMatch("aab", "c*a*b");
  //  decltype(actual) expect = true;
  //  ASSERT_EQ(expect, actual);
  //}
  //TEST_F(TestSolution, Test5)
  //{
  //  Solution s;
  //  auto actual = s.isMatch("mississippi", "mis*is*p*.");
  //  decltype(actual) expect = false;
  //  ASSERT_EQ(expect, actual);
  //}
  //TEST_F(TestSolution, Test6)
  //{
  //  Solution s;
  //  auto actual = s.isMatch("mississippi", "mis*is*ip*.");
  //  decltype(actual) expect = true;
  //  ASSERT_EQ(expect, actual);
  //}
  TEST_F(TestSolution, Test7)
  {
    Solution s;
    auto actual = s.isMatch("a", ".*..");
    decltype(actual) expect = false;
    EXPECT_EQ(expect, actual);
  }
}

