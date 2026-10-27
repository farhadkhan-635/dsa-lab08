// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 08, Task 1: Recursive depth-first traversals

#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* left;    // left child, nullptr if there is none
    Node* right;   // right child, nullptr if there is none
};

// makes one new node with no children yet
Node* createNode(int value)
{
    Node* node = new Node;
    node->data = value;
    node->left = nullptr;    // child pointers always start as nullptr
    node->right = nullptr;
    return node;
}

// Left, Root, Right
void inorder(Node* root)
{
    if (root == nullptr)     // base case: nothing here, so recursion stops
    {
        return;
    }
    inorder(root->left);             // whole left subtree first
    cout << root->data << " ";       // then this node
    inorder(root->right);            // then the whole right subtree
}

// Root, Left, Right
void preorder(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->data << " ";       // this node comes before its children
    preorder(root->left);
    preorder(root->right);
}

// Left, Right, Root
void postorder(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";       // this node comes after both children
}

// releases every node, children first and the node itself last
void freeTree(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main()
{
    // building the seven node tree by linking nodes directly
    // 40 is the root, its children are 20 (left) and 60 (right)
    // 20 has children 10 (left) and 30 (right)
    // 60 has children 50 (left) and 70 (right)
    Node* root = createNode(40);
    root->left = createNode(20);
    root->right = createNode(60);
    root->left->left = createNode(10);
    root->left->right = createNode(30);
    root->right->left = createNode(50);
    root->right->right = createNode(70);

    // my predictions, written before running the program:
    // inorder   : 10 20 30 40 50 60 70   (left, root, right gives sorted order here)
    // preorder  : 40 20 10 30 60 50 70   (every node comes before its children)
    // postorder : 10 30 20 50 70 60 40   (every node comes after its children)
    cout << "Seven node tree:" << endl;
    cout << "Inorder   : ";
    inorder(root);
    cout << endl;
    cout << "Preorder  : ";
    preorder(root);
    cout << endl;
    cout << "Postorder : ";
    postorder(root);
    cout << endl;

    // empty tree, the base case stops at once so nothing is printed
    cout << endl << "Empty tree (nullptr), the lines below must stay blank:" << endl;
    cout << "Inorder   : ";
    inorder(nullptr);
    cout << endl;
    cout << "Preorder  : ";
    preorder(nullptr);
    cout << endl;
    cout << "Postorder : ";
    postorder(nullptr);
    cout << endl;

    // single node tree, every traversal prints just that one value
    cout << endl << "Single node tree (5):" << endl;
    Node* single = createNode(5);
    cout << "Inorder   : ";
    inorder(single);
    cout << endl;
    cout << "Preorder  : ";
    preorder(single);
    cout << endl;
    cout << "Postorder : ";
    postorder(single);
    cout << endl;

    freeTree(root);
    freeTree(single);
    return 0;
}
