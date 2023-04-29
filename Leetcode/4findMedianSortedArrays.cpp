#include <string>
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
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums2.size() > nums1.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        if (nums2.size() == 0) {
            int n = nums1.size();
            if (n & 1) {
                return nums1[n / 2];
            } else {
                return (nums1[n / 2] + nums1[n / 2 - 1]) / 2.0;
            }
        }
        if (nums1.size() == 1) {
            return (nums1[0] + nums2[0]) / 2.0;
        }

        auto cnt = nums1.size() + nums2.size();
        if (cnt & 1) {
            return getFirstN(nums1, nums2, cnt / 2);
        } else {
            auto xx = getFirstN(nums1, nums2, (cnt - 1) / 2) + getFirstN(nums1, nums2, cnt / 2);
            return xx / 2.0;
        }
 


        return 2.0;
    }
    int getcount(vector<int>& nums1, vector<int>& nums2, int n) {
        auto it1 = lower_bound(nums1.begin(), nums1.end(), n);
        auto it2 = lower_bound(nums2.begin(), nums2.end(), n);
        return (it1 - nums1.begin()) + (it2 - nums2.begin());
    }

    int getFirstN(vector<int>& nums1, vector<int>& nums2, int n) {
        int low = min(nums1[0], nums2[0]);
        int high = max(nums1.back(), nums2.back()) + 1;
        while (low + 1 < high) {
            auto mid = (low + high) / 2;
            auto cnt = getcount(nums1, nums2, mid);
            if ( cnt <= n) {
                low = mid;
            }
            else {
                high = mid;
            }
        }
        return low;
    }
};

class TestSolution4 :public testing::Test
{
public:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};


TEST_F(TestSolution4, Test1)
{
    vector<int> para = {1,3 };
    vector<int> para2 = {2};
    //int expect = 4;

    Solution s;
    auto actual = s.findMedianSortedArrays(para, para2);
    EXPECT_EQ(2.0, actual);
}
TEST_F(TestSolution4, Test2)
{
    vector<int> para = { 1,3 };
    vector<int> para2 = { 2,4 };
    //int expect = 4;

    Solution s;
    auto actual = s.findMedianSortedArrays(para, para2);
    EXPECT_EQ(2.5, actual);
}

}


