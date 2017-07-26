// Deque-STL problem @ HackerRank
// Date: 25/07/2017 21:52:00
// Manoel Vilela

#include <iostream>
#include <deque>
#define endl '\n'

using namespace std;

// always remove the previous smaller elements
// sorted by increasing order arr[dq.front()] > arr[dq.back()]
void ensure_max(deque<int> &dq, int arr[], int &i) {

    // pop all previous smallest or equal elements (useless)
    while(!dq.empty() && arr[dq.back()] <= arr[i]) {
        dq.pop_back();
    }

    // insert the index of the current element on the end of deque
    dq.push_back(i);
}

// desired function on HackerRank
// time: O(n) | space: O(k)
void printKMax(int arr[], int n, int k){
    // always store the index of useful elements
    deque<int> dq(k);

    int i;
    // iterate for the first k elements
    for(i = 0; i < k; i++) {
        ensure_max(dq, arr, i);
    }

    // iterate on the rest of array
    for(; i < n; i++) {
        // the maximum element for subarray is the head of deque
        cout << arr[dq.front()] << " ";

        // remove the head if don't belongs to this next sub-array
        if (dq.front() <= (i - k)) {
            dq.pop_front();
        }

        // call ensure_max
        ensure_max(dq, arr, i);

    }
    cout << arr[dq.front()] << endl;
}

// read the entries and call printKMax for each query
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    while(t > 0) {
        int n, k;
        cin >> n >> k;
        int i;
        int arr[n];
        for(i = 0; i < n; i++)
            cin >> arr[i];
        printKMax(arr, n, k);
        t--;
    }
    return 0;
}
