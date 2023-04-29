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
    public:
        vector<string> braceExpansionII(string expression) {
            size_t i = 0;
            return parseExp(expression, i);
        }
        vector<string> parseExp(const string& expression, size_t &i) {
            vector<string> result;
            vector<string> r;
            while (i < expression.size()) {
                switch (expression[i]) {
                case '{':
                    r = parseBrace(expression, i);
                    plus(result, r);
                    break;
                case '}':
                    return result;
                case ',':
                    r = parseExp(expression, ++i);
                    merge(result, r);
                    break;
                default:
                    r = parseAtom(expression, i);
                    plus(result, r);
                }
            }

            return result;
        }
        vector<string> parseBrace(const string& expression, size_t& i) {
            ++i;
            vector<string> r = parseExp(expression, i);
            ++i;
            return r;
        }
        vector<string> parseAtom(const string& expression, size_t& i) {
            string r;
            while (i < expression.size() && 'a' <= expression[i] && expression[i] <= 'z') {
                r += expression[i++];
            }
            return { r };
        }
        void plus(vector<string>& result, vector<string>& r) {
            if (result.empty()) {
                for (auto& s : r) {
                    result.push_back(s);
                }
                return;
            }
            vector<string> rr;
            for (auto& s1 : result) {
                for (auto& s2 : r) {
                    rr.push_back(s1 + s2);
                }
            }
            sort(rr.begin(), rr.end());
            auto it = unique(rr.begin(), rr.end());
            rr.erase(it, rr.end());
            result = std::move(rr);
        }
        void merge(vector<string>& result, vector<string>& r) {
            for (auto& s : r) {
                result.push_back(s);
            }
            sort(result.begin(), result.end());
            auto it = unique(result.begin(), result.end());
            result.erase(it, result.end());
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
        auto actual = s.braceExpansionII("{a,b}{c,{d,e}}");
        decltype(actual) expect = { "ac","ad","ae","bc","bd","be" };
        EXPECT_EQ_CONTAINER(expect, actual);
    }
}

