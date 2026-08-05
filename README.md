# DSA 301 · Design and Analysis of Algorithms (C++)

Semester 3 course repository. Mirai School of Technology.

| | |
|---|---|
| **Credits** | 4 |
| **Language** | C++17 or newer |
| **Instructor** | Devesh Singh |
| **Modules** | 9 |
---

## Start here

1. Read `DSA301HandBook.pdf` for the topic you are on. One page per board.
2. Open the matching `.cpp` file in the folder and run it.
3. Open the `.excalidraw` file in the same folder if you want the board as drawn in class.

```bash
g++ -std=c++17 -O2 -Wall 01_Lambdas/01_Basics.cpp -o run && ./run
```

Every `.cpp` file is standalone with its own `main()`. Nothing to link, nothing to install.

---

## What is in each folder

```
NN_Topic_Name/
  01_Something.cpp        runnable, one topic, commented
  02_Something_Else.cpp
  Excalidraw/             the class boards, one per .cpp file
```

---

## Course structure

### Module One · STL Power-Ups and Fundamentals

The tools you will use in every problem after this. Lambdas for short logic, the containers worth knowing, the four algorithms that do most of the work, and a revision pass over recursion, stacks and linked lists.

| Ch | Folder | Topics | Boards |
|---:|---|---|---:|
| 1 | [`01_Lambdas`](./01_Lambdas) | Basics · Capture Lists · STL Usage · Recursive Lambdas · Quick Revision | 5 |
| 2 | [`02_STL_Containers`](./02_STL_Containers) | Vector Deque · Map Set · Quick Revision | 3 |
| 3 | [`03_STL_Algorithms`](./03_STL_Algorithms) | Sort Comparators · Binary Search · Priority Queue | 3 |
| 4 | [`04_Core_Revision`](./04_Core_Revision) | Recursion · Stack Dry Run · Linked List | 3 |

### Module Two · Binary Trees: Traversals and Views

Every tree problem is a traversal with something extra carried along. Learn the three orders, then the iterative forms, then what you can measure and see from outside the tree.

| Ch | Folder | Topics | Boards |
|---:|---|---|---:|
| 5 | [`05_Tree_Traversals`](./05_Tree_Traversals) | Recursive DFS · Iterative And BFS · Morris Traversal | 3 |
| 6 | [`06_Tree_Properties`](./06_Tree_Properties) | Height And Depth · Diameter And Balanced | 2 |
| 7 | [`07_Tree_Views`](./07_Tree_Views) | Top And Bottom View · Vertical And Boundary | 2 |

### Module Three · Binary Trees: Path Sums, LCA and Ops

Trees you change rather than only read. Inverting and flattening, the path sum family, lowest common ancestor, and rebuilding a tree from its traversals.

| Ch | Folder | Topics | Boards |
|---:|---|---|---:|
| 8 | [`08_Tree_Structure_Ops`](./08_Tree_Structure_Ops) | Invert And Symmetric · Flatten To List | 2 |
| 9 | [`09_Tree_Path_Sums`](./09_Tree_Path_Sums) | Root To Leaf · Max Path Sum | 2 |
| 10 | [`10_Tree_LCA_Construction`](./10_Tree_LCA_Construction) | LCA · Construct From Traversals · Serialization | 3 |

### Module Four · Binary Search Trees

One invariant buys you O(h) search. This module is about using it, breaking it carefully during deletion, and putting it back.

| Ch | Folder | Topics | Boards |
|---:|---|---|---:|
| 11 | [`11_BST_Basics`](./11_BST_Basics) | Search Insert · Validation | 2 |
| 12 | [`12_BST_Operations`](./12_BST_Operations) | Deletion Successor · Kth Element Iterator | 2 |
| 13 | [`13_BST_Queries`](./13_BST_Queries) | Sorted Array To BST · Range Sum Two Sum | 2 |

### Module Five · Greedy Algorithms and Patterns

Greedy is easy to write and easy to get wrong. The work is in the sort order and the argument for why it is safe, not in the loop.

| Ch | Folder | Topics | Boards |
|---:|---|---|---:|
| 14 | [`14_Greedy_Intervals`](./14_Greedy_Intervals) | Exchange Argument · Merge And Activity Selection | 2 |
| 15 | [`15_Greedy_Scheduling`](./15_Greedy_Scheduling) | Min Platforms Sweep · Fractional Knapsack Job Sequencing | 2 |
| 16 | [`16_Greedy_Arrays`](./16_Greedy_Arrays) | Jump Game · Gas Station | 2 |

### Module Six · Dynamic Programming: 1D, LIS and Grids

Same three questions every time: what is the state, what is the transition, what is the base case. Once those are written down the code is short.

| Ch | Folder | Topics | Boards |
|---:|---|---|---:|
| 17 | [`17_DP_Foundations`](./17_DP_Foundations) | Memoisation vs Tabulation · Coin Change | 2 |
| 18 | [`18_DP_LIS_LCS`](./18_DP_LIS_LCS) | Longest Increasing Subsequence · Longest Common Subsequence | 2 |
| 19 | [`19_DP_Grids_Subsets`](./19_DP_Grids_Subsets) | Grid Paths · Subset Sum | 2 |

### Module Seven · Dynamic Programming: Advanced and Partition

Knapsack and its relatives, the string tables, and the partition family where the state is an interval and you loop over split points.

| Ch | Folder | Topics | Boards |
|---:|---|---|---:|
| 20 | [`20_DP_Knapsack`](./20_DP_Knapsack) | 0/1 Knapsack · Unbounded Knapsack & Rod Cutting | 2 |
| 21 | [`21_DP_Strings`](./21_DP_Strings) | Edit Distance · Shortest Common Supersequence | 2 |
| 22 | [`22_DP_Partition`](./22_DP_Partition) | Matrix Chain Multiplication · Partition DP | 2 |

### Module Eight · Graph Algorithms and Shortest Paths

Build the adjacency list, then pick the traversal that matches the weights. Four shortest path algorithms and two ways to build a minimum spanning tree.

| Ch | Folder | Topics | Boards |
|---:|---|---|---:|
| 23 | [`23_Graph_Traversals`](./23_Graph_Traversals) | Representation, BFS and DFS · Cycle Detection · Bipartite Check and Topological Sort | 3 |
| 24 | [`24_Graph_Shortest_Paths`](./24_Graph_Shortest_Paths) | Dijkstra and 0-1 BFS · Bellman-Ford and Floyd-Warshall | 2 |
| 25 | [`25_Graph_MST`](./25_Graph_MST) | DSU and Kruskal · Prim | 2 |

### Module Nine · Tree DP, Backtracking and Capstone

DP on a rooted tree, search with undo, and the two pointer patterns. The last chapter is also the one you should reach for first on array problems.

| Ch | Folder | Topics | Boards |
|---:|---|---|---:|
| 26 | [`26_Tree_DP`](./26_Tree_DP) | Subtree DP · Tree Diameter | 2 |
| 27 | [`27_Backtracking`](./27_Backtracking) | Subsets and Permutations · N-Queens · Word Search and Rat in a Maze | 3 |
| 28 | [`28_Window_Two_Pointers`](./28_Window_Two_Pointers) | Sliding Window · Two Pointers | 2 |

---


