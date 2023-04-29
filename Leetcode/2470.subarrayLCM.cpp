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
#include <stack>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int subarrayLCM(vector<int> &nums, int k)
    {
        int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 };
        vector<int> factors;
        int ff = 1;
        for (int i = 0; i < sizeof(primes) / sizeof(primes[0]); ++i) {
            if (k % primes[i] == 0) {
                int factor = primes[i];
                while (k % factor == 0) factor *= primes[i];
                factor /= primes[i];
                factors.push_back(factor);
                ff *= factor;
            }
        }
        if (ff != k) factors.push_back(k / ff);
        
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            unsigned flag = (1 << factors.size()) - 1;
            int j = i;
            for (; j < nums.size(); ++j) {
                int n = nums[j];
                if (k % n != 0) {
                    i = j;
                    break;
                }
                for (int k = 0; k < factors.size(); ++k) {
                    if (n % factors[k] == 0) {
                        flag &= ~(1 << k);
                    }
                }
                if (flag == 0) break;
            }
            if (flag == 0) {
                for (; j < nums.size() && k % nums[j] == 0; ++j) ++result;
            }
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
    vector<int> nums = { 831, 897, 603, 482, 826, 360, 766, 559, 717, 185, 903, 184, 416, 513, 549, 516, 651, 482, 631, 259, 714, 452, 148, 971, 778, 636, 363, 290, 251, 783, 411, 444, 872, 898, 106, 775, 681, 202, 947, 559, 826, 557, 357, 98, 198, 180, 512, 38, 744, 409, 922, 623, 758, 469, 836, 43, 689, 13, 847, 589, 821, 218, 547, 24, 220, 795, 250, 247, 252, 448, 376, 465, 949, 558, 849, 600, 251, 318, 831, 599, 310, 724, 596, 719, 490, 451, 446, 234, 329, 228, 411, 126, 559, 123, 248, 295, 167, 696, 79, 987, 925, 491, 651, 5, 135, 792, 745, 199, 26, 173, 119, 671, 4, 780, 254, 965, 609, 174, 888, 644, 196, 967, 33, 947, 54, 496, 473, 949, 767, 35, 115, 285, 612, 447, 699, 663, 907, 124, 581, 462, 348, 630, 784, 368, 150, 450, 779, 572, 930, 282, 721, 359, 439, 45, 639, 192, 843, 939, 371, 184, 560, 755, 816, 840, 735, 272, 173, 987, 657, 240, 791, 434, 683, 873, 8, 906, 43, 544, 230, 869, 448, 715, 574, 663, 491, 188, 290, 595, 985, 141, 484, 718, 224, 774, 658, 194, 19, 717, 878, 326, 137, 464, 205, 801, 81, 885, 447, 127, 171, 387, 472, 940, 265, 883, 823, 455, 426, 736, 520, 22, 443, 167, 566, 70, 430, 374, 686, 914, 144, 704, 275, 531, 960, 623, 940, 931, 202, 908, 628, 45, 620, 172, 708, 3, 993, 905, 935, 592, 333, 803, 526, 387, 199, 623, 172, 973, 937, 886, 502, 504, 61, 555, 292, 453, 575, 143, 27, 44, 630, 252, 684, 16, 500, 213, 898, 349, 479, 388, 30, 569, 498, 35, 628, 17, 136, 221, 546, 310, 264, 481, 490, 795, 992, 517, 126, 504, 888, 255, 910, 580, 559, 742, 298, 143, 963, 84, 659, 400, 122, 129, 171, 300, 936, 53, 274, 847, 430, 798, 590, 238, 170, 21, 765, 304, 587, 219, 618, 50, 981, 466, 141, 778, 677, 125, 33, 647, 166, 713, 361, 133, 265, 252, 412, 258, 163, 956, 969, 117, 552, 335, 639, 773, 808, 930, 919, 289, 812, 723, 843, 745, 453 };
    Solution s;
    auto actual = s.subarrayLCM(nums, 771);
    decltype(actual) expect = 0;
    EXPECT_EQ(expect, actual);
    
}

}
