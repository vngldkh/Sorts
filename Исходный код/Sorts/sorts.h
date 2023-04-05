#ifndef TASK_SORTS_H
#define TASK_SORTS_H

#include <chrono>

/**
 * Abstract sort class.
 */
class Sort {
public:
    virtual std::chrono::nanoseconds timeSort(uint32_t*&, size_t) = 0;
    virtual size_t opSort(uint32_t*&, size_t) = 0;
    ~Sort() = default;
};

class SelectionSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class BubbleSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class BubbleSortIverson1 : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class BubbleSortIverson2 : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class InsertionSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class BinaryInsertionSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class CountSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class RadixSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class MergeSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class QuickSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class HeapSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class ShellSort : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

class ShellSortCiura : public Sort {
    std::chrono::nanoseconds timeSort(uint32_t*&, size_t) override;
    size_t opSort(uint32_t*&, size_t) override;
};

#endif //TASK_SORTS_H
