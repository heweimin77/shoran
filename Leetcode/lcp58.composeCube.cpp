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

    class Solution {
    public:
        bool composeCube(vector<vector<string>>& shapes) {
            int n = shapes[0].size();
            vector<vector<vector<string>>> ss;
            for (auto& s : shapes) {
                ss.push_back(vector<vector<string>>(2, vector<string>(4, string(n, '0'))));
                auto& ns1 = ss.back()[0];
                for (int j = 0; j < n; ++j) {
                    ns1[0][j] = s[0][j];
                    ns1[1][j] = s[j][n-1];
                    ns1[2][j] = s[n-1][n-1-j];
                    ns1[3][j] = s[n - 1 - j][0];
                }
                auto& ns2 = ss.back()[1];
                for (int j = 0; j < n; ++j) {
                    ns2[0][j] = s[0][n - 1 - j];
                    ns2[1][j] = s[j][0];
                    ns2[2][j] = s[n - 1][j];
                    ns2[3][j] = s[n - 1 - j][n - 1];
                }
            }

            unsigned int flag = 0;
            array<pair<int, int>, 6> selected;
            selected[0] = { 0, 0 };
            return traverse(ss, selected, 1, flag);
        }

        bool traverse(vector<vector<vector<string>>> &ss, array<pair<int, int>, 6>& selected, int i, unsigned int flag) {
            if (i == 6) return true;
            for (int f = 1; f < 6; ++f) {
                if (flag & (1 << f)) continue;
                flag |= (1 << f);
                for (int s = 0; s < 8; ++s) {
                    selected[i] = { f, s };
                    if (!check(ss, selected, i)) {
                        continue;
                    }
                    if (traverse(ss, selected, i + 1, flag)) {
                        return true;
                    }
                }
                flag &= ~(1 << f);
            }
            return false;
        }
        bool check(vector<vector<vector<string>>>& ss, array<pair<int, int>, 6>& selected, int i) {
            switch (i)
            {
            case 1: 
                if (!checkline(ss, selected, 0, 0, 1, 0, true)) return false;
                break;
            case 2:
                if (!checkline(ss, selected, 0, 1, 2, 0, true)) return false;
                if (!checkline(ss, selected, 1, 3, 2, 1, true)) return false;
                if (!checkpoint(ss, selected, 0, 1, 1, 0, 2, 1)) return false;
                break;
            case 3:
                if (!checkline(ss, selected, 0, 2, 3, 0, true)) return false;
                if (!checkline(ss, selected, 2, 3, 3, 1, true)) return false;
                if (!checkpoint(ss, selected, 0, 2, 2, 0, 3, 1)) return false;
                break;
            case 4:
                if (!checkline(ss, selected, 0, 3, 4, 0, true)) return false;
                if (!checkline(ss, selected, 3, 3, 4, 1, true)) return false;
                if (!checkline(ss, selected, 4, 3, 1, 1, true)) return false;
                if (!checkpoint(ss, selected, 0, 3, 3, 0, 4, 1)) return false;
                if (!checkpoint(ss, selected, 0, 0, 4, 0, 1, 1)) return false;
                break;
            case 5:
                if (!checkline(ss, selected, 5, 0, 1, 2, true)) return false;
                if (!checkline(ss, selected, 5, 1, 4, 2, true)) return false;
                if (!checkline(ss, selected, 5, 2, 3, 2, true)) return false;
                if (!checkline(ss, selected, 5, 3, 2, 2, true)) return false;

                if (!checkpoint(ss, selected, 5, 0, 2, 2, 1, 3)) return false;
                if (!checkpoint(ss, selected, 5, 1, 1, 2, 4, 3)) return false;                
                if (!checkpoint(ss, selected, 5, 2, 4, 2, 3, 3)) return false;
                if (!checkpoint(ss, selected, 5, 3, 3, 2, 2, 3)) return false;
                break;
            default:
                break;
            }
            return true;
        }
        bool checkline(vector<vector<vector<string>>>& ss, array<pair<int, int>, 6>& selected, int i1, int j1, int i2, int j2, bool reverse) {
            auto &p1 = selected[i1];
            auto x1 = (p1.second + j1) & 0x3;
            auto& p2 = selected[i2];
            auto x2 = (p2.second + j2) & 0x3;
            auto &s1 = ss[p1.first][p1.second >> 2][x1];
            auto &s2 = ss[p2.first][p2.second >> 2][x2];
            int k2 = 0, d2 = 1;
            for (int k1 = 1, k2 = s1.size() - 2; k2 > 0; ++k1, --k2) {
                if (s1[k1] == s2[k2]) return false;
            }
            return true;
        }
        bool checkpoint(vector<vector<vector<string>>>& ss, array<pair<int, int>, 6>& selected, int i1, int j1, int i2, int j2, int i3, int j3) {
            char c1 = getChar(ss, selected, i1, j1);
            char c2 = getChar(ss, selected, i2, j2);
            char c3 = getChar(ss, selected, i3, j3);
            int f = 0;
            if (c1 == '1') ++f;
            if (c2 == '1') ++f;
            if (c3 == '1') ++f;
            return f == 1;
        }
        char getChar(vector<vector<vector<string>>>& ss, array<pair<int, int>, 6>& selected, int i1, int j1) {
            auto& p1 = selected[i1];
            auto x1 = (p1.second + j1) & 0x3;
            auto& s1 = ss[p1.first][p1.second >> 2][x1];
            return s1.front();
        }

    };

    class Solution2Raw {
    public:
        bool composeCube(vector<vector<string>>& shapes) {
            int n = shapes[0].size();
            vector<vector<vector<string>>> ss;
            for (auto& s : shapes) {
                ss.push_back(vector<vector<string>>(2, vector<string>(4, string(n, '0'))));
                auto& ns = ss.back()[0];
                ns[0] = s[0];
                for (int j = 0; j < n; ++j) {
                    ns[1][j] = s[j][n - 1];
                    ns[2][j] = s[n - 1][n - 1 - j];
                    ns[3][j] = s[n - 1 - j][0];
                }
                auto& ns2 = ss.back()[1];
                for (int j = 0; j < n; ++j) {
                    ns2[0][j] = s[0][n - 1 - j];
                    ns2[1][j] = s[j][0];
                    ns2[2][j] = s[n - 1][j];
                    ns2[3][j] = s[n - 1 - j][n - 1];
                }
            }

            unsigned int flag = 0;
            array<pair<int, int>, 6> selected;
            selected[0] = { 0, 0 };
            return traverse(ss, selected, 1, flag);
        }

        bool traverse(vector<vector<vector<string>>>& ss, array<pair<int, int>, 6>& selected, int i, unsigned int flag) {
            if (i == 6) {
                for (auto& s : selected) {
                    cout << "(" << s.first << "," << s.second << ")";
                }
                return true;
            }
            for (int f = 1; f < 6; ++f) {
                if (flag & (1 << f)) continue;
                flag |= (1 << f);
                for (int s = 0; s < 8; ++s) {
                    selected[i] = { f, s };
                    if (!check(ss, selected, i)) {
                        continue;
                    }
                    if (traverse(ss, selected, i + 1, flag)) {
                        return true;
                    }
                }
                flag &= ~(1 << f);
            }
            return false;
        }
        bool check(vector<vector<vector<string>>>& ss, array<pair<int, int>, 6>& selected, int i) {
            switch (i)
            {
            case 1:
                if (!checkline(ss, selected, 0, 0, 1, 0, true)) return false;
                break;
            case 2:
                if (!checkline(ss, selected, 0, 1, 2, 0, true)) return false;
                if (!checkline(ss, selected, 1, 3, 2, 1, true)) return false;
                if (!checkpoint(ss, selected, 0, 1, 1, 0, 2, 1)) return false;
                break;
            case 3:
                if (!checkline(ss, selected, 0, 2, 3, 0, true)) return false;
                if (!checkline(ss, selected, 2, 3, 3, 1, true)) return false;
                if (!checkpoint(ss, selected, 0, 2, 2, 0, 3, 1)) return false;
                break;
            case 4:
                if (!checkline(ss, selected, 0, 3, 4, 0, true)) return false;
                if (!checkline(ss, selected, 3, 3, 4, 1, true)) return false;
                if (!checkline(ss, selected, 4, 3, 1, 1, true)) return false;
                if (!checkpoint(ss, selected, 0, 3, 3, 0, 4, 1)) return false;
                if (!checkpoint(ss, selected, 0, 0, 4, 0, 1, 1)) return false;
                break;
            case 5:
                if (!checkline(ss, selected, 5, 0, 1, 2, true)) return false;
                if (!checkline(ss, selected, 5, 1, 4, 2, true)) return false;
                if (!checkline(ss, selected, 5, 2, 3, 2, true)) return false;
                if (!checkline(ss, selected, 5, 3, 2, 2, true)) return false;

                if (!checkpoint(ss, selected, 5, 0, 2, 2, 1, 3)) return false;
                if (!checkpoint(ss, selected, 5, 1, 1, 2, 4, 3)) return false;
                if (!checkpoint(ss, selected, 5, 2, 4, 2, 3, 3)) return false;
                if (!checkpoint(ss, selected, 5, 3, 3, 2, 2, 3)) return false;
                break;
            default:
                break;
            }
            return true;
        }
        bool checkline(vector<vector<vector<string>>>& ss, array<pair<int, int>, 6>& selected, int i1, int j1, int i2, int j2, bool reverse) {
            auto& p1 = selected[i1];
            auto x1 = (p1.second + j1) & 0x3;
            auto& p2 = selected[i2];
            auto x2 = (p2.second + j2) & 0x3;
            auto& s1 = ss[p1.first][p1.second >> 2][x1];
            auto& s2 = ss[p2.first][p2.second >> 2][x2];
            int k2 = 0, d2 = 1;
            for (int k1 = 1, k2 = s1.size() - 2; k2 > 0; ++k1, --k2) {
                if (s1[k1] == s2[k2]) return false;
            }
            return true;
        }
        bool checkpoint(vector<vector<vector<string>>>& ss, array<pair<int, int>, 6>& selected, int i1, int j1, int i2, int j2, int i3, int j3) {
            char c1 = getChar(ss, selected, i1, j1);
            char c2 = getChar(ss, selected, i2, j2);
            char c3 = getChar(ss, selected, i3, j3);
            int f = 0;
            if (c1 == '1') ++f;
            if (c2 == '1') ++f;
            if (c3 == '1') ++f;
            return f == 1;
        }
        char getChar(vector<vector<vector<string>>>& ss, array<pair<int, int>, 6>& selected, int i1, int j1) {
            auto& p1 = selected[i1];
            auto x1 = (p1.second + j1) & 0x3;
            auto& s1 = ss[p1.first][p1.second >> 2][x1];
            return s1.front();
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
        vector<vector<string>> para = {{"000", "110", "000"}, {"110", "011", "000"}, {"110", "011", "110"}, {"000", "010", "111"}, {"011", "111", "011"}, {"011", "010", "000"}};
        //vector<vector<string>> para = { {"100","110","111"},{"000","011","000"},{"001","111","001"},{"110","010","010"},{"010","011","000"},{"011","011","011"} };
        //vector<vector<string>> para = { {"100","110","111"},{"010", "010","000"}, {"011","011","011"} , {"001","111","001"} ,{"000","110","010"} ,{"110","010","010"} };
        //vector<vector<string>> para = { {"100","110","111"},{"010", "010","000"}, {"011","011","011"} , {"001","111","001"} ,{"000","110","010"} ,{"011","010","010"} };
        vector<int> ipara = { 0,0,2 };
        vector<int> ipara2 = { 2,3,5 };
        Solution s;
        auto actual = s.composeCube(para);
        decltype(actual) expect = true;
        EXPECT_EQ(expect, actual);
    }
}
