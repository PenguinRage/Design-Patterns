//
// Created by penguinrage on 5/08/17.
//


#include <iostream>
#include <vector>
#include <utility>

#ifndef DESIGN_PATTERNS_STRATEGY_HPP
#define DESIGN_PATTERNS_STRATEGY_HPP

// TODO - changing this to vector because nobody uses C arrays anymore.


class SortStrategy {
public:
    virtual void sort(std::vector<int> &, int, int, int) = 0;
};

class Quicksort : public SortStrategy {
public:

    int partition(std::vector<int> &aVector, int left, int right, int who) {
        for (int i = left; i < right; ++i) {
            if (aVector[i] <= who) {
                std::swap(aVector[i], aVector[left]);
                left++;
            }
        }
        return left - 1;
    }

    virtual void sort(std::vector<int> &aVector, int size, int left, int right) {
        if (left >= right) return;
        int middle = left + (right - left) / 2;
        std::swap(aVector[middle], aVector[left]);
        int midpoint = partition(aVector, left + 1, right, aVector[left]);
        std::swap(aVector[left], aVector[midpoint]);
        sort(aVector, size, left, midpoint);
        sort(aVector, size, midpoint + 1, right);
    }
};

class Mergesort : public SortStrategy {
public:
    virtual void merge(std::vector<int> &aVector, int size, int low, int middle, int high) {
        int temp[size];
        for (int i = low; i <= high; i++) {
            temp[i] = aVector[i];
        }
        int i = low;
        int j = middle + 1;
        int k = low;

        while (i <= middle && j <= high) {
            if (temp[i] <= temp[j]) {
                aVector[k] = temp[i];
                ++i;
            } else {
                aVector[k] = temp[j];
                ++j;
            }
            ++k;
        }
        while (i <= middle) {
            aVector[k] = temp[i];
            ++k;
            ++i;
        }
    }

    virtual void sort(std::vector<int> &aVector, int size, int low, int high) {
        if (low < high) {
            int middle = (low + high) / 2;
            sort(aVector, size, low, middle);
            sort(aVector, size, middle + 1, high);
            merge(aVector, size, low, middle, high);
        }
    }
};

class Heapsort : public SortStrategy {
public:

    void Sift(std::vector<int> &aVector, const std::vector<int>::size_type heapSize,
              const std::vector<int>::size_type siftNode) {
        std::vector<int>::size_type i, j;

        j = siftNode;
        do {
            i = j;
            if (((2 * i + 1) < heapSize) && aVector[j] < aVector[2 * i + 1])
                j = 2 * i + 1;
            if (((2 * i + 2) < heapSize) && aVector[j] < aVector[2 * i + 2])
                j = 2 * i + 2;

            std::swap(aVector[i], aVector[j]);
        } while (i != j);
    }


    void makeHeap(std::vector<int> &aVector) {
        for (int i = (int) aVector.size() - 1; i >= 0; --i) {
            Sift(aVector, aVector.size(), i);
        }
    }

    virtual void sort(std::vector<int> &aVector, int size, int low, int high) {
        makeHeap(aVector);
        for (std::vector<int>::size_type i = aVector.size() - 1; i > 0; --i) {
            std::swap(aVector[i], aVector[0]);
            Sift(aVector, i, 0);
        }
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

    void sort(std::vector<int> &aVector, int size, int low, int high) {
        m_sort->sort(aVector, size, low, high);
    }
};


#endif //DESIGN_PATTERNS_STRATEGY_HPP
