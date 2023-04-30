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
    using Index1 = array < vector<int>, 2626 >;
    using Index2 = vector < vector<int>>; // array < vector<int>, 68276>

public:
    vector<string> maxRectangle(vector<string> &words)
    {
        Index1 indexes1;
        Index2 indexes2(68276);
        unordered_set<string> dict;
        string onechar;
        for (int i = 0; i < words.size(); ++i) {
            auto &w = words[i];
            if (w.size() == 1) {
                onechar = w;
                continue;
            }
            int x = w.size() * 26 + (w[0] - 'a');
            indexes1[x].push_back(i);
            x *= 26;
            x += w.back() - 'a';
            indexes2[x].push_back(i);
            dict.insert(w);
        }

        vector<string> results;
        for (auto it = indexes1.rbegin(); it != indexes1.rend(); ++it) {
            //cout << it->size() << endl;
            for (int i = 0; i < it->size(); ++i) {
                auto &s1 = (*it)[i];

                for (int j = i; j < it->size(); ++j) {
                    auto &s2 = (*it)[j];
                    searchresults(words, dict, s1, s2, indexes1, indexes2, results);
                }
                auto jt = it;
                for (++jt; jt != indexes1.rend(); ++jt) {
                    for (auto &s2 : *jt) {
                        searchresults(words, dict, s1, s2, indexes1, indexes2, results);
                    }
                }
            }
        }
        if (results.empty()) {
            results.push_back({ onechar });
        }
        return results;
    }
    void searchresults(const vector<string> &words, unordered_set<string> &dict, int i1, int i2, Index1 &indexes1, Index2 &indexes2, vector<string> &results)
    {
        auto &s1 = words[i1], &s2 = words[i2];
        if (s1[0] != s2[0]) return;
        vector<string> rs(s2.size());
        if (!results.empty() && results.size() * results[0].size() >= s1.size() * s2.size()) return;
        int x = s1.size() * 26 + s2.back() - 'a';
        for (auto i3 : indexes1[x]) {
            auto &s3 = words[i3];
            int y = (s2.size() * 26 + (s1.back() - 'a')) * 26 + s3.back() - 'a';
            for (auto i4 : indexes2[y]) {
                auto &s4 = words[i4];
                //cout << s1 << ", " << s2 << ", " << s3 << ", " << s4 <<  endl;

                vector<int> selected(s2.size());
                selected[0] = i1, selected.back() = i3;
                rs[0] = s1, rs.back() = s3;
                vector<vector<int> *> xselected(s2.size());
                bool valid = true;
                for (int i = 1; i < s2.size() - 1; ++i) {
                    int y = (s1.size() * 26 + (s2[i] - 'a')) * 26 + s4[i] - 'a';
                    xselected[i] = &indexes2[y];
                    if (xselected[i]->empty()) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) continue;
                int i = 1;
                while (i > 0) {
                    if (i == s2.size() - 1) {
                        for (int j = 1; j < selected.size() - 1; ++j) {
                            auto index = (*xselected[j])[selected[j]];
                            rs[j] = words[index];
                        }
                        if (ok(rs, dict)) {
                            results = rs;
                            return;
                        }
                        --i;
                        ++selected[i];
                    } else {
                        if (selected[i] < xselected[i]->size()) {
                            ++i;
                            selected[i] = 0;
                        } else {
                            --i;
                            ++selected[i];
                        }
                    }
                }
            }
        }
    }
    bool ok(vector<string> &results, unordered_set<string> &dict)
    {
        string w(results.size(), 'a');
        for (int i = 1; i < results[0].size(); ++i) {
            for (int j = 0; j < results.size(); ++j) {
                w[j] = results[j][i];
            }
            if (dict.count(w) == 0) return false;
        }
        return true;

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
    vector<string> words = { "this", "real", "hard", "trh", "hea", "iar", "sld" };
    Solution s;
    auto actual = s.maxRectangle(words);
    decltype(actual) expect = { "this",  "real", "hard" };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}
