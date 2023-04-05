#include <iostream>
#include <algorithm>
#include "Generator.h"

/**
 * Генерирует массив размера size, заполненный случайными значениями в диапазоне [0;max_val].
 * @param max_val Максимальное значение элементов массива.
 * @param size Размер массива.
 * @return Указатель на сгенерированный массив.
 */
uint32_t* Generator::randArray(uint32_t max_val, size_t size) {
    uint32_t* arr = new uint32_t[size];
    for (size_t i = 0; i < size; ++i) {
        arr[i] = abs(rand()) % (max_val + 1);
    }
    return arr;
}

/**
 * Генерирует почти отсортированный массив.
 * @param size Размер массива.
 * @return Указатель на сгенерированный массив.
 */
uint32_t* Generator::almostSorted(size_t size) {
    // Генерируем массив, заполненный случайными числами в диапазоне [0;4100].
    uint32_t* arr = randArray(4100, size);
    // Сортируем его.
    std::sort(arr, arr + size);

    // size / 6 раз меняем пару случайно выбранных элементов местами.
    for (size_t j = 0; j < size / 6; ++j) {
        size_t pos1 = abs(rand()) % size;
        size_t pos2 = abs(rand()) % size;

        std::swap(arr[pos1], arr[pos2]);
    }

    return arr;
}

/**
 * Генерирует массив, заполненный последовательными числами от 4100 в убывающей последовательности.
 * @param size Размер массива.
 * @return Указатель на сгенерированный массив.
 */
uint32_t* Generator::descending(size_t size) {
    uint32_t* arr = new uint32_t[size];
    arr[0] = 4100;
    for (size_t i = 1; i < size; ++i) {
        arr[i] = arr[i - 1] - 1;
    }
    return arr;
}

