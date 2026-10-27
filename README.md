# DSA Lab 08: Trees, Traversals and BST Search and Insertion

Data Structures and Algorithms, Department of Computing

| | |
|---|---|
| Name | Farhad Khan |
| CMS ID | 549034 |
| Class | BSCS-15E |
| Instructor | Sara Tariq Sheikh |
| Lab Engineer | Hasan Mohtashim |
| Lab Date | 27 October 2026 |

## About

This lab covers binary tree traversals and binary search tree (BST) search and insertion in C++. It follows the lab rules: functions without classes, a `Node` structure with `int data`, `Node* left` and `Node* right`, child pointers initialized to `nullptr`, and `std::stack` and `std::queue` used only where the lab allows them. Each task is one standalone source file that compiles and runs on its own. Every tree is released with `freeTree()` before the program ends.

## Files

| Name | Task | What it does |
|---|---|---|
| q1 | Recursive depth-first traversals | `createNode()`, `inorder()`, `preorder()` and `postorder()` on the seven node tree (40, 20, 60, 10, 30, 50, 70). Predictions are written in comments, and an empty tree and a single-node tree are tested. |
| q2 | Level-order traversal | `levelOrder()` with `std::queue<Node*>`. Returns at once for an empty tree, and prints 40 20 60 10 30 50 70 for the seven node tree. |
| q3 | Iterative traversals | `preorderIterative()` and `inorderIterative()` with `std::stack<Node*>` and no recursion. Output is printed next to the recursive versions from Task 1 for comparison. |
| q4 | Searching in a BST | `searchRecursive()` and `searchIterative()` return the node or `nullptr`. Searches 40, 10, 70, 25 and an empty tree, and prints the nodes compared for 25. |
| q5 | Recursive insertion | `insertRecursive()` returns the root of the updated subtree. Builds the tree from empty, inserts 25, ignores a second 20, and verifies with search. |
| q6 | Iterative insertion | `insertIterative()` with a tracked parent. Compares both insertion methods with `sameTree()`, then builds a skewed tree (10, 20, 30, 40, 50) and counts the comparisons for 50. |

Each one is a single source file (q1 is `q1.cpp`, q2 is `q2.cpp`, and so on).

## How to run

Each file is a complete program on its own, so run them one at a time.

**Using an IDE (easiest)**

1. Open the file, for example `q1.cpp`, in your IDE.
2. Press the compile and run button.
   - Dev-C++: F11
   - Code::Blocks: F9
   - Visual Studio: Ctrl + F5
   - VS Code with a C++ extension: the play button at the top right
3. A console window opens. All six programs run their tests on their own and need no input.

**Using the terminal (optional)**

If you have the g++ compiler installed, open a terminal in this folder and run:

```
g++ q1.cpp -o q1
./q1
```

The first line turns the source code into a program, and the second line runs it. On Windows use `.\q1` for the second line. For the other tasks replace q1 with q2, q3 and so on.

## Sample output

q1, traversals of the seven node tree:

```
Inorder   : 10 20 30 40 50 60 70
Preorder  : 40 20 10 30 60 50 70
Postorder : 10 30 20 50 70 60 40
```

q4, searching for a missing key:

```
Search 25: recursive Not found, iterative Not found, same result: yes
Nodes compared while searching 25: 40 20 30 (then reached nullptr, so the key is not in the tree)
```

q6, the skewed tree against a balanced one:

```
Search 50: Found
Nodes compared in the skewed tree      : 5
Nodes compared in the BST built above: 3 (the same key, in a balanced tree)
```

## Memory safety

- Every node is created with `new` in `createNode()`.
- `freeTree()` releases a tree in postorder, children first and the node itself last, and is called for every tree before the program ends.
- In `insertIterative()` a node is created only after the loop has confirmed the key is not a duplicate, so an ignored duplicate never leaks a node.
- Every pointer is checked against `nullptr` before it is used.
- All six programs were built with AddressSanitizer and UndefinedBehaviorSanitizer and ran with no errors or leaks. The insertion, search and iterative traversal functions were also compared against a reference over thousands of random trees.

## Concepts covered

- **Traversal orders:** inorder is Left, Root, Right, preorder is Root, Left, Right and postorder is Left, Right, Root. On a BST, inorder gives the keys in sorted order.
- **Recursive base case:** every recursive function stops when the pointer is `nullptr`, which also makes an empty tree safe.
- **Why level-order uses a queue:** a queue is first in, first out, so all nodes of one level come out before their children, which were added later. Extra space is O(w), the widest level.
- **Why preorder pushes the right child first:** a stack is last in, first out, so the left child pushed last is on top and is visited first.
- **Why inorder keeps a stack:** the stack remembers every node passed on the way left, because each of them still has to be printed after its left subtree and before its right subtree.
- **Searching 25 in the seven node BST:** the nodes compared are 40, 20 and 30. The left child of 30 is `nullptr`, so 25 is not in the tree.
- **Insertion and search cost:** both follow one path from the root, so they take O(h): O(log n) for a balanced tree and O(n) for a skewed one.
- **Why the skewed tree is slower:** keys inserted in sorted order all go to the right, so the tree becomes a chain of height n. Searching for 50 compares all 5 nodes, while the balanced tree needs 3. As n grows, a balanced tree needs about log2(n) comparisons and the chain needs up to n.
- **Duplicates:** keys are unique in this lab, so inserting an existing key leaves the tree unchanged.

## Reference

Goodrich, M. T., Tamassia, R., & Mount, D. M. (2011). *Data Structures and Algorithms in C++* (2nd ed.). Wiley.
