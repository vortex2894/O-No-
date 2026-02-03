/*
1047. Remove All Adjacent Duplicates In String

Link: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/description

You are given a string s consisting of lowercase English letters. A duplicate removal consists of choosing two adjacent and equal letters and removing them.

We repeatedly make duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made. It can be proven that the answer is unique.



Example 1:

Input: s = "abbaca"
Output: "ca"
Explanation:
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal, and this is the only possible move.  The result of this move is that the string is "aaca", of which only "aa" is possible, so the final string is "ca".


Example 2:

Input: s = "azxxzy"
Output: "ay"



Constraints:

    1 <= s.length <= 10^5
    s consists of lowercase English letters.

*/

#include <unordered_map>
#include <iostream>

class Solution
{
public:
    std::string removeDuplicates(std::string s)
    {
        std::string st;

        for (auto ch : s)
        {
            if (!st.empty() && st.back() == ch)
            {
                st.pop_back();
            }
            else
            {
                st.push_back(ch);
            }
        }

        return st;
    }
};

class TestRunner
{
public:
    static void runTests()
    {
        Solution solver;

        std::unordered_map<std::string, std::string> test_cases = {
            {"abbaca", "ca"},
            {"azxxzy", "ay"}};

        int passed = 0;
        int total = test_cases.size();

        std::cout << "Running " << total << " test cases...\n"
                  << std::endl;

        for (const auto &[input, expected] : test_cases)
        {
            std::string result = solver.removeDuplicates(input);

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