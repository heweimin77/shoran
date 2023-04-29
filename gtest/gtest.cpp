// gtest.cpp 
//

#include "gtest.h"



namespace testing
{

TestCase::TestCase(const std::string& casename, const std::string& testname, Test* test)
{
    name_ = testname + "." + casename;
    test->SetName(testname);
    Environment::GetInstance().RegisterTest(test);
    Environment::GetInstance().RegisterTestCase(testname, this);
}

bool TestCase::IsMatch(const string& filter)
{
    return string::npos != name_.find(filter);
}

void TestCase::ShowError()
{
    if (IsError()) {
        std::cout << "[Error] " << name_ << std::endl;
    }
}

void Test::RunTest()
{
    for (auto t : cases_) {
        RunTestCase(t);
    }
}

void Test::RunTest(const std::string& filter)
{
    for (auto t : cases_) {
        if (t->IsMatch(filter)) {
            RunTestCase(t);
        }
    }
}

void Test::RunTestCase(TestCase* testcase)
{
    std::cout << "[ Run ] " + testcase->GetName() << std::endl;
    Setup();
    testcase->RunTestCase();
    TearDown();
    if (testcase->IsError()) {
        std::cout << "[ Failed ] " + testcase->GetName() << std::endl << std::endl;
    } else {
        std::cout << "[ Passed ] " + testcase->GetName() << std::endl << std::endl;

    }
}

void Test::DisplayError()
{
    for (auto t : cases_) {
        if (t->IsError()) {
            t->ShowError();
        }
    }
}

Environment& Environment::GetInstance()
{
    static Environment env;
    return env;
}

void Environment::RegisterTest(Test* tt)
{
    Test* test = nullptr;
    for (auto t : tests_) {
        if (t->GetName() == tt->GetName()) {
            test = t;
            break;
        }
    }

    if (test != nullptr) {
        delete tt;
    } else {
        tests_.push_back(tt);
    }
}

void Environment::RegisterTestCase(const std::string& testname, TestCase* testcase)
{
    Test* test = nullptr;
    for (auto t : tests_) {
        if (t->GetName() == testname) {
            test = t;
            break;
        }
    }
    test->RegisterTestCase(testcase);
}

void Environment::RunAllTestCase()
{
    for (auto t : tests_) {
        t->RunTest();
    }

    for (auto t : tests_) {
        t->DisplayError();
    }
}

void Environment::RunTestCase(const std::string& filter)
{
    for (auto t : tests_) {
        t->RunTest(filter);
    }

    for (auto t : tests_) {
        t->DisplayError();
    }
}

}