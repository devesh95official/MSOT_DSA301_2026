# Binary Search Tree (BST)

> No code or implementation — only the ideas you need to start solving BST problems.

---

## 1. What is a BST?

A **Binary Search Tree** is a binary tree with one main rule:

```text
        LEFT < NODE < RIGHT
```

Example:

```text
          10
         /  \
        5    20
```

Why is this a BST?

```text
5 < 10 < 20
```

### Remember

```text
SMALLER  → LEFT
BIGGER   → RIGHT
```

---

## 2. Which one is a BST?

### Example A ✅

```text
          10
         /  \
        5    20
```

`5 < 10 < 20`

So, **BST**.

### Example B ❌

```text
          10
         /  \
        15   20
```

`15` is on the left, but `15 > 10`.

So, **not a BST**.

### Example C ❌

```text
          10
         /  \
        5     7
```

`7` is on the right, but `7 < 10`.

So, **not a BST**.

---

# 3. Where will a new value go?

Consider:

```text
          10
         /  \
        5    20
```

### Question

Where will `7` go?

Start at `10`:

```text
7 < 10
→ go LEFT
```

Now at `5`:

```text
7 > 5
→ go RIGHT
```

So:

```text
          10
         /  \
        5    20
         \
          7
```

### The idea

At every node, ask:

```text
Is my value smaller?
    → LEFT

Is my value bigger?
    → RIGHT
```

---

# 4. One more insertion question

```text
          50
         /  \
        30   70
```

### Question

Where will `20` go?

```text
20 < 50 → LEFT
20 < 30 → LEFT
```

Answer:

```text
          50
         /  \
        30   70
       /
      20
```

### Question

Where will `60` go?

```text
60 > 50 → RIGHT
60 < 70 → LEFT
```

Answer:

```text
          50
         /  \
        30   70
            /
           60
```

---

# 5. How do we search in a BST?

Consider:

```text
          50
         /  \
        30   70
       / \   / \
      20 40 60 80
```

### Question

Is `40` present?

Start at `50`:

```text
40 < 50 → LEFT
```

At `30`:

```text
40 > 30 → RIGHT
```

At `40`:

```text
FOUND ✅
```

We checked only:

```text
50 → 30 → 40
```

We did **not** check every node.

---

## 6. Search question: value does not exist

Same tree:

```text
          50
         /  \
        30   70
       / \   / \
      20 40 60 80
```

### Question

Is `65` present?

```text
65 > 50 → RIGHT
65 < 70 → LEFT
65 > 60 → RIGHT
```

There is no node there.

```text
65 is NOT present ❌
```

---

# 7. Where is the minimum?

Consider:

```text
          50
         /  \
        30   70
       /
      20
     /
    10
```

### Question

What is the smallest value?

Keep going **LEFT**:

```text
50 → 30 → 20 → 10
```

Answer:

```text
MINIMUM = 10
```

### Trick

```text
Minimum = LEFTMOST node
```

---

# 8. Where is the maximum?

Consider:

```text
          50
         /  \
        30   70
            /  \
           60   80
                 \
                  90
```

### Question

What is the largest value?

Keep going **RIGHT**:

```text
50 → 70 → 80 → 90
```

Answer:

```text
MAXIMUM = 90
```

### Trick

```text
Maximum = RIGHTMOST node
```

---

# 9. Inorder traversal in a BST

Remember:

```text
INORDER = LEFT → ROOT → RIGHT
```

Consider:

```text
          50
         /  \
        30   70
       / \   / \
      20 40 60 80
```

### Question

What is the inorder traversal?

Left side:

```text
20 30 40
```

Root:

```text
50
```

Right side:

```text
60 70 80
```

So:

```text
20 30 40 50 60 70 80
```

### ⭐ Most important BST trick

```text
BST + INORDER = SORTED ORDER
```

Why?

Because the BST already guarantees:

```text
smaller values → left
larger values  → right
```

And inorder visits:

```text
left → node → right
```

---

# 10. Successor and predecessor

Use the sorted order:

```text
20 30 40 50 60 70 80
```

### Question

What is the **successor** of `30`?

Successor means:

```text
NEXT BIGGER value
```

Answer:

```text
40
```

### Question

What is the **predecessor** of `50`?

Predecessor means:

```text
NEXT SMALLER value
```

Answer:

```text
40
```

### Remember

```text
Successor   = next bigger
Predecessor = next smaller
```

---

# 11. Deleting a node — the 3 cases

Deletion looks harder, so split it into just **3 cases**.

```text
1. No child
2. One child
3. Two children
```

---

## Case 1 — No child

```text
          50
         /  \
        30   70
       /
      20
```

### Question

Remove `20`.

`20` has no children.

So simply remove it:

```text
          50
         /  \
        30   70
```

### Idea

```text
0 children → remove it
```

---

## Case 2 — One child

```text
          50
         /
        30
       /
      20
```

### Question

Remove `30`.

`30` has only one child:

```text
20
```

So `20` takes the place of `30`:

```text
          50
         /
        20
```

### Idea

```text
1 child → child comes up
```

---

## Case 3 — Two children

```text
          50
         /  \
        30   70
       / \
      20 40
```

### Question

Remove `30`.

`30` has two children:

```text
20 and 40
```

Which value can replace `30`?

Take the **smallest value in its right subtree**:

```text
40
```

So:

```text
          50
         /  \
        40   70
       /
      20
```

### Why `40`?

Because it is the **next bigger value** after `30`.

This is called the:

```text
INORDER SUCCESSOR
```

### Easy memory trick

```text
Delete node with 2 children
→ find next bigger value
→ replace it
```

---

# 12. Important BST trap: check the whole subtree

Consider:

```text
          50
         /  \
        30   70
       / \
      20 60
```

### Question

Is this a BST?

**No ❌**

Why?

`60` is inside the **left subtree of 50**.

Therefore it must be:

```text
60 < 50
```

But:

```text
60 > 50
```

So the tree is invalid.

### Big lesson

The BST rule is not only about the direct parent.

It must be true for the **whole subtree**.

---

# 13. Another BST trick question

```text
          10
         /  \
        5    20
            /
           15
```

### Is it a BST?

**Yes ✅**

Because:

```text
Everything on left of 10  < 10
Everything on right of 10 > 10
```

And inside the right subtree:

```text
15 < 20
```

Everything is valid.

---

# 14. A very common wrong tree

```text
          10
         /  \
        5    20
            /
            8
```

### Is it a BST?

**No ❌**

`8` is in the **right subtree of 10**.

So it must be:

```text
8 > 10
```

But:

```text
8 < 10
```

Therefore invalid.

---

# 15. Build a BST from a sequence

### Question

Insert:

```text
10, 5, 15, 2, 7, 12, 20
```

The final tree is:

```text
              10
             /  \
            5    15
           / \   / \
          2   7 12 20
```

Now answer:

### Minimum?

```text
2
```

### Maximum?

```text
20
```

### Inorder?

```text
2 5 7 10 12 15 20
```

Again, sorted!

---

# 16. Which BST is better?

### Tree A

```text
          50
         /  \
        30   70
       / \   / \
      20 40 60 80
```

### Tree B

```text
10
  \
   20
     \
      30
        \
         40
           \
            50
```

### Which one is better for searching?

```text
Tree A ✅
```

Why?

Tree A is **short and balanced**.

Tree B is very tall and looks like a linked list.

---

# 17. Why can BST become slow?

A good BST can be short:

```text
          50
         /  \
        30   70
       / \   / \
      20 40 60 80
```

A bad BST can become:

```text
10
  \
   20
     \
      30
        \
         40
           \
            50
```

So:

```text
Balanced BST → roughly O(log N)
Skewed BST   → O(N)
```

You do not need to memorize the math yet.

Just remember:

```text
SHORT TREE = GOOD
TALL TREE  = BAD
```

---

# 18. The BST cheat sheet

```text
┌──────────────────────────────────────────────┐
│                  BST RULE                    │
├──────────────────────────────────────────────┤
│ Smaller → LEFT                               │
│ Bigger  → RIGHT                              │
│                                              │
│ Minimum → LEFTMOST                           │
│ Maximum → RIGHTMOST                          │
│                                              │
│ Inorder → SORTED ORDER                       │
│                                              │
│ Successor   → NEXT BIGGER                    │
│ Predecessor → NEXT SMALLER                   │
│                                              │
│ Delete 0 children → remove                   │
│ Delete 1 child   → child comes up            │
│ Delete 2 children → use next bigger value    │
└──────────────────────────────────────────────┘
```

---

# 19. Quick practice questions

Try these without looking at the answers.

### Q1

```text
          40
         /  \
        20   60
```

Where will `10` go?

<details>
<summary>Answer</summary>

```text
20's LEFT
```

</details>

---

### Q2

```text
          40
         /  \
        20   60
       / \
      10 30
```

What is the minimum?

<details>
<summary>Answer</summary>

```text
10
```

</details>

---

### Q3

```text
          40
         /  \
        20   60
       / \   / \
      10 30 50 70
```

What is the inorder traversal?

<details>
<summary>Answer</summary>

```text
10 20 30 40 50 60 70
```

</details>

---

### Q4

What is the successor of `50`?

```text
          40
         /  \
        20   60
            / \
           50 70
```

<details>
<summary>Answer</summary>

```text
60
```

</details>

---

### Q5

Is this a BST?

```text
          40
         /  \
        20   60
             /
            30
```

<details>
<summary>Answer</summary>

```text
NO ❌

30 is in the right subtree of 40,
but 30 < 40.
```

</details>

---

# 20. Final memory trick

You only need to remember this first:

```text
              BST

      SMALLER → LEFT
      BIGGER  → RIGHT
```

And then:

```text
LEFTMOST  → MINIMUM
RIGHTMOST → MAXIMUM

INORDER → SORTED

SUCCESSOR   → NEXT BIGGER
PREDECESSOR → NEXT SMALLER
```

> **Master these observations first. The code becomes much easier afterwards.**
