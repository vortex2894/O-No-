/*
589. N-ary Tree Postorder Traversal



Link: https://leetcode.com/problems/n-ary-tree-postorder-traversal/description

Given the root of an n-ary tree, return the postorder traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal. Each group of children is separated by the null value (See examples)

Example 1:

Input: root = [1,null,3,2,4,null,5,6]
Output: [5,6,3,2,4,1]

Explanation: see the related figure.

Example 2:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]

Explanation: see the related figure.

Constraints:

    The number of nodes in the tree is in the range [0, 104].
    0 <= Node.val <= 104
    The height of the n-ary tree is less than or equal to 1000.


*/
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <bits/stdc++.h>

class TreeNode
{
public:
    int val;
    std::vector<TreeNode *> children;

    TreeNode() {}

    TreeNode(int _val)
    {
        val = _val;
    }

    TreeNode(int _val, std::vector<TreeNode *> _children)
    {
        val = _val;
        children = _children;
    }
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
        for (auto child : root->children)
        {
            deleteTree(child);
        }
        delete root;
    }
};

class Solution
{
public:
private:
    std::vector<int> ans;

    void postorderTraversal(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        
        for (auto child : node->children)
        {
            postorderTraversal(child);
            this->ans.push_back(child->val);

        }
    }

public:
    std::vector<int> postorder(TreeNode *root)
    {
        if (root == NULL)
        {
            return this->ans;
        }
        postorderTraversal(root);
        this->ans.push_back(root->val);
        return this->ans;
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

    std::vector<int> expected = {5, 6, 3, 2, 4, 1};

    // Create leaf nodes
    TreeNode *node5 = new TreeNode(5);
    TreeNode *node6 = new TreeNode(6);

    // Create node 3 with children 5 and 6
    std::vector<TreeNode *> children3 = {node5, node6};
    TreeNode *node3 = new TreeNode(3, children3);

    // Create node 2 and node 4 (no children)
    TreeNode *node2 = new TreeNode(2);
    TreeNode *node4 = new TreeNode(4);

    // Create root node 1 with children 3, 2, 4
    std::vector<TreeNode *> children1 = {node3, node2, node4};
    TreeNode *root = new TreeNode(1, children1);

    std::vector<int> res_vec = solver.postorder(root);

    bool pass1 = (res_vec == expected);
    std::cout << "Test 1: " << (pass1 ? "PASS" : "FAIL") << " for " << res_vec << "\n";

    TreeUtils::deleteTree(root);
    return 0;
}