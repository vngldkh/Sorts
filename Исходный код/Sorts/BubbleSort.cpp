#include <chrono>
#include "sorts.h"

/**
 * Сортировка пузырьком с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds BubbleSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    uint32_t temp;

    for (size_t i = 0; i < size - 1; ++i) {
        // Двигаем (i+1)-й максимум в конец.
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

/**
 * Сортировка пузырьком с подсчётом числа элементарных операций.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число элементарных операций.
 */
size_t BubbleSort::opSort(uint32_t*& arr, size_t size) {
    size_t op_count = 1;
    uint32_t temp;

    op_count += 2 + 4;
    for (size_t i = 0; i < size - 1; ++i) {
        op_count += 2 + 6;
        for (size_t j = 0; j < size - i - 1; ++j) {
            op_count += 2 + 3 + 1;
            if (arr[j] > arr[j + 1]) {
                op_count += 3;
                temp = arr[j];
                op_count += 5;
                arr[j] = arr[j + 1];
                op_count += 4;
                arr[j + 1] = temp;
            }
            op_count += 3 + 6;
        }
        op_count += 3 + 4;
    }

    return op_count;
}
