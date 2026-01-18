/*
2696. Minimum String Length After Removing Substrings

Link: https://leetcode.com/problems/minimum-string-length-after-removing-substrings/description/

You are given a string s consisting only of uppercase English letters.

You can apply some operations to this string where, in one operation, you can remove any occurrence of one of the substrings "AB" or "CD" from s.

Return the minimum possible length of the resulting string that you can obtain.

Note that the string concatenates after removing the substring and could produce new "AB" or "CD" substrings.



Example 1:

Input: s = "ABFCACDB"
Output: 2
Explanation: We can do the following operations:
- Remove the substring "ABFCACDB", so s = "FCACDB".
- Remove the substring "FCACDB", so s = "FCAB".
- Remove the substring "FCAB", so s = "FC".
So the resulting length of the string is 2.
It can be shown that it is the minimum length that we can obtain.

Example 2:

Input: s = "ACBBD"
Output: 5
Explanation: We cannot do any operations on the string so the length remains the same.


Constraints:

    1 <= s.length <= 100
    s consists only of uppercase English letters.


*/

#include <vector>
#include <stack>
#include <unordered_map>
#include <iostream>

class Solution
{
public:
    int minLength(std::string s)
    /*
        Time complexity: O(n)
        Space complexity: O(n)
     */
    {
        std::stack<char> st;
        for (const auto &ch : s)
        {
            if (!st.empty() && ((ch == 'B' && st.top() == 'A') || (ch == 'D' && st.top() == 'C')))
            {
                st.pop();
            }
            else
            {
                st.push(ch);
            }
        }
        return st.size();
    }
};

class TestRunner
{
public:
    static void runTests()
    {
        Solution solver;

        std::unordered_map<std::string, int> test_cases = {
            {"ABFCACDB", 2},
            {"ACBBD", 5}};

        int passed = 0;
        int total = test_cases.size();

        std::cout << "Running " << total << " test cases...\n"
                  << std::endl;

        for (const auto &[input, expected] : test_cases)
        {
            int result = solver.minLength(input);

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