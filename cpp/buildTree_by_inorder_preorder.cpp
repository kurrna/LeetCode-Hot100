//
// Created by Kurna on 25-7-23.
//
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
};

class Solution {
private:
    unordered_map<int, int> index;

    TreeNode *build(vector<int> &preorder, int preorderStart, int preorderEnd, vector<int> &inorder, int inorderStart,
                    int inorderEnd) {
        if (preorderStart > preorderEnd || inorderStart > inorderEnd) return nullptr;
        int rootVal = preorder[preorderStart];
        auto *root = new TreeNode(rootVal);
        int rootIndex = index[rootVal];
        int leftSize = rootIndex - inorderStart;
        root->left = build(preorder, preorderStart + 1, preorderStart + leftSize, inorder, inorderStart, rootIndex - 1);
        root->right = build(preorder, preorderStart + leftSize + 1, preorderEnd, inorder, rootIndex + 1, inorderEnd);
        return root;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        for (int i = 0; i < inorder.size(); i++) {
            index[inorder[i]] = i;
        }
        return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

    void printPreorder(TreeNode* node) {
        if (node == nullptr) return;
        std::cout << node->val << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }

    // 中序遍历打印
    void printInorder(TreeNode* node) {
        if (node == nullptr) return;
        printInorder(node->left);
        std::cout << node->val << " ";
        printInorder(node->right);
    }

    // 递归释放二叉树内存
    void freeTree(TreeNode* node) {
        if (node == nullptr) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

    void test() {
        // 测试用例：构建示例二叉树
        std::vector<int> preorder = {3, 9, 20, 15, 7};
        std::vector<int> inorder = {9, 3, 15, 20, 7};

        TreeNode* root = buildTree(preorder, inorder);

        std::cout << "测试结果：" << std::endl;
        std::cout << "预期前序遍历: 3 9 20 15 7" << std::endl;
        std::cout << "实际前序遍历: ";
        printPreorder(root);
        std::cout << std::endl;

        std::cout << "预期中序遍历: 9 3 15 20 7" << std::endl;
        std::cout << "实际中序遍历: ";
        printInorder(root);
        std::cout << std::endl;

        freeTree(root);
    }
};

int main() {
    Solution solution;
    solution.test();
    return 0;
}
