/*
1021. Remove Outermost Parentheses

Link: https://leetcode.com/problems/remove-outermost-parentheses/description/

A valid parentheses string is either empty "", "(" + A + ")", or A + B,
where A and B are valid parentheses strings, and + represents string concatenation.

    For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.

A valid parentheses string s is primitive if it is nonempty,
and there does not exist a way to split it into s = A + B, with A and B nonempty valid parentheses strings.

Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk,
where Pi are primitive valid parentheses strings.

Return s after removing the outermost parentheses of every primitive string in the primitive decomposition of s.



Example 1:

Input: s = "(()())(())"
Output: "()()()"
Explanation:
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Example 2:

Input: s = "(()())(())(()(()))"
Output: "()()()()(())"
Explanation:
The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".

Example 3:

Input: s = "()()"
Output: ""
Explanation:
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".



Constraints:

    1 <= s.length <= 105
    s[i] is either '(' or ')'.
    s is a valid parentheses string.


*/

#include <string>
#include <unordered_map>
#include <iostream>
#include <cassert>

class Solution
{
public:
    std::string removeOuterParentheses(std::string s)
    {
        /*
        Time complexity: O(n) since we iterate over our string only once!
        Space complexity: O(n) -> for ans string which is required!
        */
        if (s.empty())
        {
            return s;
        }

        std::string ans;
        ans.reserve(s.size()); // // Резервируем память заранее иначе строка ans будет многократно переаллоцироваться.

        int depth{0};

        for (auto &ch : s)
        {
            if (ch == '(')
            {
                if (depth == 0) // вне любой примитивной части
                {
                    ++depth; // Внешняя открывающая скобка - не добавляем
                }
                else
                {
                    ++depth; // Внутренняя скобка
                    ans += ch; // Добавляем в результат
                }
            }
            else
            {
                if (depth == 1) // на внешнем уровне примитивной части
                {
                    --depth; // Закрывающая внешняя скобка - не добавляем
                }
                else
                {
                    --depth; // Внутренняя скобка
                    ans += ch; // Добавляем в результат
                }
            }
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

        std::unordered_map<std::string, std::string> test_cases = {
            {"(()())(())", "()()()"},
            {"(()())(())(()(()))", "()()()()(())"},
            {"()()", ""}};

        int passed = 0;
        int total = test_cases.size();

        std::cout << "Running " << total << " test cases...\n"
                  << std::endl;

        for (const auto &[input, expected] : test_cases)
        {
            std::string result = solver.removeOuterParentheses(input);

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