#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void insertionSort(vector<int>& A, int p, int r) {
    for (int i = p + 1; i <= r; i++) {
        int key = A[i], j = i - 1;
        while (j >= p && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

void merge(vector<int>& A, int p, int q, int r) {
    vector<int> L(A.begin() + p, A.begin() + q + 1);
    vector<int> R(A.begin() + q + 1, A.begin() + r + 1);
    int i = 0, j = 0, k = p;
    
    while (i < L.size() && j < R.size())
        A[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        
    while (i < L.size()) A[k++] = L[i++];
    while (j < R.size()) A[k++] = R[j++];
}

void hybridMergeSort(vector<int>& A, int p, int r, int k) {
    if (r - p + 1 <= k) {
        insertionSort(A, p, r);
    } else if (p < r) {
        int q = p + (r - p) / 2;
        hybridMergeSort(A, p, q, k);
        hybridMergeSort(A, q + 1, r, k);
        merge(A, p, q, r);
    }
}

int main() {
    int n = 1000000;
    vector<int> ks = {1, 2, 4, 8, 16, 32, 64, 128};
    vector<int> original(n);
    
    for (int i = 0; i < n; i++) original[i] = rand();
    
    for (int k : ks) {
        vector<int> A = original;
        auto inicio = high_resolution_clock::now();
        hybridMergeSort(A, 0, n - 1, k);
        auto fin = high_resolution_clock::now();
        cout << k << " : " << duration_cast<microseconds>(fin - inicio).count() << "\n";
    }
    
    return 0;
}