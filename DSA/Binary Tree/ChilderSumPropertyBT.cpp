#include <bits/stdc++.h>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};

void changeTree(TreeNode* root) {

    if (!root) return;

    int child = 0;

    if (root->left) {
        child += root->left->data;
    }

    if (root->right) {
        child += root->right->data;
    }

    if (child >= root->data) {
        root->data = child;
    }
    else {
        if (root->left) {
            root->left->data = root->data;
        }
        else if (root->right) {
            root->right->data = root->data;
        }
    }

    changeTree(root->left);
    changeTree(root->right);

    int tot = 0;

    if (root->left) {
        tot += root->left->data;
    }

    if (root->right) {
        tot += root->right->data;
    }

    if (root->left || root->right) {
        root->data = tot;
    }
}

void inorder(TreeNode* root) {
    if (!root) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {

    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(7);
    root->right = new TreeNode(2);

    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(5);

    root->right->left = new TreeNode(1);
    root->right->right = new TreeNode(30);

    cout << "Before: ";
    inorder(root);
    cout << endl;

    changeTree(root);

    cout << "After: ";
    inorder(root);
    cout << endl;

    return 0;
}