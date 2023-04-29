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
        struct Info {
            Info(int l, int v) : level(l), flvl(l), cnt(1), deltas({ v }) {}
            int level;
            int cnt;
            int flvl;
            vector<int> deltas;
        };
    public:
        int getMaxLayerSum(TreeNode* root) {
            vector<vector<TreeNode*>> nodes;
            traverse(root, 0, nodes);
            vector<int> sums(nodes.size());
            int i = 0;
            for (auto& ns : nodes) {
                int s = 0;
                for (auto& n : ns) {
                    s += n->val;
                }
                sums[i++] = s;
            }
            int result = *max_element(sums.begin(), sums.end());

            vector<Info> infos;
            for (int i = nodes.size() - 1; i >= 0; --i) {
                for (auto& n : nodes[i]) {
                    if ((n->left == nullptr) && (n->right == nullptr)) {
                        if (i != nodes.size() - 1 || (1 != nodes.back().size())) {
                            int r = sums[i] - n->val;
                            result = max(result, r);
                        }
                        infos.push_back(Info(i, n->val));
                        infos.back().flvl -= 1;
                        n->val = infos.size() - 1;
                        continue;
                    }
                    Info* base = nullptr, * exp = nullptr;
                    int index = 0;
                    if (n->left != nullptr && n->right != nullptr) {
                        index = n->left->val;
                        base = &infos[n->left->val];
                        exp = &infos[n->right->val];
                        if (base->level < exp->level) {
                            index = n->right->val;
                            swap(base, exp);
                        }
                        if (exp->level == base->level) {
                            base->cnt += exp->cnt;
                        }
                        int d = base->level - exp->level;
                        for (int i = 0; i < exp->deltas.size(); ++i) {
                            base->deltas[i + d] += exp->deltas[i];
                        }
                        base->flvl = max(base->flvl, exp->level);
                    } else if (n->left != nullptr) {
                        index = n->left->val;
                        base = &infos[n->left->val];
                    } else {
                        index = n->right->val;
                        base = &infos[n->right->val];
                    }
                    base->deltas.push_back(n->val);
                    n->val = index;

                    if (n->left == nullptr || n->right == nullptr) {
                        int lvl = base->level;
                        if (n->left != nullptr && n->right != nullptr) {
                            int i = base->deltas.size() - 1;
                            int r = sums[lvl - i] - base->deltas[i] + base->deltas[i - 1];
                            //cout << nn << ", r3: " << r << endl;
                            result = max(result, r);
                        } else {
                            if (lvl != nodes.size() - 1 || (base->cnt != nodes.back().size())) {
                                int r = sums[lvl] - base->deltas[0];
                                //cout << nn << ", r2: " << r << endl;
                                result = max(result, r);
                            }
                            for (int i = max(1, lvl - base->flvl); i < base->deltas.size(); ++i) {
                                int r = sums[lvl - i] - base->deltas[i] + base->deltas[i - 1];
                                //cout << nn << ", r3: " << r << endl;
                                result = max(result, r);
                            }
                        }
                        base->flvl = lvl - base->deltas.size();
                    }
                }
            }
            return result;
        }

        void traverse(TreeNode* node, size_t lay, vector<vector<TreeNode*>>& nodes) {
            if (lay == nodes.size()) {
                nodes.push_back({ node });
            }
            else {
                nodes[lay].push_back(node);
            }
            if (node->left) traverse(node->left, lay + 1, nodes);
            if (node->right) traverse(node->right, lay + 1, nodes);
        }

    };

    class Solution2Timeout {
        struct Info {
            Info(int l, int v) : level(l), cnt(1), deltas({ v }) {}
            int level;
            int cnt;
            vector<int> deltas;
        };
    public:
        int getMaxLayerSum(TreeNode* root) {

            vector<vector<TreeNode*>> nodes;
            traverse(root, 0, nodes);
            vector<int> sums(nodes.size());
            int i = 0;
            for (auto& ns : nodes) {
                int s = 0;
                for (auto& n : ns) {
                    s += n->val;
                }
                sums[i++] = s;
            }
            int result = *max_element(sums.begin(), sums.end());

            vector<Info> infos;
            for (int i = nodes.size() - 1; i >= 0; --i) {
                for (auto& n : nodes[i]) {
                    //int nn = n->val;
                    if ((n->left == nullptr) && (n->right == nullptr)) {
                        if (i != nodes.size() - 1 || (1 != nodes.back().size())) {
                            int r = sums[i] - n->val;
                            result = max(result, r);
                            //cout << nn << ", r1: " << r << endl;
                        }
                        infos.push_back(Info(i, n->val));
                        n->val = infos.size() - 1;
                        continue;
                    }
                    Info* base = nullptr, * exp = nullptr;
                    int index = 0;
                    if (n->left != nullptr && n->right != nullptr) {
                        index = n->left->val;
                        base = &infos[n->left->val];
                        exp = &infos[n->right->val];
                        if (base->level < exp->level) {
                            index = n->right->val;
                            swap(base, exp);
                        }
                        if (exp->level == base->level) {
                            base->cnt += exp->cnt;
                        }
                        int d = base->level - exp->level;
                        for (int i = 0; i < exp->deltas.size(); ++i) {
                            base->deltas[i + d] += exp->deltas[i];
                        }
                    }
                    else if (n->left != nullptr) {
                        index = n->left->val;
                        base = &infos[n->left->val];
                    }
                    else {
                        index = n->right->val;
                        base = &infos[n->right->val];
                    }
                    base->deltas.push_back(n->val);
                    n->val = index;

                    if (n->left == nullptr || n->right == nullptr) {
                        int lvl = base->level;
                        if (n->left != nullptr && n->right != nullptr) {
                            int i = base->deltas.size() - 1;
                            int r = sums[lvl - i] - base->deltas[i] + base->deltas[i - 1];
                            //cout << nn << ", r3: " << r << endl;
                            result = max(result, r);
                        }
                        else {
                            if (lvl != nodes.size() - 1 || (base->cnt != nodes.back().size())) {
                                int r = sums[lvl] - base->deltas[0];
                                //cout << nn << ", r2: " << r << endl;
                                result = max(result, r);
                            }
                            for (int i = 1; i < base->deltas.size(); ++i) {
                                int r = sums[lvl - i] - base->deltas[i] + base->deltas[i - 1];
                                //cout << nn << ", r3: " << r << endl;
                                result = max(result, r);
                            }
                        }
                    }
                }
            }
            return result;
        }

        void traverse(TreeNode* node, size_t lay, vector<vector<TreeNode*>>& nodes) {
            if (lay == nodes.size()) {
                nodes.push_back({ node });
            }
            else {
                nodes[lay].push_back(node);
            }
            if (node->left) traverse(node->left, lay + 1, nodes);
            if (node->right) traverse(node->right, lay + 1, nodes);
        }

        void traverse2(TreeNode* node, size_t lay, vector<int>& laysums, vector<int>& laycnts, vector<int>& delta, int& result, int& mlay, int& mcnt) {

            vector<int> d1, d2;
            int mlay1 = lay, mcnt1 = 1;
            if (node->left) traverse2(node->left, lay + 1, laysums, laycnts, d1, result, mlay1, mcnt1);
            if (node->right) traverse2(node->right, lay + 1, laysums, laycnts, d2, result, mlay1, mcnt1);
            size_t sz = max(lay + 1, d1.size());
            sz = max(sz, d2.size());
            delta.resize(sz);
            delta[lay] += node->val;
            for (int i = lay + 1; i < d1.size(); ++i) {
                delta[i] += d1[i];
            }
            for (int i = lay + 1; i < d2.size(); ++i) {
                delta[i] += d2[i];
            }
            if (!(node->left != nullptr && node->right != nullptr)) {
                for (int i = lay; i < delta.size() - 1; ++i) {
                    int r = laysums[i] - delta[i] + delta[i + 1];
                    result = max(result, r);
                }
                int i = delta.size() - 1;
                if (mlay1 != i || mcnt1 != laycnts[i]) {
                    int r = laysums[i] - delta[i];
                    result = max(result, r);
                }
            }
            if (mlay1 > mlay) {
                mlay = mlay1;
                mcnt = mcnt1;
            }
            else if (mlay1 == mlay) {
                mcnt += mcnt1;
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
        vector<int> para = { 5,3,7 };
        vector<string> spara = { "hold","engineer","cost","level" };
        Solution s;
        TreeNode* root = createTree({ 7,7,3,6,NULL_VALUE,2,NULL_VALUE,5,4,9,NULL_VALUE,1,5,NULL_VALUE,NULL_VALUE,99,NULL_VALUE,100,50 });
        auto actual = s.getMaxLayerSum(root);
        decltype(actual) expect = 249;
        destroyTree(root);
        EXPECT_EQ(expect, actual);
    }
}



