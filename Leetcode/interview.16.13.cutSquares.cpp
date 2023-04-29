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
    vector<double> cutSquares(vector<int>& square1, vector<int>& square2) {
      vector<pair<double, double>> results;
      double x1 = square1[0] + square1[2] / 2.0;
      double y1 = square1[1] + square1[2] / 2.0;
      double x2 = square2[0] + square2[2] / 2.0;
      double y2 = square2[1] + square2[2] / 2.0;
      if (x1 == x2) {
        results.push_back({ x1, square1[1] });
        results.push_back({ x1, square1[1] + square1[2] });
        results.push_back({ x1, square2[1] });
        results.push_back({ x1, square2[1] + square2[2]});
      } else if (y1 == y2) {
        results.push_back({ square1[0], y1 });
        results.push_back({ square1[0] + square1[2], y1 });
        results.push_back({ square2[0], y1 });
        results.push_back({ square2[0] + square2[2], y1 });
      } else {
        addresultsx(results, x1, y1, x2, y2, square1[0], square1[1], square1[1] + square1[2]);
        addresultsx(results, x1, y1, x2, y2, square1[0] + square1[2], square1[1], square1[1] + square1[2]);
        addresultsy(results, x1, y1, x2, y2, square1[1], square1[0], square1[0] + square1[2]);
        addresultsy(results, x1, y1, x2, y2, square1[1] + square1[2], square1[0], square1[0] + square1[2]);

        addresultsx(results, x1, y1, x2, y2, square2[0], square2[1], square2[1] + square2[2]);
        addresultsx(results, x1, y1, x2, y2, square2[0] + square2[2], square2[1], square2[1] + square2[2]);
        addresultsy(results, x1, y1, x2, y2, square2[1], square2[0], square2[0] + square2[2]);
        addresultsy(results, x1, y1, x2, y2, square2[1] + square2[2], square2[0], square2[0] + square2[2]);
      }

      std::sort(results.begin(), results.end());
      return std::vector<double> {results[0].first, results[0].second, results.back().first, results.back().second};
    }
    void addresultsx(vector<pair<double, double>>& results, double x1, double y1, double x2, double y2, double x, double yy1, double yy2) {
      double y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
      if (yy1 <= y && y <= yy2) {
        results.push_back({ x, y });
      }
    }

    void addresultsy(vector<pair<double, double>>& results, double x1, double y1, double x2, double y2, double y, double xx1, double xx2) {
      double x = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
      if (xx1 < x && x < xx2) {
        results.push_back({ x, y });
      }
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
    vector<int> square1 = {-1, -1, 2};
    vector<int> square2 = {0, -1, 2};
    auto actual = s.cutSquares(square1, square2);
    decltype(actual) expect = {-1, 0, 2, 0 };
    EXPECT_EQ_CONTAINER(expect, actual);
  }

  TEST_F(TestSolution, Test2)
  {
    Solution s;
    vector<int> square1 = { -1, 1, 3 };
    vector<int> square2 = { 0, 0, 5 };
    auto actual = s.cutSquares(square1, square2);
    decltype(actual) expect = { -1, 2.5, 5, 2.5 };
    EXPECT_EQ_CONTAINER(expect, actual);
  }

  TEST_F(TestSolution, Test3)
  {
    Solution s;
    vector<int> square1 = { -1, 1, 3 };
    vector<int> square2 = { 0, 0, 5 };
    auto actual = s.cutSquares(square1, square2);
    decltype(actual) expect = { -1, 2.5, 5, 2.5 };
    EXPECT_EQ_CONTAINER(expect, actual);
  }
}

