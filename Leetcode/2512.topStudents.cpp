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

  class Compare {
  public:
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
      if (lhs.second != rhs.second) {
        return lhs.second > rhs.second;
      }
      return lhs.first < rhs.first;
    }

  };

  class Solution {
  public:
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {
      priority_queue<pair<int, int>, vector<pair<int, int>>, Compare > q;
      unordered_set<string> positive;
      for (auto& r : positive_feedback) {
        positive.insert(r);
      }
      unordered_set<string> negative;
      for (auto& r : negative_feedback) {
        negative.insert(r);
      }

      for (size_t i = 0; i < report.size(); ++i) {
        auto score = getScore(positive, negative, report[i]);
        q.push({ student_id[i], score});
        if (q.size() > k) {
          q.pop();
        }
      }
      vector<int> results(k);
      for (auto it = results.rbegin(); it != results.rend(); ++it) {
        *it = q.top().first;
        q.pop();
      }

      return results;
    }

    int getScore(unordered_set<string>& positive, unordered_set<string>& negative, const string& r) {
      int score = 0;
      auto it = r.begin();
      while (it != r.end()) {
        while (it != r.end() && *it == ' ') ++it;
        auto f = it;
        while (f != r.end() && *f != ' ') ++f;
        auto s = string(it, f);
        if (positive.count(s) > 0) {
          score += 3;
        } else if (negative.count(s) > 0) {
          --score;
        }
        it = f;
      }

      return score;
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
    vector<string> positive = { "smart","brilliant","studious" };
    vector<string> negative = { "not" };
    vector<string> report = { "this student is studious","the student is smart"};
    vector<int> ids = {1,2};
    Solution s;
    auto actual = s.topStudents(positive, negative, report, ids, 2);
    decltype(actual) expect = {1, 2};
    EXPECT_EQ_CONTAINER(expect, actual);
  }
}

