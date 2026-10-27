// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 08, Task 5: Recursive insertion in a BST

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

// Left, Root, Right, on a BST this prints the keys in sorted order
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

// Root, Left, Right, used here to see the shape of the tree
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

// search from Task 4, needed to verify the insertion
Node* searchRecursive(Node* root, int key)
{
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

// inserts value and returns the root of the updated subtree.
// The caller must store the returned pointer back, because for an empty
// tree the root changes from nullptr to the new node.
Node* insertRecursive(Node* root, int value)
{
    // an empty spot means this is where the value belongs, this case also
    // covers inserting into a completely empty tree
    if (root == nullptr)
    {
        return createNode(value);
    }

    if (value < root->data)
    {
        // the left subtree may get a new root, so its result is linked back
        root->left = insertRecursive(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insertRecursive(root->right, value);
    }
    else
    {
        // equal key, keys are unique in this lab so nothing is inserted
        cout << "Duplicate " << value << " ignored, tree not changed" << endl;
    }

    return root;   // unchanged root of this subtree
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
    Node* root = nullptr;   // start with an empty tree

    int values[] = {40, 20, 60, 10, 30, 50, 70};
    for (int i = 0; i < 7; i++)
    {
        root = insertRecursive(root, values[i]);   // always assign the result back
    }

    // the first insertion made 40 the root, so the tree has the same shape as Task 1
    cout << "After inserting 40 20 60 10 30 50 70:" << endl;
    cout << "Inorder  : ";
    inorder(root);
    cout << endl;
    cout << "Preorder : ";
    preorder(root);
    cout << endl;

    // 25 is smaller than 40 and 30 and bigger than 20, so it becomes the left child of 30
    cout << endl << "Insert 25:" << endl;
    root = insertRecursive(root, 25);
    cout << "Inorder  : ";
    inorder(root);
    cout << endl;

    // 20 is already in the tree, so this must change nothing
    cout << endl << "Insert 20 again:" << endl;
    root = insertRecursive(root, 20);
    cout << "Inorder  : ";
    inorder(root);
    cout << endl;

    // verify with the search function
    cout << endl << "Search 25: "
         << (searchRecursive(root, 25) != nullptr ? "Found" : "Not found") << endl;

    freeTree(root);
    return 0;
}
