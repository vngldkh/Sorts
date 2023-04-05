#include <chrono>
#include "sorts.h"

/**
 * Сортировка пузырьком (1-е + 2-е условие Айверсона) с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds BubbleSortIverson2::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    uint32_t temp;
    size_t pos, temp_pos = size - 1;

    do {
        pos = 0;
        // Сдвигаем максимум неотсортированной части в её конец.
        for (size_t j = 0; j < temp_pos; ++j) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                pos = j;
            }
        }
        // Задаём конец неотсортированной части, как позицию последнего обмена.
        temp_pos = pos;
    } while (pos != 0);
    // Пока был совершён хотя бы один обмен.

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

/**
 * Сортировка пузырьком (1-е + 2-е условие Айверсона) с подсчётом числа элементарных операций.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число элементарных операций.
 */
size_t BubbleSortIverson2::opSort(uint32_t*& arr, size_t size) {
    size_t op_count = 1 + 1 + 4;
    uint32_t temp;
    size_t pos, temp_pos = size - 1;

    do {
        op_count += 1;
        pos = 0;

        op_count += 2 + 6;
        for (size_t j = 0; j < temp_pos; ++j) {
            op_count += 2 + 3 + 1;
            if (arr[j] > arr[j + 1]) {
                op_count += 3;
                temp = arr[j];
                op_count += 5;
                arr[j] = arr[j + 1];
                op_count += 4;
                arr[j + 1] = temp;

                op_count += 2;
                pos = j;
            }
            op_count += 3 + 3;
        }
        op_count += 2 + 2;
        temp_pos = pos;
    } while (pos != 0);

    return op_count;
}
