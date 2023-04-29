// gtesth.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

namespace testing
{
class Test;

class TestCase {
public:
    TestCase(const std::string& casename, const std::string& testname, Test* test);
    std::string GetName() { return name_;  }
    
    virtual void RunTestCase() {};
    
    bool IsMatch(const string& filter);

    void RecordError() { _error = true; }
    void ClearError() { _error = false; }
    bool IsError() const { return _error;  }
    void ShowError();

private:
    std::string name_;
    bool _error = false;
};

    
class Test
{
public:
    void SetName(const std::string& testname) { name_ = testname; }
    std::string GetName() const { return name_; }
    void RegisterTestCase(TestCase *testcase) { cases_.push_back(testcase); }

    virtual void Setup() {}
    virtual void TearDown() {}

    void RunTest();
    void RunTest(const std::string &filter);
    void RunTestCase(TestCase *testcase);
    
    void DisplayError();

private:
    std::string name_;
    std::vector<TestCase *> cases_;

};

class Environment
{
public:
    static Environment& GetInstance();

    void RegisterTest(Test *t);
    void RegisterTestCase(const std::string& testname, TestCase* testcase);

    void RunAllTestCase();
    void RunTestCase(const std::string& filter);

private:
    Environment() {}
    ~Environment() {}

private:
    std::vector<Test*> tests_;

};

}

#define TEST_F(testname, testcasename)  \
class testcasename : public testing::TestCase    \
{\
public:\
    testcasename() : TestCase(#testcasename, #testname, new testname()) {}\
    virtual void RunTestCase(); \
} a##testname##testcasename; \
void testcasename::RunTestCase()

#define GTEST_RUN_ALL_CASE()    \
testing::Environment::GetInstance().RunAllTestCase();

#define GTEST_RUN_ALL_CASE_FILTER(filter) \
testing::Environment::GetInstance().RunTestCase(filter);

#define EXPECT_TRUE(x)  \
if(!(x)) {\
    RecordError();\
    std::cout << "Assert failed"<<  std::endl ; \
}

#define EXPECT_FALSE(x)  \
if(x) {\
    RecordError();\
    std::cout  << "Assert failed"<<  std::endl; \
}

#define EXPECT_EQ(expect, actual)  \
{ \
    auto left = (expect); \
    auto right = (actual); \
    if(left != right) { \
        RecordError(); \
        std::cout << "Assert failed, " \
                  << "expect(" << left << "), "  \
                  << "actual(" << right << "). " << std::endl;  \
    } \
}

template <class Stream, class Container>
inline void output(Stream &os, Container c)
{
    if (!c.empty()) {
        auto it = c.begin();
        os << *it;
        for (++it; it != c.end(); ++it) {
            os << ", " << *it;
        }
    }
}

#define EXPECT_EQ_COMPLEX_CONTAINER(expect, actual)  \
{ \
    auto &left = (expect); \
    auto &right = (actual); \
    if(left != right) { \
        RecordError(); \
        std::cout << "Assert failed, " \
                  << "expect("; \
        std::cout << "), "  << "actual("; \
        std::cout << "). "<< std::endl ;  \
    } \
}

#define EXPECT_EQ_CONTAINER(expect, actual)  \
{ \
    auto &left = (expect); \
    auto &right = (actual); \
    if(left != right) { \
        RecordError(); \
        std::cout << "Assert failed, " \
                  << "expect("; \
        output(std::cout, left);\
        std::cout << "), "  << "actual("; \
        output(std::cout, right);\
        std::cout << "). " << std::endl ;  \
    } \
}


#define EXPECT_NE(x, y)  \
{ \
    auto left = (x); \
    auto right = (y); \
    if(left == right) { \
        RecordError(); \
        std::cout << "Assert failed. " << std::endl; \
    } \
} 