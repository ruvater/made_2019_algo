#include <iostream>

// Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
// Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1)
// в отсортированном массиве.
// Напишите нерекурсивный алгоритм.
// Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

template<typename T>
void PrintArray(T *a, int left, int right, int left_boundary, int right_boundary) {
    for (int i = left; i <= right; i++) {
        if (i == left_boundary) std::cout << "[";
        std::cout << a[i];
        if (i == right_boundary) std::cout << "]";
        std::cout <<  " ";
    }

    std::cout << std::endl;
}

template<typename T, class Comparator>
void SetPivot(T *a, int left, int right, Comparator comp) {
    int mid = (left + right) / 2;

    // Lowest to the beginning
    if (comp(a[mid], a[left])) {
        swap(&a[mid], &a[left]);
    }
    if (comp(a[right], a[left])) {
        swap(&a[right], &a[left]);
    }

    // Median to the end
    if (comp(a[mid], a[right])) {
        swap(&a[mid], &a[right]);
    }
}

template<typename T, class Comparator>
int Partition(T *a, int left, int right, Comparator comp) {
    if (left == right) {
        return right;
    }

    int i = right - 1;
    for (int j = right - 1; j >= left; j--) {
        //PrintArray(a, left, right, j, i);
        if (comp(a[right], a[j])) {
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

template<typename T, class Comparator>
int KthSmallest(T *a, int n, int k, Comparator comp) {
    int pivot;
    int left = 0;
    int right = n - 1;
    while (true) {
        // std::cout << "Finding: " << k << std::endl;
        SetPivot(a, left, right, comp);
        pivot = Partition(a, left, right, comp);
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

    std::cout << KthSmallest(a, n, k, [] (const auto& first, const auto& last) {
        return first < last;
    });

    return 0;
}