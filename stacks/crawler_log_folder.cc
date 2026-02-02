/*
1598. Crawler Log Folder


https://leetcode.com/problems/crawler-log-folder/description

The Leetcode file system keeps a log each time some user performs a change folder operation.

The operations are described below:

    "../" : Move to the parent folder of the current folder. (If you are already in the main folder, remain in the same folder).
    "./" : Remain in the same folder.
    "x/" : Move to the child folder named x (This folder is guaranteed to always exist).

You are given a list of strings logs where logs[i] is the operation performed by the user at the ith step.

The file system starts in the main folder, then the operations in logs are performed.

Return the minimum number of operations needed to go back to the main folder after the change folder operations.



Example 1:

Input: logs = ["d1/","d2/","../","d21/","./"]
Output: 2
Explanation: Use this change folder operation "../" 2 times and go back to the main folder.

Example 2:

Input: logs = ["d1/","d2/","./","d3/","../","d31/"]
Output: 3

Example 3:

Input: logs = ["d1/","../","../","../"]
Output: 0



Constraints:

    1 <= logs.length <= 103
    2 <= logs[i].length <= 10
    logs[i] contains lowercase English letters, digits, '.', and '/'.
    logs[i] follows the format described in the statement.
    Folder names consist of lowercase English letters and digits.



*/

#include <vector>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <string>

class Solution
{
public:
    int minOperations(std::vector<std::string> &logs)
    {
        std::stack<std::string> st;
        for (auto log : logs) {
            if ((log == "../" && st.empty()) || log == "./") {
                continue;
            } else if (log == "../" && !st.empty()) {
                st.pop();
            } else {
                st.push(log);
            }
        }
        return st.size();
        
    }
};

struct TestCase
{
    std::vector<std::string> logs;
    int expected;
    std::string description;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

class TestRunner
{
public:
    static void runTests()
    {
        Solution solver;

        std::vector<TestCase> test_cases = {
            {{"d1/","d2/","../","d21/","./"}, 2, "Test case 1"},
            {{"d1/","d2/","./","d3/","../","d31/"}, 3, "Test case 2"},
            {{"d1/","../","../","../"}, 0, "Test case 3"}
        };

        int passed{0};
        auto total{test_cases.size()};

        std::cout << "Running " << total << " test cases...\n"
                  << std::endl;

        for (const auto &test_case : test_cases)
        {
            auto logs{test_case.logs};
            const auto expected{test_case.expected};
            const auto result{solver.minOperations(logs)};

            if (result == expected)
            {
                std::cout << "✓ PASS: \"" << logs << "\" -> \"" << result << "\"" << std::endl;
                passed++;
            }
            else
            {
                std::cout << "✗ FAIL: \"" << logs << "\" -> expected \""
                          << expected << "\", got \"" << result << "\"" << std::endl;
            }
        }

        std::cout << "\n"
                  << std::string(40, '-') << std::endl;
        std::cout << "Results: " << passed << "/" << total << " tests passed" << std::endl;

        if (passed == total)
        {
            std::cout << "✅ All tests passed!" << std::endl;
        }
        else
        {
            std::cout << "❌ Some tests failed!" << std::endl;
            exit(1);
        }
    }
};

int main(int argc, char const *argv[])
{
    TestRunner::runTests();
    return 0;
}