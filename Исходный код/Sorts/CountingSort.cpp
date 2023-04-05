#include <chrono>
#include <iostream>
#include "sorts.h"

/**
 * Устойчивая сортировка подсчётом с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds CountSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    const size_t range = 4101;
    auto* counts = new size_t[range];
    auto* res = new uint32_t[size];

    // Инициализируем массив для счёта.
    for (size_t i = 0; i < range; ++i) {
        counts[i] = 0;
    }

    // Считаем число каждого элемента.
    for (size_t i = 0; i < size; ++i) {
        ++counts[arr[i]];
    }

    // Определяем таким образом последнюю позицию для каждого элемента.
    for (size_t i = 1; i < range; ++i) {
        counts[i] += counts[i - 1];
    }

    // Идём по массиву в обратном порядке, записывая каждый элемент в новый массив на вычисленное место.
    for (size_t i = size; i > 0; --i) {
        res[--counts[arr[i - 1]]] = arr[i - 1];
    }

    delete[] arr;
    arr = res;

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

/**
 * Устойчивая сортировка подсчётом с подсчётом числа элементарных операций.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число элементарных операций.
 */
size_t CountSort::opSort(uint32_t*& arr, size_t size) {
    size_t op_count = 0;
    const size_t range = 4101;
    auto* counts = new size_t[range];
    auto* res = new uint32_t[size];

    op_count += 4;
    for (size_t i = 0; i < range; ++i) {
        op_count += 2;
        counts[i] = 0;
        op_count += 3 + 3;
    }

    op_count += 4;
    for (size_t i = 0; i < size; ++i) {
        op_count += 5;
        ++counts[arr[i]];
        op_count += 3 + 3;
    }

    op_count += 4;
    for (size_t i = 1; i < range; ++i) {
        op_count += 7;
        counts[i] += counts[i - 1];
        op_count += 3 + 3;
    }

    op_count += 4;
    for (size_t i = size; i > 0; --i) {
        op_count += 11;
        res[--counts[arr[i - 1]]] = arr[i - 1];
        op_count += 3 + 2;
    }

    op_count += 2;
    delete[] arr;
    arr = res;

    return op_count;
}
