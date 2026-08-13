// Core Revision - 3. Linked List

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *next;
    Node(int v) : val(v), next(nullptr) {}
};

// Keep a tail pointer, otherwise every append walks the whole list.
Node *build(const vector<int> &a) {
    Node *head = nullptr, *tail = nullptr;
    for (int x : a) {
        Node *n = new Node(x);
        if (!head) head = tail = n;
        else { tail->next = n; tail = n; }
    }
    return head;
}

// nullptr is the only end marker there is.
void print(Node *head) {
    for (Node *c = head; c; c = c->next) cout << c->val << " -> ";
    cout << "null\n";
}

// O(1): the new node points at the old head, and head moves back one.
Node *pushFront(Node *head, int v) {
    Node *n = new Node(v);
    n->next = head;
    return n;
}

// O(n): with no tail pointer you have to walk to the last node.
Node *pushBack(Node *head, int v) {
    Node *n = new Node(v);
    if (!head) return n;
    Node *c = head;
    while (c->next) c = c->next;
    c->next = n;
    return head;
}

// Deleting needs the node before the target, so stop one short of it.
Node *removeVal(Node *head, int v) {
    if (!head) return nullptr;
    if (head->val == v) {
        Node *nx = head->next;
        delete head;
        return nx;
    }
    Node *prev = head;
    while (prev->next && prev->next->val != v) prev = prev->next;
    if (prev->next) {
        Node *del = prev->next;
        prev->next = del->next;
        delete del;
    }
    return head;
}

// Three pointers: save next, flip the link, slide both forward.
Node *reverseList(Node *head) {
    Node *prev = nullptr, *cur = head;
    while (cur) {
        Node *nx = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nx;
    }
    return prev;
}

// slow steps 1, fast steps 2, so slow lands on the middle (upper one if even length).
Node *middle(Node *head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Floyd: inside a loop the fast pointer gains one step per move, so it must meet slow.
bool hasCycle(Node *head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// Read next before deleting the node you are standing on.
void freeList(Node *head) {
    while (head) {
        Node *nx = head->next;
        delete head;
        head = nx;
    }
}

int main() {
    Node *head = build({1, 2, 3, 4, 5});
    print(head);                        // 1 -> 2 -> 3 -> 4 -> 5 -> null

    // Both of these can change the head, so always reassign the return value.
    head = pushFront(head, 0);
    head = pushBack(head, 6);
    print(head);                        // 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null

    head = removeVal(head, 3);
    head = removeVal(head, 99);         // absent value, list unchanged
    print(head);                        // 0 -> 1 -> 2 -> 4 -> 5 -> 6 -> null

    cout << middle(head)->val << "\n";  // 4, the 4th of 6 nodes

    head = reverseList(head);
    print(head);                        // 6 -> 5 -> 4 -> 2 -> 1 -> 0 -> null

    cout << hasCycle(head) << "\n";     // 0
    freeList(head);

    // A deliberate cycle: point the tail back into the middle, then let Floyd find it.
    {
        Node *h = build({1, 2, 3, 4});
        Node *tail = h;
        while (tail->next) tail = tail->next;
        tail->next = h->next;           // 4 now points back at 2
        cout << hasCycle(h) << "\n";    // 1
        tail->next = nullptr;           // break it, or freeList never ends
        freeList(h);
    }

    return 0;
}
