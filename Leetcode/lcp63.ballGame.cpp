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

#define MAKE(i, j, d)  ( (i) | ((j) << 10) | ((d) << 20))
#define IGET(x)  ((x) & 1023)
#define JGET(x)  (((x) >> 10) & 1023)
#define DGET(x)  ((x) >> 20)

  class Solution {
  public:
    vector<vector<int>> ballGame(int num, vector<string>& plate) {
      int deltas[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
      vector<vector<int>> results;
      int n = plate.size();
      int m = plate[0].size();
      static int flag[1000][1000];
      memset(flag, 0, sizeof(flag));
      static int data1[1000 * 1000 * 4];
      static int data2[1000 * 1000 * 4];
      int* q = data1, * q1 = data2;
      int qc = 0, qc1 = 0;

      for (int i = 0; i < plate.size(); ++i) {
        for (int j = 0; j < plate[i].size(); ++j) {
          if (plate[i][j] == 'O') {
            q[qc++] = MAKE(i, j, 0);
            q[qc++] = MAKE(i, j, 1);
            q[qc++] = MAKE(i, j, 2);
            q[qc++] = MAKE(i, j, 3);
            //q.push_back(MAKE(i, j, 0));
            //q.push_back(MAKE(i, j, 1));
            //q.push_back(MAKE(i, j, 2));
            //q.push_back(MAKE(i, j, 3));
            flag[i][j] = 15;
          }
        }
      }

      for (int s = 0; s <= num; ++s) {
        for (int xx = 0; xx < qc; ++xx) {
          int x = q[xx];
          int i = IGET(x);
          int j = JGET(x);
          int d = DGET(x);

          int ni = i + deltas[d][0];
          int nj = j + deltas[d][1];
          int nd = d;

          if (ni < 0 || ni >= n || nj < 0 || nj >= m) {
            if (plate[i][j] != '.') continue;
            if ((ni < 0 || ni >= n) && (nj == 0 || nj == m - 1)) continue;
            if ((nj < 0 || nj >= m) && (ni == 0 || ni == n - 1)) continue;
            results.push_back({ i, j });
            continue;
          }

          if (plate[ni][nj] == 'E') {
            nd = (nd + 3) & 3;
          }
          else if (plate[ni][nj] == 'W') {
            nd = (nd + 1) & 3;
          }
          if (flag[ni][nj] & (1 << nd)) continue;
          flag[ni][nj] |= (1 << nd);
          //nq.push_back(MAKE(ni, nj, nd));
          q1[qc1++] = MAKE(ni, nj, nd);
        }
        swap(q, q1);
        qc = qc1;
        qc1 = 0;
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
    vector<string> positive = { "smart","brilliant","studious" };
    vector<string> negative = { "not" };
    vector<string> report = { "this student is studious","the student is smart" };
    vector<int> ids = { 1,2 };
    Solution s;
    vector<string> plate = {"..E.", ".EOW", "..W."};
    auto actual = s.ballGame(4, plate);
    decltype(actual) expect = { {2, 1} };
    EXPECT_EQ_COMPLEX_CONTAINER(expect, actual);
  }
}

