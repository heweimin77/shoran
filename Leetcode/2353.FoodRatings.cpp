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
#include <numeric>

#include "support.h"

using namespace std;


namespace {

class FoodRatings {
    using MyType = pair<int, string>;
    struct Compare {
        bool operator () (const MyType &lhs, const MyType &rhs)
        {
            if (lhs.first != rhs.first) {
                return lhs.first < rhs.first;
            }
            return lhs.second > rhs.second;
        }
    };
public:
    FoodRatings(vector<string> &foods, vector<string> &cuisines, vector<int> &ratings)
    {
        for (int i = 0; i < foods.size(); ++i) {
            auto &f = foods[i];
            auto &c = cuisines[i];
            int r = ratings[i];
            foodxs[f] = { c, r };
            cuisinexs[c].push({r, f});
        }
    }

    void changeRating(string food, int newRating)
    {
        auto &fd = foodxs[food];
        fd.second = newRating;
        auto &c = cuisinexs[fd.first];
        c.push({newRating, food});
    }

    string highestRated(string cuisine)
    {
        auto &c = cuisinexs[cuisine];
        while (!c.empty()) {
            auto &fd = foodxs[c.top().second];
            if (fd.second == c.top().first) {
                return c.top().second;
            }
            c.pop();
        }
        return "";
    }
private:
    unordered_map<string, pair<string, int>> foodxs;
    unordered_map<string, priority_queue<MyType, vector<MyType>, Compare>> cuisinexs;
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
    vector<vector<int>> grid = {{3, 2, 1}, {1, 7, 6}, {2, 7, 7}};
    //FoodRatings s;
    //auto actual = s.equalPairs(grid);
    //decltype(actual) expect = 1;
    //EXPECT_EQ(expect, actual);
}

}

