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

    class Solution {
        constexpr static unsigned FLAG = 0x1112341;
        constexpr static unsigned MASK = 0x88888888;
    public:
        int Leetcode(vector<string>& words) {
            char indexes[26];
            memset(indexes, -1, sizeof(indexes));
            indexes['h' - 'a'] = 0;
            indexes['e' - 'a'] = 4;
            indexes['l' - 'a'] = 8;
            indexes['o' - 'a'] = 12;
            indexes['t' - 'a'] = 16;
            indexes['c' - 'a'] = 20;
            indexes['d' - 'a'] = 24;
            unordered_map<unsigned, int> final;
            final[0] = 0;
            for (auto& w : words) {
                unordered_map<unsigned, int> r;
                seekResult(w, indexes, r, 0, 0);

                unordered_map<unsigned, int> next = final;
                for (auto& i1 : r) {
                    for (auto& i2 : next) {
                        unsigned nflag = i1.first + i2.first;
                        if ((FLAG - nflag) & MASK) continue;
                        auto it = final.find(nflag);
                        if (it == final.end()) {
                            final.insert({ nflag, i1.second + i2.second });
                        }
                        else {
                            it->second = min(it->second, i1.second + i2.second);
                        }
                    }
                }
            }

            auto it = final.find(FLAG);
            if (it == final.end()) return -1;
            return it->second;
        }

        void seekResult(const string& word, char indexes[26], unordered_map<unsigned, int>& result, unsigned flag, int r) {
            auto it = result.find(flag);
            if (it == result.end()) {
                result.insert({ flag, r });
            } else {
                it->second = min(it->second, r);
            }
            int wsize = word.size();
            for (int i = 0; i < wsize; ++i) {
                char idx = indexes[word[i] - 'a'];
                if (idx < 0) continue;
                unsigned nflag = flag + (1 << idx);
                if ((FLAG - nflag) & MASK) continue;
                seekResult(string(word.begin(), word.begin() + i) + string(word.begin() + i + 1, word.end()), indexes, result, nflag, r + i * (wsize - i - 1));
            }
        }
    };

    class Solution2 {
        constexpr static unsigned FLAG = 0x1112341;
        constexpr static unsigned MASK = 0x88888888;
    public:
        int Leetcode(vector<string>& words) {
            char indexes[26];
            memset(indexes, -1, sizeof(indexes));
            indexes['h' - 'a'] = 0;
            indexes['e' - 'a'] = 4;
            indexes['l' - 'a'] = 8;
            indexes['o' - 'a'] = 12;
            indexes['t' - 'a'] = 16;
            indexes['c' - 'a'] = 20;
            indexes['d' - 'a'] = 24;
            vector<unordered_map<unsigned, int>> results;
            for (auto& w : words) {
                results.push_back(getResult(w, indexes));
            }
            int r = parseResults(results, FLAG);
            if (r == INT_MAX) return -1;
            return r;
        }
        unordered_map<unsigned, int> getResult(const string& word, char indexes[26]) {
            unordered_map<unsigned, int> result;
            seekResult(word, indexes, result, 0, 0);
            //cout << word << ":" << endl;
            //for (auto& r : result) {
            //    printf("%x : %d\n", r.first, r.second);
            //}
            //cout << endl;
            return result;
        }
        void seekResult(const string& word, char indexes[26], unordered_map<unsigned, int>& result, unsigned flag, int r) {
            auto it = result.find(flag);
            if (it == result.end()) {
                result.insert({ flag, r });
            }
            else {
                it->second = min(it->second, r);
            }
            int wsize = word.size();
            for (int i = 0; i < wsize; ++i) {
                char idx = indexes[word[i] - 'a'];
                if (idx < 0) continue;
                unsigned nflag = flag + (1 << idx);
                if ((FLAG - nflag) & MASK) continue;
                seekResult(string(word.begin(), word.begin() + i) + string(word.begin() + i + 1, word.end()), indexes, result, nflag, r + i * (wsize - i - 1));
            }
        }
        int parseResults(vector<unordered_map<unsigned, int>>& results, unsigned flag) {
            unordered_map<unsigned, int> final;
            final[0] = 0;
            for (auto& r : results) {
                unordered_map<unsigned, int> next = final;
                for (auto& i1 : r) {
                    for (auto& i2 : next) {
                        unsigned nflag = i1.first + i2.first;
                        if ((FLAG - nflag) & MASK) continue;
                        auto it = final.find(nflag);
                        if (it == final.end()) {
                            final.insert({ nflag, i1.second + i2.second });
                        }
                        else {
                            it->second = min(it->second, i1.second + i2.second);
                        }
                    }
                }
            }

            auto it = final.find(FLAG);
            if (it == final.end()) return -1;
            return it->second;
        }
    };


    class SolutionTimeout {
        constexpr static unsigned FLAG = 0x1112341;
        constexpr static unsigned MASK = 0x88888888;
    public:
        int Leetcode(vector<string>& words) {
            char indexes[26];
            memset(indexes, -1, sizeof(indexes));
            indexes['h' - 'a'] = 0;
            indexes['e' - 'a'] = 4;
            indexes['l' - 'a'] = 8;
            indexes['o' - 'a'] = 12;
            indexes['t' - 'a'] = 16;
            indexes['c' - 'a'] = 20;
            indexes['d' - 'a'] = 24;
            vector<unordered_map<unsigned, int>> results;
            for (auto& w : words) {
                results.push_back(getResult(w, indexes));
            }
            int r = parseResults(results, FLAG);
            if (r == INT_MAX) return -1;
            return r;
        }
        unordered_map<unsigned, int> getResult(const string& word, char indexes[26]) {
            unordered_map<unsigned, int> result;
            seekResult(word, indexes, result, 0, 0);
            //cout << word << ":" << endl;
            //for (auto& r : result) {
            //    printf("%x : %d\n", r.first, r.second);
            //}
            //cout << endl;
            return result;
        }
        void seekResult(const string& word, char indexes[26], unordered_map<unsigned, int>& result, unsigned flag, int r) {
            auto it = result.find(flag);
            if (it == result.end()) {
                result.insert({ flag, r });
            }
            else {
                it->second = min(it->second, r);
            }
            int wsize = word.size();
            for (int i = 0; i < wsize; ++i) {
                char idx = indexes[word[i] - 'a'];
                if (idx < 0) continue;
                unsigned nflag = flag + (1 << idx);
                if ((FLAG - nflag) & MASK) continue;
                seekResult(string(word.begin(), word.begin() + i) + string(word.begin() + i + 1, word.end()), indexes, result, nflag, r + i * (wsize - i - 1));
            }
        }
        int parseResults(vector<unordered_map<unsigned, int>>& results, unsigned flag) {
            return traverse(results, flag, 0, 0);
        }
        int traverse(vector<unordered_map<unsigned, int>>& results, unsigned flag, int i, int r) {
            if (flag == 0) return r;
            if (results.size() == i) return INT_MAX;
            int rr = INT_MAX;
            for (auto& x : results[i]) {
                unsigned nflag = flag - x.first;
                if (nflag & MASK) continue;
                int nr = traverse(results, nflag, i + 1, r + x.second);
                rr = min(rr, nr);
            }
            return rr;
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
        vector<int> para = { 1,1,1,1 };
        vector<string> spara = { "hold","engineer","cost","level" };
        Solution s;
        auto actual = s.Leetcode(spara);
        decltype(actual) expect = 5;
        EXPECT_EQ(expect, actual);
    }
}

