#include <chrono>
#include "sorts.h"

/**
 * Сортировка Шелла (последовательность Циура) с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds ShellSortCiura::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    // Записываем последовательность Циура.
    uint32_t ciura[] = {0, 1, 4, 10, 23, 57, 132, 301, 701, 1750};
    uint32_t temp;
    // Проходимся по элементам последовательности.
    for (uint32_t k = 9; k != 0; --k) {
        uint32_t d = ciura[k];
        // Обмениваем элементы, отстающие на расстояние d, если они нарушают порядок.
        for (auto i = d; i < size; ++i) {
            for (auto j = i; j >= d && arr[j - d] > arr[j]; j -= d) {
                temp = arr[j];
                arr[j] = arr[j - d];
                arr[j - d] = temp;
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

/**
 * Сортировка Шелла (последовательность Циура) с подсчётом ЭО.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число ЭО.
 */
size_t ShellSortCiura::opSort(uint32_t*& arr, size_t size) {
    size_t op_count = 0;

    op_count += 10;
    uint32_t ciura[] = {0, 1, 4, 10, 23, 57, 132, 301, 701, 1750};
    uint32_t temp;

    op_count += 3;
    for (uint32_t k = 9; k != 0; --k) {
        op_count += 3;
        uint32_t d = ciura[k];
        op_count += 2 + 3;
        for (auto i = d; i < size; ++i) {
            op_count += 2;
            for (auto j = i;
                 (op_count += 3) && j >= d &&
                 (op_count += 2 + 4 + 1) && arr[j - d] > arr[j];
                 j -= d) {
                op_count += 3;
                temp = arr[j];
                op_count += 4 + 2;
                arr[j] = arr[j - d];
                op_count += 5;
                arr[j - d] = temp;
                op_count += 4;
            }
            op_count += 3;
        }
        op_count += 3;
    }

    return op_count;
}
