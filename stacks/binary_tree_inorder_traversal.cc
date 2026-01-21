/*
897. Increasing Order Search Tree

Link: https://leetcode.com/problems/binary-tree-inorder-traversal/description

Given the root of a binary tree, return the inorder traversal of its nodes' values.


Example 1:

Input: root = [1,null,2,3]

Output: [1,3,2]

Explanation: see the related figure.

Example 2:

Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]

Output: [4,2,6,5,7,1,3,9,8]

Explanation: see the related figure.

Example 3:

Input: root = []

Output: []

Example 4:

Input: root = [1]

Output: [1]

Constraints:

    The number of nodes in the tree is in the range [0, 100].
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
    TreeNode(int x = 0) : val(x), left(nullptr), right(nullptr) {}
};

class TreeUtils
{
public:
    static void deleteTree(TreeNode *root)
    {
        if (!root)
            return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
};

class Solution
{
public:
private:
    std::vector<int> values;

    /*
     * Inorder traversal means visiting a binary tree in the order Left → Root → Right.
     * Time complexity:  O(n) — Every node is visited exactly once.
     *
     * Space complexity: O(n) in the worst case (skewed tree) due to recursion stack.
     *                   O(h) in the average case where h = height of tree, plus the output list.
     */
    void inorder(TreeNode *node)
    {
        if (!node)
        {
            return;
        }

        inorder(node->left);
        values.push_back(node->val);
        inorder(node->right);
    }

public:
    std::vector<int> inorderTraversal(TreeNode *root)
    {
        if (root == NULL)
        {
            return this->values;
        }
        inorder(root);
        return this->values;
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

    std::vector<int> v1 = {1, 2, 3};

    std::vector<int> expected = {1, 3, 2};

    TreeNode *input = new TreeNode(v1[0]);
    input->right = new TreeNode(v1[1]);
    input->right->left = new TreeNode(v1[2]);

    std::vector<int> res_vec = solver.inorderTraversal(input);

    bool pass1 = (res_vec == expected);
    std::cout << "Test 1: " << (pass1 ? "PASS" : "FAIL") << v1 << " → " << res_vec << "\n";
    
    TreeUtils::deleteTree(input);
    return 0;
}