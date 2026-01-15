/*
682. Baseball Game

Link: https://leetcode.com/problems/baseball-game/description/

You are keeping the scores for a baseball game with strange rules. At the beginning of the game, you start with an empty record.

You are given a list of strings operations, where operations[i] is the ith operation you must apply to the record and is one of the following:

    An integer x.
        Record a new score of x.
    '+'.
        Record a new score that is the sum of the previous two scores.
    'D'.
        Record a new score that is the double of the previous score.
    'C'.
        Invalidate the previous score, removing it from the record.

Return the sum of all the scores on the record after applying all the operations.

The test cases are generated such that the answer and all intermediate calculations fit in a 32-bit integer and that all operations are valid.



Example 1:

Input: ops = ["5","2","C","D","+"]
Output: 30
Explanation:
"5" - Add 5 to the record, record is now [5].
"2" - Add 2 to the record, record is now [5, 2].
"C" - Invalidate and remove the previous score, record is now [5].
"D" - Add 2 * 5 = 10 to the record, record is now [5, 10].
"+" - Add 5 + 10 = 15 to the record, record is now [5, 10, 15].
The total sum is 5 + 10 + 15 = 30.

Example 2:

Input: ops = ["5","-2","4","C","D","9","+","+"]
Output: 27
Explanation:
"5" - Add 5 to the record, record is now [5].
"-2" - Add -2 to the record, record is now [5, -2].
"4" - Add 4 to the record, record is now [5, -2, 4].
"C" - Invalidate and remove the previous score, record is now [5, -2].
"D" - Add 2 * -2 = -4 to the record, record is now [5, -2, -4].
"9" - Add 9 to the record, record is now [5, -2, -4, 9].
"+" - Add -4 + 9 = 5 to the record, record is now [5, -2, -4, 9, 5].
"+" - Add 9 + 5 = 14 to the record, record is now [5, -2, -4, 9, 5, 14].
The total sum is 5 + -2 + -4 + 9 + 5 + 14 = 27.

Example 3:

Input: ops = ["1","C"]
Output: 0
Explanation:
"1" - Add 1 to the record, record is now [1].
"C" - Invalidate and remove the previous score, record is now [].
Since the record is empty, the total sum is 0.



Constraints:

    1 <= operations.length <= 1000
    operations[i] is "C", "D", "+", or a string representing an integer in the range [-3 * 104, 3 * 104].
    For operation "+", there will always be at least two previous scores on the record.
    For operations "C" and "D", there will always be at least one previous score on the record.

*/

#include <vector>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <bits/stdc++.h>

class Solution {
public:
    int calPoints(std::vector<std::string>& operations) {
        std::vector<int> scores;
        
        for (const auto& op : operations) {
            if (op == "C") {
                if (!scores.empty()) {
                    scores.pop_back();
                }
            } else if (op == "D") {
                if (!scores.empty()) {
                    scores.push_back(scores.back() * 2);
                }
            } else if (op == "+") {
                if (scores.size() >= 2) {
                    int sum = scores[scores.size() - 1] + scores[scores.size() - 2];
                    scores.push_back(sum);
                }
            } else {
                bool isNumber = !op.empty() && 
                    (op[0] == '-' || std::isdigit(op[0])) &&
                    std::all_of(op.begin() + 1, op.end(), 
                               [](char c) { return std::isdigit(c); });
                
                if (isNumber) {
                    scores.push_back(std::stoi(op));
                }
            }
        }
        
        return std::accumulate(scores.begin(), scores.end(), 0);
    }
};

struct TestCase
{
    std::vector<std::string> input;
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
            {{"5", "2", "C", "D", "+"}, 30, "Test case 1"},
            {{"5", "-2", "4", "C", "D", "9", "+", "+"}, 27, "Test case 2"},
            {{"1", "C"}, 0, "Test case 3"}};

        int passed {0};
        auto total {test_cases.size()};

        std::cout << "Running " << total << " test cases...\n"
                  << std::endl;

        for (const auto &test_case : test_cases)
        {
            auto input {test_case.input};
            const auto expected {test_case.expected};
            const auto result {solver.calPoints(input)};

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