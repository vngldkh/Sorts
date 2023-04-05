#include <chrono>
#include "sorts.h"

const uint16_t base = 10;
uint32_t divider;

uint16_t getDigit(int64_t x) {
    return x / divider % base;
}

/**
 * Поразрядная (цифровая) сортировка с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds RadixSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    uint32_t* sorted;
    divider = 1;
    auto* count = new size_t[base];

    // Проходимся по всем разрядам от младшего к старшему, сортируем числа по цифре текущего разряда
    // с помощью сортировки подсчётом.
    for (uint16_t digit = 0; digit < 4; ++digit) {
        for (uint16_t i = 0; i < base; ++i) {
            count[i] = 0;
        }

        for (size_t i = 0; i < size; ++i) {
            ++count[getDigit(arr[i])];
        }

        if (count[0] == size) {
            break;
        }

        for (uint16_t i = 1; i < base; ++i) {
            count[i] += count[i - 1];
        }

        sorted = new uint32_t[size];

        for (size_t i = size; i > 0; --i) {
            sorted[--count[getDigit(arr[i - 1])]] = arr[i - 1];
        }

        delete[] arr;
        arr = sorted;

        divider *= base;
    }

    delete[] count;

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

/**
 * Поразрядная (цифровая) сортировка с подсчётом ЭО.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число ЭО.
 */
size_t RadixSort::opSort(uint32_t*& arr, size_t size) {
    size_t op_count = 2;

    uint32_t* sorted;
    divider = 1;
    auto* count = new size_t[base];

    op_count += 3;
    for (uint16_t digit = 0; digit < 4; ++digit) {
        op_count += 4;
        for (uint16_t i = 0; i < base; ++i) {
            op_count += 3;
            count[i] = 0;
            op_count += 3 + 3;
        }

        op_count += 4;
        for (size_t i = 0; i < size; ++i) {
            op_count += 2 + 2 + 3;
            ++count[getDigit(arr[i])];
            op_count += 3 + 3;
        }

        op_count += 3;
        if (count[0] == size) {
            break;
        }

        op_count += 4;
        for (uint16_t i = 1; i < base; ++i) {
            op_count += 7;
            count[i] += count[i - 1];
            op_count += 3 + 3;
        }

        op_count += 1;
        sorted = new uint32_t[size];

        op_count += 3;
        for (size_t i = size; i > 0; --i) {
            op_count += 3 + 3 + 2 + 1 + 2 + 1 + 1;
            sorted[--count[getDigit(arr[i - 1])]] = arr[i - 1];
        }

        op_count += 2;
        delete[] arr;
        arr = sorted;

        op_count += 4;
        divider *= base;
    }

    op_count += 1;
    delete[] count;

    return op_count;
}
