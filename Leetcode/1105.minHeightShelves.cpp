#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int minHeightShelves(vector<vector<int>> &books, int shelfWidth)
    {
        int n = books.size();
        vector<int> results(n);
        for (int i = 0; i < n; ++i) {
            int r = INT_MAX;
            int mh = INT_MIN;
            int thick = shelfWidth;
            for (int j = i; j >= 0; --j) {
                thick -= books[j][0];
                if (thick < 0) break;
                mh = max(mh, books[j][1]);
                int rr = j > 0 ? results[j - 1] + mh : mh;
                r = min(r, rr);
            }
            results[i] = r;
        }
        return results.back();
    }
};

class Solution2 {
#define MakeKey(thick, height) (((thick) << 10) | (height))
#define GetThick(key)  (((key) >> 10) & 0x3FF)
#define GetHeight(key)  ((key) & 0x3FF)
public:
    int minHeightShelves(vector<vector<int>> &books, int shelfWidth)
    {
        unordered_map<int, int> results;
        int result = 0;
        for (auto &b : books) {
            unordered_map<int, int> nexts;
            result = nexts[MakeKey(shelfWidth - b[0], b[1])] = result + b[1];
            for (auto &r : results) {
                auto thick = GetThick(r.first);
                if (b[0] <= thick) {
                    auto height = max(b[1], GetHeight(r.first));
                    auto key = MakeKey(thick - b[0], height);
                    int rr = r.second + height - GetHeight(r.first);
                    result = min(result, rr);
                    auto it = nexts.find(key);
                    if (it != nexts.end()) {
                        it->second = min(it->second, rr);
                    } else {
                        nexts.insert({key, rr});
                    }
                }
            }
            results = std::move(nexts);
        }
        return result;
    }
};

class TestSolution :public testing::Test {
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
    vector<vector<int>> books = { {1, 3}, {2, 4}, {3, 2 } };
    Solution s;
    auto actual = s.minHeightShelves(books, 6);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}

}
