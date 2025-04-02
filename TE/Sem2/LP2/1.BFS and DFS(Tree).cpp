#include <bits/stdc++.h>
using namespace std;

class node {
private:
    int data;
    node* left;
    node* right;

public:
    node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
    friend class Tree;
};

class Tree {
    node* root;

    void buildTree(node*& root);
    void displayTree(node* root);
    void helper(node* root, int level, vector<int>& temp);
    int height(node* root);
    vector<vector<int>> recurBfs(node* root);
    void dfsRecursive(node* root);
    void bfsIterative(node* root);

public:
    void buildTree() { buildTree(root); }
    void displayTree() { displayTree(root); }
    vector<vector<int>> recurBfs() { return recurBfs(root); }
    int height() { return height(root); }
    void dfsRecursive() { dfsRecursive(root); }
    void bfsIterative() { bfsIterative(root); }
};

vector<vector<int>> Tree::recurBfs(node* root) {
    int heig = height(root);
    vector<vector<int>> ans;

    for (int i = 0; i < heig; i++) {
        vector<int> temp;
        helper(root, i, temp);
        ans.push_back(temp);
    }
    return ans;
}

void Tree::buildTree(node*& root) {
    queue<node*> q;
    cout << "Enter the data for root: ";
    int data;
    cin >> data;
    root = new node(data);
    q.push(root);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        cout << "Enter the left node of " << temp->data << ": ";
        int leftData;
        cin >> leftData;
        cout << "Enter the right node of " << temp->data << ": ";
        int rightData;
        cin >> rightData;

        if (leftData != -1) {
            temp->left = new node(leftData);
            q.push(temp->left);
        }
        if (rightData != -1) {
            temp->right = new node(rightData);
            q.push(temp->right);
        }
    }
}

void Tree::displayTree(node* root) {
    queue<node*> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();

        if (temp == NULL) {
            cout << endl;
            if (!q.empty()) {
                q.push(NULL);
            }
        } else {
            cout << temp->data << " ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }
}

int Tree::height(node* root) {
    if (root == NULL)
        return 0;
    return max(height(root->left), height(root->right)) + 1;
}

void Tree::helper(node* root, int level, vector<int>& temp) {
    if (root == NULL)
        return;

    if (level == 0) {
        temp.push_back(root->data);
    } else if (level > 0) {
        helper(root->left, level - 1, temp);
        helper(root->right, level - 1, temp);
    }
}

void Tree::dfsRecursive(node* root) {
    if (root == NULL)
        return;
    cout << root->data << " ";
    dfsRecursive(root->left);
    dfsRecursive(root->right);
}

void Tree::bfsIterative(node* root) {
    if (root == NULL)
        return;
    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* temp = q.front();
        q.pop();
        cout << temp->data << " ";

        if (temp->left)
            q.push(temp->left);
        if (temp->right)
            q.push(temp->right);
    }
}

int main() {
    Tree t1;
    t1.buildTree();
    t1.displayTree();

    cout << "\nRecursive BFS (Level Order Traversal):\n";
    vector<vector<int>> levels = t1.recurBfs();
    for (const auto& level : levels) {
        for (int val : level) {
            cout << val << " ";
        }
        cout << endl;
    }

    cout << "\nDFS Recursive Traversal:\n";
    t1.dfsRecursive();
    cout << endl;

    cout << "\nBFS Iterative Traversal:\n";
    t1.bfsIterative();
    cout << endl;
    
    return 0;
}
