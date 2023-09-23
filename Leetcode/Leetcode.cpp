// Shoran.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "gtest.h"

int main()
{
    //单跑TestMain用例，全跑为Test用例
    //GTEST_RUN_ALL_CASE_FILTER("TestSolution.Test");
    GTEST_RUN_ALL_CASE_FILTER("TestSolution.TestMain");

    //GTEST_RUN_ALL_CASE();

    return 0;
}

