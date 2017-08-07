//
// Created by penguinrage on 5/08/17.
//


#include <iostream>

#ifndef DESIGN_PATTERNS_STRATEGY_HPP
#define DESIGN_PATTERNS_STRATEGY_HPP

// TODO - fill in template sorting strategies for each


class SortStrategy {
public:
    virtual void sort(int arr[], int left, int right) = 0;
};

class Quicksort : public SortStrategy {
public:
    virtual void sort(int arr[], int left, int right) {
        int i = left, j = right;
        int tmp;
        int pivot = arr[(left + right) / 2];

        /* partition */
        while (i <= j) {
            while (arr[i] < pivot)
                i++;
            while (arr[j] > pivot)
                j--;
            if (i <= j) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--;
            }
        };

        /* recursion */
        if (left < j)
            sort(arr, left, j);
        if (i < right)
            sort(arr, i, right);
    }
};

class Mergesort : public SortStrategy {
public:
    virtual void sort(int arr[], int left, int right) {
        std::cout << "Merge sort()\n";
    }
};

class Heapsort : public SortStrategy {
public:
    virtual void sort(int arr[], int left, int right) {
        std::cout << "Heap sort()\n";
    }
};

// Context
class SortingStrategies {
private:
    SortStrategy *m_sort;
public:
    SortingStrategies() {}

    void set_strategy(SortStrategy *s) {
        m_sort = s;
    }

    void sort(int arr[], int left, int right) {
        m_sort->sort(arr, left, right);
    }
};


#endif //DESIGN_PATTERNS_STRATEGY_HPP
