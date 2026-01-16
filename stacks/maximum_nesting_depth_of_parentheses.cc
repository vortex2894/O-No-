/*
1614. Maximum Nesting Depth of the Parentheses

Link: https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/description

Given a valid parentheses string s, return the nesting depth of s. The nesting depth is the maximum number of nested parentheses.

Example 1:

Input: s = "(1+(2*3)+((8)/4))+1"

Output: 3

Explanation:

Digit 8 is inside of 3 nested parentheses in the string.

Example 2:

Input: s = "(1)+((2))+(((3)))"

Output: 3

Explanation:

Digit 3 is inside of 3 nested parentheses in the string.

Example 3:

Input: s = "()(())((()()))"

Output: 3



Constraints:

    1 <= s.length <= 100
    s consists of digits 0-9 and characters '+', '-', '*', '/', '(', and ')'.
    It is guaranteed that parentheses expression s is a VPS.

*/

#include <string>
#include <unordered_map>
#include <iostream>
#include <cassert>
#include <algorithm>

class Solution
{
public:
    int maxDepth(std::string s)
    {
        /*
            Time complexity: O(n) since we iterate over our string only once!
            Space complexity: O(1)
        */
        int max_depth_found = 0;
        int current_depth = 0;

        for (auto &ch : s)
        {
            if (ch == '(')
            {
                max_depth_found = std::max(max_depth_found, ++current_depth);
            }
            else if (ch == ')')
            {
                --current_depth;
            }
            else
            {
                continue;
            }
        }
        return max_depth_found;
    }
};

class TestRunner
{
public:
    static void runTests()
    {
        Solution solver;

        std::unordered_map<std::string, int> test_cases = {
            {"(1+(2*3)+((8)/4))+1", 3},
            {"(1)+((2))+(((3)))", 3},
            {"()(())((()()))", 3}};

        int passed = 0;
        int total = test_cases.size();

        std::cout << "Running " << total << " test cases...\n"
                  << std::endl;

        for (const auto &[input, expected] : test_cases)
        {
            int result = solver.maxDepth(input);

            if (result == expected)
            {
                std::cout << "✓ PASS: \"" << input << "\" -> \"" << result << "\"" << std::endl;
                passed++;
            }
            else
            {
                std::cout << "✗ FAIL: \"" << input << "\" -> expected \""
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