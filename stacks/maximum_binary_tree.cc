/*
654. Maximum Binary Tree


Link: https://leetcode.com/problems/maximum-binary-tree/description

You are given an integer array nums with no duplicates. A maximum binary tree can be built recursively from nums using the following algorithm:

    Create a root node whose value is the maximum value in nums.
    Recursively build the left subtree on the subarray prefix to the left of the maximum value.
    Recursively build the right subtree on the subarray suffix to the right of the maximum value.

Return the maximum binary tree built from nums.
Example 1:

Input: nums = [3,2,1,6,0,5]
Output: [6,3,5,null,2,0,null,null,1]
Explanation: The recursive calls are as follow:
- The largest value in [3,2,1,6,0,5] is 6. Left prefix is [3,2,1] and right suffix is [0,5].
    - The largest value in [3,2,1] is 3. Left prefix is [] and right suffix is [2,1].
        - Empty array, so no child.
        - The largest value in [2,1] is 2. Left prefix is [] and right suffix is [1].
            - Empty array, so no child.
            - Only one element, so child is a node with value 1.
    - The largest value in [0,5] is 5. Left prefix is [0] and right suffix is [].
        - Only one element, so child is a node with value 0.
        - Empty array, so no child.

Example 2:

Input: nums = [3,2,1]
Output: [3,null,2,null,1]


Constraints:

    1 <= nums.length <= 1000
    0 <= nums[i] <= 1000
    All integers in nums are unique.


*/

#include <vector>
#include <iostream>
#include <bits/stdc++.h>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class TreeUtils
{
public:
    static void deleteTree(TreeNode *root)
    {
        if (!root)
        {
            return;
        }
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }

    static bool isSameTree(TreeNode *p, TreeNode *q)
    {
        // Both are null -> equal
        if (!p && !q)
            return true;

        // One is null, other isn't -> not equal
        if (!p || !q)
            return false;

        // Compare current node values and recursively compare subtrees
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

class Solution
{
public:
    /*
     * Time Complexity: O(n). Solution using monotoniuc stack builds the tree in a single pass by maintaining nodes in decreasing order.
     * Space Complexity: O(n).
     */
    TreeNode *constructMaximumBinaryTree(std::vector<int> &nums)
    {
        std::vector<TreeNode *> stack;
        for (int num : nums)
        {
            TreeNode *curr = new TreeNode(num);
            while (!stack.empty() && stack.back()->val < num)
            {
                curr->left = stack.back();
                stack.pop_back();
            }
            if (!stack.empty())
            {
                stack.back()->right = curr;
            }
            stack.push_back(curr);
        }
        return stack.front();
    }
};

int main()
{
    Solution solver;

    TreeNode *root = new TreeNode(6);
    root->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    root->left->right->right = new TreeNode(1);
    root->right = new TreeNode(5);
    root->right->left = new TreeNode(0);

    std::vector<int> nums{3, 2, 1, 6, 0, 5};
    TreeNode *res = solver.constructMaximumBinaryTree(nums);

    bool pass1 = TreeUtils::isSameTree(root, res);
    std::cout << "Test 1: " << (pass1 ? "PASS" : "FAIL") << std::endl;
    TreeUtils::deleteTree(root);
    TreeUtils::deleteTree(res);
    std::cout << std::endl;
    return 0;
}