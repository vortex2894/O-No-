/*
897. Increasing Order Search Tree
Link: https://leetcode.com/problems/increasing-order-search-tree/description/
Given the root of a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree
is now the root of the tree, and every node has no left child and only one right child.
Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
Input: root = [5,1,7]
Output: [1,null,5,null,7]
Constraints:
    The number of nodes in the given tree will be in the range [1, 100].
    0 <= Node.val <= 1000
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
    static TreeNode *createFromLevelOrder(const std::vector<int> &data)
    {
        if (data.empty() || data[0] == 0)
            return nullptr;

        TreeNode *root = new TreeNode(data[0]);
        std::queue<TreeNode *> q;
        q.push(root);
        size_t i = 1; // Start from index 1

        while (!q.empty() && i < data.size())
        {
            TreeNode *curr = q.front();
            q.pop();

            // Left child
            if (i < data.size())
            {
                curr->left = new TreeNode(data[i]);
                q.push(curr->left);

                ++i;
            }

            // Right child
            if (i < data.size())
            {
                curr->right = new TreeNode(data[i]);
                q.push(curr->right);
                ++i;
            }
        }
        return root;
    }

    static void deleteTree(TreeNode *root)
    {
        if (!root)
            return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }

    static std::string treeToString(TreeNode *root)
    {
        if (!root)
            return "[]";
        std::stringstream ss;
        ss << "[";
        bool first = true;
        for (TreeNode *cur = root; cur; cur = cur->right)
        {
            if (!first)
                ss << ", ";
            ss << cur->val;
            first = false;
        }
        ss << "]";
        return ss.str();
    }
    static std::vector<int> treeToVector(TreeNode *root)
    {
        std::vector<int> result;
        if (!root)
        {
            return result;
        }

        TreeNode *current = root;
        while (current)
        {
            if (current->val == 0)
            {
                current = current->right;
            }
            else
            {
                result.push_back(current->val);
                current = current->right;
            }
        }
        return result;
    }
};

class Solution
{
public:
private:
    std::vector<int> values;

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
    TreeNode *increasingBST(TreeNode *root)
    {
        values.clear();
        inorder(root);

        TreeNode dummy;
        TreeNode *cur = &dummy;
        for (int val : values)
        {
            cur->right = new TreeNode(val);
            cur = cur->right;
        }
        return dummy.right;
    }
};

int main()
{
    Solution solver;

    std::vector<int> v1 = {5, 1, 7};

    std::vector<int> expected = {1, 5, 7};

    auto input = TreeUtils::createFromLevelOrder(v1);

    TreeNode *res = solver.increasingBST(input);

    std::vector<int> res_vec = TreeUtils::treeToVector(res);

    bool pass1 = (res_vec == expected);

    std::cout << "Test 1: " << (pass1 ? "PASS" : "FAIL")
              << " → " << TreeUtils::treeToString(res) << "\n";

    TreeUtils::deleteTree(input);
    TreeUtils::deleteTree(res);
    return 0;
}