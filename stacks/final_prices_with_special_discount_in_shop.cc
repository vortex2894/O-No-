/*
1475. Final Prices With a Special Discount in a Shop

Link: https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/description

You are given an integer array prices where prices[i] is the price of the ith item in a shop.

There is a special discount for items in the shop. If you buy the ith item,
then you will receive a discount equivalent to prices[j] where j is the minimum index such that j > i and prices[j] <= prices[i].
Otherwise, you will not receive any discount at all.

Return an integer array answer where answer[i] is the final price you will pay for the ith item of the shop, considering the special discount.



Example 1:

Input: prices = [8,4,6,2,3]
Output: [4,2,4,2,3]
Explanation:
For item 0 with price[0]=8 you will receive a discount equivalent to prices[1]=4, therefore, the final price you will pay is 8 - 4 = 4.
For item 1 with price[1]=4 you will receive a discount equivalent to prices[3]=2, therefore, the final price you will pay is 4 - 2 = 2.
For item 2 with price[2]=6 you will receive a discount equivalent to prices[3]=2, therefore, the final price you will pay is 6 - 2 = 4.
For items 3 and 4 you will not receive any discount at all.

Example 2:

Input: prices = [1,2,3,4,5]
Output: [1,2,3,4,5]
Explanation: In this case, for all items, you will not receive any discount at all.

Example 3:

Input: prices = [10,1,1,6]
Output: [9,0,1,6]



Constraints:

    1 <= prices.length <= 500
    1 <= prices[i] <= 1000
*/

#include <vector>
#include <stack>
#include <unordered_map>
#include <iostream>

class Solution
{
public:
    std::vector<int> finalPrices(std::vector<int> &prices)
    {
        /*
        Time complexity: O(2n) => O(n) since Each index is pushed and popped at most once
        Space complexity: O(n) stack can store up to n indices; Prices vector is updated in-place, so no extra result array is needed.
        */
        auto prices_size = prices.size();
        // Стек поддерживает монотонно возрастающую (по индексам) и монотонно убывающую (по значениям) последовательность
        // => паттерн монотонного стека
        std::stack<int> st; // хранит индексы элементов, для которых мы ищем меньший элемент справа

        for (int i = 0; i < prices_size; ++i)
        {
            while (!st.empty() && prices[i] <= prices[st.top()]) // prices[st.top()] — элемент, для которого ищем скидку; Если текущий элемент меньше или равен элементу в стеке → это искомая скидка!
            {
                prices[st.top()] = prices[st.top()] - prices[i]; // Применяем скидку
                st.pop(); // // Убираем из стека, так как нашли для него скидку
            }
            st.push(i);
        }
        // После цикла в стеке остаются элементы без скидки,
        // т.е. элементы, для которых нет меньшего элемента справа, остаются в стеке и возвращаются без изменений.
        return prices;
    }

    std::vector<int> finalPricesUsingBruteForce(std::vector<int> &prices)
    {
        /*
        Time complexity: O(n^2) since there are 2 loops.
        Space complexity: O(n)
        */
        auto prices_size = prices.size();
        std::vector<int> ans;
        ans.reserve(prices_size);

        for (int i = 0; i < prices_size; ++i)
        {
            int current_price = prices[i];
            for (int j = i + 1; j < prices_size; ++j)
            {
                if (prices[j] <= current_price)
                {
                    current_price -= prices[j];
                    break;
                }
                else
                {
                    continue;
                }
            }
            ans.push_back(current_price);
        }

        return ans;
    }
};

struct TestCase
{
    std::vector<int> input;
    std::vector<int> expected;
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
            {{8, 4, 6, 2, 3}, {4, 2, 4, 2, 3}, "Test case 1"},
            {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, "Test case 2"},
            {{10, 1, 1, 6}, {9, 0, 1, 6}, "Test case 3"}};

        int passed = 0;
        int total = test_cases.size();

        std::cout << "Running " << total << " test cases...\n"
                  << std::endl;

        for (const auto &test_case : test_cases)
        {
            auto input = test_case.input;
            const auto expected = test_case.expected;
            const auto result = solver.finalPrices(input);

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