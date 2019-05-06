#pragma once

#include <vector>
#include <iostream>

template <typename T>
class MaxHeap
{
    std::vector<T> nodes;

public:
    MaxHeap(const std::vector<T> &arr) : nodes(std::move(arr))
    {
        this->build_heap();
    }

    T extract()
    {
        int n = this->nodes.size() - 1;
        if (n < 0) return -1;
        T max = nodes[0];

        this->nodes.erase(nodes.begin());
        this->max_heapify(0, n - 1);
        return max;
    }

    T peek() const
    {
        if (this->nodes.empty()) return -1;
        return nodes[0];
    }

    void insert(T key)
    {
        this->nodes.emplace_back(key);
        this->build_heap();
    }

    void increase_key(int i, T key)
    {
        if (this->nodes[i] >= key)
        {
            std::cout << "New key <= current key!" << std::endl;
            return;
        }
        this->nodes[i] = key;
        while (i && this->nodes[parent(i)] < this->nodes[i])
        {
            std::swap(this->nodes[i], this->nodes[parent(i)]);
            i = parent(i);
        }
    }

    void debug_priority_queue()
    {
        std::vector<T> tmp;
        std::cout << "Debugging priority queue. "
                  << "Will extract keys from the heap."
                  << std::endl << "  -> ";
        while (!nodes.empty())
        {
            T val = extract();
            std::cout << val << " ";
            tmp.emplace_back(val);
        }
        std::cout << std::endl << "Rebuilding the heap..."
                  << std::endl << std::endl;
        this->nodes.swap(tmp);
        this->build_heap();
    }

private:
    int parent (int i) { return   --i / 2; }
    int left   (int i) { return 2 * i + 1; }
    int right  (int i) { return 2 * i + 2; }

    void build_heap()
    {
        int n = this->nodes.size() - 1;
        for (int i = n / 2; i >= 0; --i)
            this->max_heapify(i, n);
    }

    void max_heapify(int i, int n)
    {
        int L = this->left(i);
        int R = this->right(i);
        int largest = i;

        if (L <= n && this->nodes[i] < this->nodes[L])
            largest = L;
        if (R <= n && this->nodes[largest] < this->nodes[R])
            largest = R;
        if (largest != i)
        {
            std::swap(this->nodes[i], this->nodes[largest]);
            max_heapify(largest, n);
        }
    }
};
