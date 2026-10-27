// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 08, Task 2: Level-order traversal using a queue

#include <iostream>
#include <queue>
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

// visits the tree level by level, left to right.
// A queue is used because it is first in, first out: nodes of one level are
// all taken out before their children, since the children were added later.
void levelOrder(Node* root)
{
    if (root == nullptr)     // empty tree, nothing to visit
    {
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        Node* curr = q.front();   // oldest waiting node
        q.pop();
        cout << curr->data << " ";

        // children go in left first and then right, only if they exist,
        // so we never push a nullptr
        if (curr->left != nullptr)
        {
            q.push(curr->left);
        }
        if (curr->right != nullptr)
        {
            q.push(curr->right);
        }
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

    cout << "Seven node tree:" << endl;
    cout << "Expected    : 40 20 60 10 30 50 70" << endl;
    cout << "Level order : ";
    levelOrder(root);
    cout << endl;

    // empty tree, the function returns at once so nothing is printed
    cout << endl << "Empty tree (nullptr), the line below must stay blank:" << endl;
    cout << "Level order : ";
    levelOrder(nullptr);
    cout << endl;

    // single node tree
    cout << endl << "Single node tree (5):" << endl;
    Node* single = createNode(5);
    cout << "Level order : ";
    levelOrder(single);
    cout << endl;

    freeTree(root);
    freeTree(single);
    return 0;
}
