#include <iostream>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void PrintArray(int *a, int left, int right, int left_boundary, int right_boundary) {
    for (int i = left; i <= right; i++) {
        if (i == left_boundary) std::cout << "[";
        std::cout << a[i];
        if (i == right_boundary) std::cout << "]";
        std::cout <<  " ";
    }

    std::cout << std::endl;
}

void SetPivot(int *a, int left, int right) {
    int mid = (left + right) / 2;

    // Lowest to the beginning
    if (a[mid] < a[left]) {
        swap(&a[mid], &a[left]);
    }
    if (a[right] < a[left]) {
        swap(&a[right], &a[left]);
    }

    // Median to the end
    if (a[mid] < a[right]) {
        swap(&a[mid], &a[right]);
    }
}

int Partition(int *a, int left, int right) {
    if (left == right) {
        return right;
    }

    int i = right - 1;
    for (int j = right - 1; j >= left; j--) {
        //PrintArray(a, left, right, j, i);
        if (a[j] > a[right]) {
            if (i != j) {
                swap(&a[i], &a[j]);
            }
            i--;
        }
    }
    //PrintArray(a, left, right, left, i);

    swap(&a[i + 1], &a[right]);
    //PrintArray(a, left, right, left, i);
    return i + 1;
}

int KthSmallest(int *a, int n, int k) {
    int pivot;
    int left = 0;
    int right = n - 1;
    while (true) {
        // std::cout << "Finding: " << k << std::endl;
        SetPivot(a, left, right);
        pivot = Partition(a, left, right);
        //std::cout << pivot - left << std::endl;

        if (pivot - left == k) {
            return a[pivot];
        }

        if (pivot - left > k) {
            right = pivot - 1;
        } else if (pivot - left < k) {
            k = k - (pivot - left) - 1;
            left = pivot + 1;
        }

    };
}

int main() {
    int n, k;

    std::cin >> n;
    std::cin >> k;

    int a[n];

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::cout << KthSmallest(a, n, k);

    return 0;
}