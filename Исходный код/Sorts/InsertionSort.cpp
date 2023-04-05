#include <chrono>
#include "sorts.h"

/**
 * Сортировка обычными вставками с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds InsertionSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    uint32_t key;
    size_t i;
    // Проходимся по всем элементам, кроме 1, т.к. он уже отсортирован.
    for (size_t j = 1; j < size; ++j) {
        key = arr[j];
        i = j;
        // Сдвигаем отсортированную часть массива, пока не дойдём до позиции текущего элемента.
        while (i > 0 && arr[i - 1] > key) {
            arr[i] = arr[i - 1];
            --i;
        }
        // Вставляем текущий элемент в отсортированную часть.
        arr[i] = key;
    }

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

/**
 * Сортировка обычными вставками с подсчётом числа ЭО.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число элементарных операций.
 */
size_t InsertionSort::opSort(uint32_t*& arr, size_t size) {
    size_t op_count = 2;

    uint32_t key;
    size_t i;

    op_count += 2 + 3;
    for (size_t j = 1; j < size; ++j) {
        op_count += 3 + 2;
        key = arr[j];
        i = j;

        op_count += 2 + 1 + 5;
        while (i > 0 && arr[i - 1] > key) {
            op_count += 5;
            arr[i] = arr[i - 1];
            op_count += 3;
            --i;
            op_count += 8;
        }
        op_count += 3;
        arr[i] = key;
    }

    return op_count;
}
