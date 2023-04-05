#include <chrono>
#include <utility>
#include "sorts.h"

/**
 * Метод бинарного поиска для определения позиции элемента в отсортированной части массива.
 * Без подсчёта числа операций.
 * @param arr Указатель на массив.
 * @param elem Элемент, позицию которого хотим определить.
 * @param begin Позиция начала поиска.
 * @param end Позиция конца поиска.
 * @return Позиция элемента.
 */
size_t timeBinarySearch(uint32_t*& arr, uint32_t elem, size_t begin, size_t end) {
    size_t left = begin, right = end, mid;

    if (left >= right) {
        return elem >= arr[left] ? left + 1 : left;
    }

    while (left + 1 < right) {
        mid = left + (right - left) / 2;
        if (arr[mid] <= elem) {
            left = mid;
        } else {
            right = mid;
        }
    }
    if (arr[right] <= elem) {
        return right + 1;
    }
    if (arr[left] <= elem) {
        return right;
    }
    return left;
}

/**
 * Сортировка бинарными вставками с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds BinaryInsertionSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    uint32_t temp;
    size_t j, k;
    // Считаем, что размер отсортированной части - 1. Один элемент отсортирован.
    // Проходимся по всем элементам от 1 до size - 1.
    for (size_t i = 1; i < size; ++i) {
        // Позиция последнего элемента в отсортированной части.
        j = i - 1;
        temp = arr[i];
        // Определяем позицию текущего элемента в отсортированной части.
        k = timeBinarySearch(arr, temp, 0, j);
        // Сдвигаем все элементы после k-й позиции.
        for (size_t m = j + 1; m > k; --m) {
            arr[m] = arr[m - 1];
        }
        arr[k] = temp;
    }

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

std::pair<size_t, size_t> opBinarySearch(uint32_t*& arr, uint32_t elem, size_t begin, size_t end) {
    size_t left = begin, right = end, mid, count = 5;

    count += 3;
    if (left >= right) {
        count += 4;
        return elem >= arr[left] ?
               std::make_pair(left + 1, count) :
               std::make_pair(left, count);
    }

    count += 4;
    while (left + 1 < right) {
        count += 6;
        mid = left + (right - left) / 2;
        count += 4;
        if (arr[mid] <= elem) {
            count += 2;
            left = mid;
        } else {
            count += 2;
            right = mid;
        }
        count += 4;
    }

    count += 4 + 1;
    if (arr[right] <= elem) {
        count += 1;
        return std::make_pair(right + 1, count);
    }
    count += 4;
    if (arr[left] <= elem) {
        return std::make_pair(right, count);
    }
    return std::make_pair(left, count);
}

/**
 * Сортировка бинарными вставками с посдчётом числа элементарных операций.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число элементарнхых операций.
 */
size_t BinaryInsertionSort::opSort(uint32_t*& arr, size_t size) {
    uint32_t temp;
    size_t j, k, op_count = 3;

    op_count += 2 + 3;
    for (size_t i = 1; i < size; ++i) {
        op_count += 3;
        j = i - 1;
        op_count += 3;
        temp = arr[i];
        auto p = opBinarySearch(arr, temp, 0, j);
        k = p.first;
        op_count += p.second;
        op_count += 4 + 3;
        for (size_t m = j + 1; m > k; --m) {
            op_count += 5;
            arr[m] = arr[m - 1];
        }
        op_count += 3;
        arr[k] = temp;
    }

    return op_count;
}

