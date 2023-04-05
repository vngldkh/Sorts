#include <chrono>
#include "sorts.h"

/**
 * Сортировка пузырьком (1-е условие Айверсона) с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds BubbleSortIverson1::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    uint32_t temp;
    size_t i = 0;
    bool flag = true;
    // Пока за проход был сделан хотя бы один обмен, повторяем.
    while (flag) {
        flag = false;
        // Двигаем (i+1)-й максимальный элементы в конец.
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = true;
            }
        }
        ++i;
    }

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

/**
 * Сортировка пузырьком (1-е условие Айверсона) с подсчётом числа элементарных операций.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число элементарных операций.
 */
size_t BubbleSortIverson1::opSort(uint32_t*& arr, size_t size) {
    size_t op_count = 1 + 2 + 2;
    uint32_t temp;
    size_t i = 0;
    bool flag = true;

    op_count += 1;
    while (flag) {
        op_count += 1;
        flag = false;

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

                op_count += 1;
                flag = true;
            }
            op_count += 3 + 6;
        }
        op_count += 3 + 1;
        ++i;
    }

    return op_count;
}
