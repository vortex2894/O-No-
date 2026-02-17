/*
114. Flatten Binary Tree to Linked List


Link: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description

Given the root of a binary tree, flatten the tree into a "linked list":

    The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
    The "linked list" should be in the same order as a pre-order traversal of the binary tree.

Example 1:

Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]

Example 2:

Input: root = []
Output: []

Example 3:

Input: root = [0]
Output: [0]


Constraints:

    The number of nodes in the tree is in the range [0, 2000].
    -100 <= Node.val <= 100

*/

#include <string>
#include <vector>
#include <queue>
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
};

class Solution
{
public:
    TreeNode *prev = nullptr;
    /*
     * Time Complexity: O(n). Each node is visited exactly once.
     * Space Complexity: O(h).  Recursion stack space (height of tree).
     * Worst case: O(n) (skewed tree)
     */
    void flatten(TreeNode *root)
    {
        if (root == nullptr)
        {
            return;
        }
        flatten(root->right);
        flatten(root->left);

        root->left = nullptr;
        root->right = prev;
        prev = root;
    }
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

int main()
{
    Solution solver;

    // Test Case: simple binary tree
    //       1
    //      / \
    //     2   5
    //    / \   \
    //   3   4   6

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(6);

    std::cout << "Original tree (pre-order): 1, 2, 3, 4, 5, 6" << std::endl;
    solver.flatten(root);

    std::cout << "Flattened tree: ";
    TreeNode *curr = root;
    std::vector<int> result;
    while (curr)
    {
        result.push_back(curr->val);
        if (curr->left)
        {
            std::cout << "ERROR: Left child not null at node " << curr->val << "!" << std::endl;
        }
        curr = curr->right;
    }
    std::cout << result << std::endl;
    TreeUtils::deleteTree(root);
    std::cout << std::endl;
    return 0;
}