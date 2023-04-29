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
    void setZeroes(vector<vector<int>>& matrix) {
      for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
          if (matrix[i][j] == 0) {
            matrix[i][0] = 0;
            matrix[0][j] = 0;
          }
        }
      }
      for (size_t i = 0; i < matrix.size(); ++i) {
        if (matrix[i][0] == 0) {
          for (size_t j = 1; j < matrix[i].size(); ++j) {
            matrix[i][j] = 0;
          }
        }
      }
      for (size_t j = 0; j < matrix[0].size(); ++j) {
        if (matrix[0][j] == 0) {
          for (size_t i = 1; i < matrix.size(); ++i) {
            matrix[i][j] = 0;
          }
        }
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
    vector<vector<int>> matrix = { {1, 1, 1},{1, 0, 1},{1, 1, 1} };
    s.setZeroes(matrix);
    decltype(matrix) expect = { {1, 0, 1},{0, 0, 0},{1, 0, 1} };
    EXPECT_EQ_COMPLEX_CONTAINER(expect, matrix);
  }
}

