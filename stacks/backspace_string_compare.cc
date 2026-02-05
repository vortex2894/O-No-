/*
844. Backspace String Compare


Link: https://leetcode.com/problems/backspace-string-compare/description

Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.

Note that after backspacing an empty text, the text will continue empty.



Example 1:

Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".

Example 2:

Input: s = "ab##", t = "c#d#"
Output: true
Explanation: Both s and t become "".

Example 3:

Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".


Constraints:

    1 <= s.length, t.length <= 200
    s and t only contain lowercase letters and '#' characters.

*/

#include <vector>
#include <iostream>

class Solution
{
public:
    bool backspaceCompare(std::string s, std::string t)
    {
        std::string st_1;
        std::string st_2;

        for (auto ch : s)
        {
            if (ch == '#')
            {
                if (!st_1.empty())
                {
                    st_1.pop_back();
                }
            }
            else
            {
                st_1.push_back(ch);
            }
        }

        for (auto ch : t)
        {
            if (ch == '#')
            {
                if (!st_2.empty())
                {
                    st_2.pop_back();
                }
            }
            else
            {
                st_2.push_back(ch);
            }
        }
        return st_1 == st_2;
    }
};

struct TestCase
{
    std::string s;
    std::string t;
    bool expected;
};

class TestRunner
{
public:
    static void runTests()
    {
        Solution solver;

        std::vector<TestCase> test_cases = {
            {"ab#c", "ad#c", true},
            {"ab##", "c#d#", true}};

        int passed = 0;
        int total = test_cases.size();

        std::cout << "Running " << total << " test cases...\n"
                  << std::endl;

        for (const auto &[s, t, expected] : test_cases)
        {
            bool result = solver.backspaceCompare(s, t);

            if (result == expected)
            {
                std::cout << "✓ PASS: \"" << s << " + " << t << "\" -> \"" << result << "\"" << std::endl;
                passed++;
            }
            else
            {
                std::cout << "✗ FAIL: \"" << s << " + " << t << "\" -> expected \""
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