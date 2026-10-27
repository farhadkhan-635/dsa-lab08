// Name    : Farhad Khan
// Reg No  : 549034
// Section : BSCS-15E
// Lab 08, Task 6: Iterative insertion in a BST

// Why searching a skewed tree takes longer than a balanced one:
// when keys arrive in sorted order (10, 20, 30, 40, 50) every new key is
// bigger than all the others, so it always goes to the right and every node
// has only a right child. The tree becomes a chain, like a linked list, and
// its height is n. Searching for the largest key has to compare all n nodes,
// which is O(n). In a balanced tree every comparison throws away about half of
// the remaining nodes, so the height is about log2(n) and a search needs about
// that many comparisons. As n grows the gap grows too: with 1000 nodes the
// chain needs up to 1000 comparisons and a balanced tree needs about 10.

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

// recursive insertion from Task 5, used to build the tree we compare against
Node* insertRecursive(Node* root, int value)
{
    if (root == nullptr)
    {
        return createNode(value);
    }
    if (value < root->data)
    {
        root->left = insertRecursive(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insertRecursive(root->right, value);
    }
    else
    {
        cout << "Duplicate " << value << " ignored, tree not changed" << endl;
    }
    return root;
}

// inserts value with a loop and returns the root.
// The loop walks down like a search. We keep parent one step behind curr,
// because when curr finally becomes nullptr we have already left the tree,
// and parent is the node that must receive the new child.
Node* insertIterative(Node* root, int value)
{
    // empty tree, the new node itself is the root
    if (root == nullptr)
    {
        return createNode(value);
    }

    Node* curr = root;
    Node* parent = nullptr;

    while (curr != nullptr)
    {
        parent = curr;
        if (value < curr->data)
        {
            curr = curr->left;
        }
        else if (value > curr->data)
        {
            curr = curr->right;
        }
        else
        {
            // equal key, return before creating a node so nothing is leaked
            cout << "Duplicate " << value << " ignored, tree not changed" << endl;
            return root;
        }
    }

    // attach the new node to the correct side of the parent
    Node* newNode = createNode(value);
    if (value < parent->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    return root;   // the root does not change when the tree was not empty
}

// search from Task 4
Node* searchIterative(Node* root, int key)
{
    Node* curr = root;
    while (curr != nullptr)
    {
        if (key == curr->data)
        {
            return curr;
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
    return nullptr;
}

// helper: counts how many nodes the key is compared with on its way down
int countComparisons(Node* root, int key)
{
    int count = 0;
    Node* curr = root;
    while (curr != nullptr)
    {
        count++;   // one comparison with this node
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
    return count;
}

// helper: true when both trees have the same shape and the same values
bool sameTree(Node* a, Node* b)
{
    if (a == nullptr && b == nullptr)
    {
        return true;
    }
    if (a == nullptr || b == nullptr)
    {
        return false;
    }
    return a->data == b->data && sameTree(a->left, b->left) && sameTree(a->right, b->right);
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
    // part 1: build two fresh trees with the same insertions as Task 5,
    // one with the recursive function and one with the iterative function
    int values[] = {40, 20, 60, 10, 30, 50, 70, 25, 20};   // the last 20 is a duplicate
    Node* treeR = nullptr;
    Node* treeI = nullptr;

    cout << "Building a tree with insertRecursive (40 20 60 10 30 50 70 25, then 20 again):" << endl;
    for (int i = 0; i < 9; i++)
    {
        treeR = insertRecursive(treeR, values[i]);
    }

    cout << "Building a tree with insertIterative (same insertions):" << endl;
    for (int i = 0; i < 9; i++)
    {
        treeI = insertIterative(treeI, values[i]);
    }

    cout << endl << "Recursive insertion:" << endl;
    cout << "Inorder  : ";
    inorder(treeR);
    cout << endl;
    cout << "Preorder : ";
    preorder(treeR);
    cout << endl;

    cout << endl << "Iterative insertion:" << endl;
    cout << "Inorder  : ";
    inorder(treeI);
    cout << endl;
    cout << "Preorder : ";
    preorder(treeI);
    cout << endl;

    cout << endl << "Both trees identical: " << (sameTree(treeR, treeI) ? "yes" : "no") << endl;

    // part 2: keys inserted in sorted order give a skewed tree
    cout << endl << "Skewed tree, inserting 10 20 30 40 50:" << endl;
    Node* skewed = nullptr;
    for (int v = 10; v <= 50; v += 10)
    {
        skewed = insertIterative(skewed, v);
    }
    cout << "Inorder  : ";
    inorder(skewed);
    cout << endl;
    cout << "Preorder : ";
    preorder(skewed);      // same as inorder, every node has only a right child
    cout << endl;

    cout << "Search 50: " << (searchIterative(skewed, 50) != nullptr ? "Found" : "Not found") << endl;
    cout << "Nodes compared in the skewed tree      : " << countComparisons(skewed, 50) << endl;
    cout << "Nodes compared in the BST built above: " << countComparisons(treeI, 50)
         << " (the same key, in a balanced tree)" << endl;

    freeTree(treeR);
    freeTree(treeI);
    freeTree(skewed);
    return 0;
}
