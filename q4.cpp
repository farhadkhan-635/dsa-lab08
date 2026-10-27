// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 08, Task 4: Searching in a BST

#include <iostream>
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

// returns the node that holds key, or nullptr if the key is not in the tree.
// Smaller keys can only be in the left subtree and larger keys only in the
// right subtree, so only one side is searched at every step.
Node* searchRecursive(Node* root, int key)
{
    // two ways to stop: the tree is empty or we are standing on the key.
    // Returning root works for both, it is nullptr in the first case.
    if (root == nullptr || root->data == key)
    {
        return root;
    }

    if (key < root->data)
    {
        return searchRecursive(root->left, key);
    }
    return searchRecursive(root->right, key);
}

// same search with a loop, no recursion
Node* searchIterative(Node* root, int key)
{
    Node* curr = root;

    while (curr != nullptr)
    {
        if (key == curr->data)
        {
            return curr;             // found it
        }
        else if (key < curr->data)
        {
            curr = curr->left;       // key can only be on the left
        }
        else
        {
            curr = curr->right;      // key can only be on the right
        }
    }
    return nullptr;                  // walked off the tree, so the key is missing
}

// helper for the demonstration: prints every node the key is compared with
void printSearchPath(Node* root, int key)
{
    cout << "Nodes compared while searching " << key << ": ";
    Node* curr = root;
    while (curr != nullptr)
    {
        cout << curr->data << " ";
        if (key == curr->data)
        {
            break;
        }
        else if (key < curr->data)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    if (curr == nullptr)
    {
        cout << "(then reached nullptr, so the key is not in the tree)";
    }
    cout << endl;
}

// runs both searches for one key and prints what each of them found
void testKey(Node* root, int key)
{
    Node* r = searchRecursive(root, key);
    Node* it = searchIterative(root, key);

    cout << "Search " << key << ": recursive "
         << (r != nullptr ? "Found" : "Not found")
         << ", iterative "
         << (it != nullptr ? "Found" : "Not found");
    cout << ", same result: " << (r == it ? "yes" : "no") << endl;
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
    // the BST from Task 1, built by linking nodes
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

    cout << "Searching the seven node BST:" << endl;
    testKey(root, 40);   // the root itself
    testKey(root, 10);   // leftmost leaf
    testKey(root, 70);   // rightmost leaf
    testKey(root, 25);   // not in the tree

    // 25 is smaller than 40 so go left, 25 is bigger than 20 so go right,
    // 25 is smaller than 30 so go left, and the left child of 30 is nullptr.
    // The nodes compared are 40, 20 and 30.
    cout << endl;
    printSearchPath(root, 25);

    // empty tree, both versions must say Not found and not crash
    cout << endl << "Searching an empty tree:" << endl;
    testKey(nullptr, 40);

    freeTree(root);
    return 0;
}
