/*
1008. Construct Binary Search Tree from Preorder Traversal


Link: https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/description

Given an array of integers preorder, which represents the preorder traversal of a BST (i.e., binary search tree), construct the tree and return its root.

It is guaranteed that there is always possible to find a binary search tree with the given requirements for the given test cases.

A binary search tree is a binary tree where for every node, any descendant of Node.left has a value strictly less than Node.val, and any descendant of Node.right has a value strictly greater than Node.val.

A preorder traversal of a binary tree displays the value of the node first, then traverses Node.left, then traverses Node.right.



Example 1:

Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]


Example 2:

Input: preorder = [1,3]
Output: [1,null,3]



Constraints:

    1 <= preorder.length <= 100
    1 <= preorder[i] <= 1000
    All the values of preorder are unique.



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
    TreeNode *bstFromPreorder(std::vector<int> &preorder)
    {
        int n = preorder.size();
        std::stack<TreeNode *> st;
        TreeNode *root = new TreeNode(preorder[0]);
        st.push(root);

        for (int i = 1; i < n; ++i)
        {
            int current_num = preorder[i];
            TreeNode *tmp = nullptr;
            // search for parent
            while (!st.empty() && st.top()->val < current_num)
            {
                tmp = st.top();
                st.pop();
            }
            if (tmp != nullptr)
            {
                tmp->right = new TreeNode(current_num);
                st.push(tmp->right);
            }
            else
            {
                // Stack top element is a parent for a new node
                tmp = st.top();
                tmp->left = new TreeNode(current_num);
                st.push(tmp->left);
            }
        }
        return root;
    }
};

int main()
{
    Solution solver;

    TreeNode *root = new TreeNode(8);
    root->left = new TreeNode(5);
    root->left->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->right = new TreeNode(10);
    root->right->right = new TreeNode(12);

    std::vector<int> nums{8, 5, 1, 7, 10, 12};
    TreeNode *res = solver.bstFromPreorder(nums);

    bool pass1 = TreeUtils::isSameTree(root, res);
    std::cout << "Test 1: " << (pass1 ? "PASS" : "FAIL") << std::endl;
    TreeUtils::deleteTree(root);
    TreeUtils::deleteTree(res);
    std::cout << std::endl;
    return 0;
}