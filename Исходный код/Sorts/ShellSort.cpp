#include <chrono>
#include "sorts.h"

/**
 * Сортировка Шелла (последовательность Шелла) с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds ShellSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    uint32_t temp;
    // Цикл по расстоянию (начинается с size / 2, на каждой итерации уменьшается вдвое).
    for (auto d = size / 2; d != 0; d /= 2) {
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
 * Сортировка Шелла (последовательность Шелла) с подсчётом ЭО.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число ЭО.
 */
size_t ShellSort::opSort(uint32_t*& arr, size_t size) {
    size_t op_count = 0;

    uint32_t temp;
    op_count += 5;
    for (auto d = size / 2; d != 0; d /= 2) {
        op_count += 5;
        for (auto i = d; i < size; ++i) {
            op_count += 2;
            for (auto j = i;
                 (op_count += 3) && j >= d &&
                 (op_count += 7) && arr[j - d] > arr[j]; j -= d) {
                op_count += 3;
                temp = arr[j];
                op_count += 6;
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
