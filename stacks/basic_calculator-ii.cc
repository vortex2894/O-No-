/*
227. Basic Calculator II

Link: https://leetcode.com/problems/basic-calculator-ii/description

Given a string s which represents an expression, evaluate this expression and return its value.

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().


Example 1:

Input: s = "3+2*2"
Output: 7

Example 2:

Input: s = " 3/2 "
Output: 1

Example 3:

Input: s = " 3+5 / 2 "
Output: 5



Constraints:

    1 <= s.length <= 3 * 105
    s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
    s represents a valid expression.
    All the integers in the expression are non-negative integers in the range [0, 231 - 1].
    The answer is guaranteed to fit in a 32-bit integer.


*/

#include <string>
#include <unordered_map>
#include <iostream>
#include <cassert>
#include <stack>

class Solution
{
public:
    /*
     * Time complexity: O(n)
     * Space complexity: O(n)
     */
    int calculate(std::string s)
    {
        std::stack<int> st;
        char previous_operator = '+'; // By default it is '+' in order to just push the first number to stack
        int i = 0;
        int str_size = s.size();

        while (i < str_size)
        {
            if (s[i] == ' ')
            {
                ++i;
            }
            else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
            {
                // Important: operator is applied not to the previous but to the next number which will be read from the string.
                previous_operator = s[i];
                ++i;
            }
            else
            {
                int num = 0;
                while (i < str_size && isdigit(s[i]))
                {
                    // Standard trick to convert digit as char to int
                    // '0' has ASCII-code = 48
                    num = (num * 10) + (s[i] - '0');
                    ++i;
                }
                if (previous_operator == '+')
                {
                    st.push(num);
                }
                else if (previous_operator == '-')
                {
                    st.push(num * (-1));
                }
                else
                {
                    int x = st.top();
                    st.pop();
                    previous_operator == '*'
                        ? st.push(num * x)
                        : st.push(x / num);
                }
            }
        }

        int ans = 0;
        while (!st.empty())
        {
            ans += st.top();
            st.pop();
        }

        return ans;
    }
};

class TestRunner
{
public:
    static void runTests()
    {
        Solution solver;

        std::unordered_map<std::string, int> test_cases = {
            {"3+2*2", 7},
            {"3/2", 1},
            {" 3+5 / 2 ", 5}};

        int passed = 0;
        int total = test_cases.size();

        std::cout << "Running " << total << " test cases...\n"
                  << std::endl;

        for (const auto &[input, expected] : test_cases)
        {
            int result = solver.calculate(input);

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