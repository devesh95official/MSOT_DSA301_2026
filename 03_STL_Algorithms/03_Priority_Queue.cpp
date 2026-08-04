// STL Algorithms - 3. Priority Queue

#include <bits/stdc++.h>
using namespace std;

int main() {
    // Default is a max-heap: top is the largest. push/pop O(log n), top O(1).
    {
        priority_queue<int> pq;
        for (int x : {3, 9, 1}) pq.push(x);
        cout << pq.top() << " " << pq.size() << "\n";     // 9 3
        pq.pop();
        cout << pq.top() << "\n";                         // 3
    }

    // Min-heap: all three template arguments have to be written out.
    {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int x : {3, 9, 1}) pq.push(x);
        cout << pq.top() << "\n";                         // 1
    }

    // Reading a heap means top-then-pop; there is no iteration and no search.
    {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int x : {4, 2, 7}) pq.push(x);
        while (!pq.empty()) { cout << pq.top() << " "; pq.pop(); }
        cout << "\n";                   // 2 4 7
    }

    // A lambda comparator needs decltype in the type and the object in the constructor.
    // The logic is inverted here: returning true means a has LOWER priority.
    {
        auto cmp = [](int a, int b) { return a > b; };
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
        pq.push(5); pq.push(1); pq.push(8);
        cout << pq.top() << "\n";                         // 1, so this is a min-heap
    }

    // pair heaps order by first then second, so pack the priority key first.
    {
        priority_queue<pair<int, int>> pq;
        pq.push({2, 100});
        pq.push({5, 1});
        pq.push({5, 9});
        cout << pq.top().first << " " << pq.top().second << "\n";     // 5 9
    }

    // Dijkstra shape: min-heap of {dist, node}, so the nearest node pops first.
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({7, 1});
        pq.push({2, 3});
        auto [d, u] = pq.top();
        cout << d << " " << u << "\n";                     // 2 3
    }

    // k largest: hold a min-heap of size k, so top is the kth largest so far.
    {
        vector<int> a = {5, 1, 9, 3, 7, 8};
        int k = 3;
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int x : a) {
            pq.push(x);
            if ((int)pq.size() > k) pq.pop();             // drop the smallest
        }
        cout << pq.top() << "\n";                         // 7, the 3rd largest
        while (!pq.empty()) { cout << pq.top() << " "; pq.pop(); }
        cout << "\n";                                     // 7 8 9
    }

    // O(n) heapify beats n pushes when every element is available up front.
    {
        vector<int> a = {5, 1, 9, 3};
        priority_queue<int> pq(a.begin(), a.end());
        cout << pq.top() << "\n";                         // 9
    }

    return 0;
}
