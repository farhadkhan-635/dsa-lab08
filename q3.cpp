// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 08, Task 3: Iterative traversals using a stack

#include <iostream>
#include <stack>
using namespace std;

struct Node
{
    int data;
    Node* left;    // left child, nullptr if there is none
    Node* right;   // right child, nullptr if there is none
};

Node* createNode(int value)
{
    Node* node = new Node;
    node->data = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// recursive versions from Task 1, kept only so the outputs can be compared
void inorder(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Root, Left, Right without recursion.
// The stack is last in, first out. We want the left child to be visited first,
// so the right child is pushed first and the left child is pushed after it,
// which puts the left child on top and it comes out first.
void preorderIterative(Node* root)
{
    if (root == nullptr)
    {
        return;
    }

    stack<Node*> s;
    s.push(root);

    while (!s.empty())
    {
        Node* curr = s.top();
        s.pop();
        cout << curr->data << " ";   // visit the node as soon as it comes out

        if (curr->right != nullptr)  // right first, so it waits underneath
        {
            s.push(curr->right);
        }
        if (curr->left != nullptr)   // left last, so it is on top
        {
            s.push(curr->left);
        }
    }
}

// Left, Root, Right without recursion.
// curr walks down to the left as far as possible. The stack remembers every
// node we passed, because each of them still has to be printed after its left
// subtree and then its right subtree has to be done. When there is no more
// left to go, the node on top of the stack is the next one to print.
void inorderIterative(Node* root)
{
    stack<Node*> s;
    Node* curr = root;

    while (curr != nullptr || !s.empty())
    {
        while (curr != nullptr)      // go as far left as possible
        {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();              // the most recent node we could not finish
        s.pop();
        cout << curr->data << " ";   // its left side is done, so print it
        curr = curr->right;          // and now move to its right subtree
    }
}

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
    // same seven node tree as Task 1
    Node* root = createNode(40);
    root->left = createNode(20);
    root->right = createNode(60);
    root->left->left = createNode(10);
    root->left->right = createNode(30);
    root->right->left = createNode(50);
    root->right->right = createNode(70);

    // both lines in each pair must be identical
    cout << "Seven node tree:" << endl;
    cout << "Preorder (recursive) : ";
    preorder(root);
    cout << endl;
    cout << "Preorder (iterative) : ";
    preorderIterative(root);
    cout << endl;
    cout << "Inorder (recursive)  : ";
    inorder(root);
    cout << endl;
    cout << "Inorder (iterative)  : ";
    inorderIterative(root);
    cout << endl;

    // empty tree, both functions must print nothing and not crash
    cout << endl << "Empty tree (nullptr), the lines below must stay blank:" << endl;
    cout << "Preorder (iterative) : ";
    preorderIterative(nullptr);
    cout << endl;
    cout << "Inorder (iterative)  : ";
    inorderIterative(nullptr);
    cout << endl;

    // single node tree
    cout << endl << "Single node tree (5):" << endl;
    Node* single = createNode(5);
    cout << "Preorder (iterative) : ";
    preorderIterative(single);
    cout << endl;
    cout << "Inorder (iterative)  : ";
    inorderIterative(single);
    cout << endl;

    freeTree(root);
    freeTree(single);
    return 0;
}
