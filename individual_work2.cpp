#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

bool hasPathSum(TreeNode* root, int targetSum, int currentSum = 0) {
    if (root != NULL)
    {
        currentSum += root->val;
        if (root->left != NULL) {
            if (hasPathSum(root->left, targetSum, currentSum)) {
                return true;
            }
        }
        if (root->right != NULL) {
            if (hasPathSum(root->right, targetSum, currentSum)) {
                return true;
            }
        }
        if (root->left == root->right && currentSum == targetSum) return true;
        return false;
    }
    else return false;
}

int main()
{
    TreeNode* root = new TreeNode;
    int targetSum = 0;
    cout << hasPathSum(root, targetSum);
}

