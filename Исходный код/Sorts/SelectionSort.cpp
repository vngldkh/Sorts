#include "sorts.h"
#include <chrono>

/**
 * Сортировка выбором с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds SelectionSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    size_t min;
    uint32_t temp;
    // Проходимся по всем элементам (кроме последнего).
    for (size_t i = 0; i < size - 1; ++i) {
        min = i;
        // Определяем позицию минимального элемента.
        for (size_t j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        // Обмениваем с текущим.
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

/**
 * Сортировка выбором с подсчётом ЭО.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число ЭО.
 */
size_t SelectionSort::opSort(uint32_t*& arr, size_t size) {
    size_t operation_count = 2;

    size_t min;
    uint32_t temp;

    /* 1 - выделение памяти,
     * 2 - запись в 0 память,
     * 3 - получение значения size,
     * 4 - вычисление size - 1,
     * 5 - получение i,
     * 6 - сравнение.
     */
    operation_count += 6;
    for (size_t i = 0; i < size - 1; ++i) {
        // 1 - получение значения i, 2 - присвоение.
        operation_count += 2;
        min = i;

        /* 1 - выделение памяти,
         * 2 - получение i,
         * 3 - вычисление i + 1,
         * 4-6 - сравнение.
         */
        operation_count += 6;
        for (size_t j = i + 1; j < size; ++j) {
            /* 1 - получение j,
             * 2 - получение arr[j],
             * 3 - получение min,
             * 4 - получение arr[min],
             * 5 - сравнение.
             */
            operation_count += 5;
            if (arr[j] < arr[min]) {
                /* 1 - получение j,
                 * 2 - запись в min значения j.
                 */
                operation_count += 2;
                min = j;
            }

            /* 1-3 - ++j,
             * 4 - получение size,
             * 5 - получение i,
             * 6 - сравнение.
             */
            operation_count += 6;
        }
        operation_count += 3;
        temp = arr[i];
        operation_count += 4;
        arr[i] = arr[min];
        operation_count += 3;
        arr[min] = temp;

        /* 1-3 - ++i,
         * 4 - получение size,
         * 5 - вычисление size - 1,
         * 6 - получение i,
         * 7 - сравнение.
         */
        operation_count += 7;
    }

    return operation_count;
}