#include <chrono>
#include <utility>
#include "sorts.h"

/**
 * Рекурсивная функция для сортировки слиянием без подсчёта ЭО.
 * @param begin Указатель на начало сортируемой части.
 * @param size Размер сортируемой части.
 * @return Указатель на отсортированную копию.
 */
uint32_t* timeMergeSort(uint32_t* begin, size_t size) {
    if (size == 1) {
        return begin;
    }

    // Рекурсивно сортируем половины массива.
    size_t mid = size / 2;
    uint32_t* first_part = timeMergeSort(begin, mid);
    uint32_t* second_part = timeMergeSort(begin + mid, size - mid);

    size_t first_counter = 0;
    size_t second_counter = 0;

    auto* res = new uint32_t[size];
    size_t res_counter = 0;

    // Производим слияние двух половин.

    while (first_counter < mid && second_counter < size - mid) {
        if (first_part[first_counter] <= second_part[second_counter]) {
            res[res_counter] = first_part[first_counter++];
        } else {
            res[res_counter] = second_part[second_counter++];
        }
        ++res_counter;
    }

    while (first_counter < mid) {
        res[res_counter++] = first_part[first_counter++];
    }
    while (second_counter < size - mid) {
        res[res_counter++] = second_part[second_counter++];
    }

    if (mid > 1) {
        delete[] first_part;
    }
    if (size - mid > 1) {
        delete[] second_part;
    }
    return res;
}

/**
 * Сортировка слиянием с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds MergeSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    arr = timeMergeSort(arr, size);

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

std::pair<uint32_t*, size_t> opMergeSort(uint32_t* begin, size_t size) {
    size_t op_count = 2;

    if (size == 1) {
        return std::make_pair(begin, op_count);
    }

    op_count += 3;
    size_t mid = size / 2;
    auto first = opMergeSort(begin, mid);
    auto second = opMergeSort(begin + mid, size - mid);
    uint32_t* first_part = first.first;
    uint32_t* second_part = second. first;
    op_count += first.second + second.second + 2;

    op_count += 2;
    size_t first_counter = 0;
    size_t second_counter = 0;

    op_count += 2 + 1;
    auto* res = new uint32_t[size];
    size_t res_counter = 0;

    while ((op_count += 3) && first_counter < mid &&
           (op_count += 5) && second_counter < size - mid) {
        op_count += 5;
        if (first_part[first_counter] <= second_part[second_counter]) {
            op_count += 3 + 1 + 2 + 1;
            res[res_counter] = first_part[first_counter++];
        } else {
            op_count += 3 + 1 + 2 + 1;
            res[res_counter] = second_part[second_counter++];
        }
        op_count += 3;
        ++res_counter;
    }

    op_count += 3;
    while (first_counter < mid) {
        op_count += 9;
        res[res_counter++] = first_part[first_counter++];
        op_count += 3;
    }
    op_count += 3;
    while (second_counter < size - mid) {
        op_count += 9;
        res[res_counter++] = second_part[second_counter++];
        op_count += 3;
    }

    return std::make_pair(res, op_count);
}

/**
 * Сортировка слиянием с подсчётом ЭО.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число ЭО.
 */
size_t MergeSort::opSort(uint32_t*& arr, size_t size) {
    auto sorted = opMergeSort(arr, size);
    arr = sorted.first;
    return sorted.second;
}
