#include <chrono>
#include "sorts.h"

/**
 * Просеивание кучи без подсчёта числа ЭО.
 * @param arr Куча.
 * @param size Размер кучи.
 * @param ind Начальный индекс.
 */
void timeHeapify(uint32_t* arr, size_t size, size_t ind) {
    bool flag = true;

    size_t current_ind = ind;

    while (flag) {
        size_t smallest_child = current_ind;
        size_t left_child = 2 * current_ind + 1;
        size_t right_child = 2 * current_ind + 2;

        if (left_child < size && arr[left_child] < arr[smallest_child]) {
            smallest_child = left_child;
        }

        if (right_child < size && arr[right_child] < arr[smallest_child]) {
            smallest_child = right_child;
        }

        flag = false;

        if (smallest_child != current_ind) {
            std::swap(arr[smallest_child], arr[current_ind]);
            current_ind = smallest_child;
            flag = true;
        }
    }
}

/**
 * Пирамидальная сортировка с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds HeapSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    uint32_t* res = new uint32_t[size];
    size_t heap_size = size;

    // Заполняем кучу.
    for (size_t i = size / 2 + 1; i > 0; --i) {
        timeHeapify(arr, heap_size, i - 1);
    }

    // Size раз достаём из кучи верхний эелемент и записываем в новый массив.
    for (size_t i = 0; i < size; ++i) {
        auto temp = arr[0];
        arr[0] = arr[--heap_size];
        timeHeapify(arr, heap_size, 0);
        res[i] = temp;
    }

    delete[] arr;
    arr = res;

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

size_t opHeapify(uint32_t* arr, size_t size, size_t ind) {
    bool flag = true;
    size_t current_ind = ind;
    size_t op_count = 2;

    op_count += 1;
    while (flag) {
        op_count += 2 + 4 + 4;
        size_t smallest_child = current_ind;
        size_t left_child = 2 * current_ind + 1;
        size_t right_child = 2 * current_ind + 2;

        if ((op_count += 3) && left_child < size &&
            (op_count += 5) && arr[left_child] < arr[smallest_child]) {
            op_count += 2;
            smallest_child = left_child;
        }

        if ((op_count += 3) && right_child < size &&
            (op_count += 5) && arr[right_child] < arr[smallest_child]) {
            op_count += 2;
            smallest_child = right_child;
        }

        op_count += 1;
        flag = false;

        op_count += 3;
        uint32_t temp;
        if (smallest_child != current_ind) {
            op_count += 3;
            temp = arr[smallest_child];
            op_count += 4;
            arr[smallest_child] = arr[current_ind];
            op_count += 3;
            arr[current_ind] = temp;
            op_count += 2;
            current_ind = smallest_child;
            op_count += 1;
            flag = true;
        }
    }

    return op_count;
}

/**
 * Пирамидальная сортировка с подсчётом числа элементарных операций.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число элементарных операций.
 */
size_t HeapSort::opSort(uint32_t*& arr, size_t size) {
    size_t op_count = 4;
    uint32_t* res = new uint32_t[size];
    size_t heap_size = size;

    op_count += 6;
    for (size_t i = size / 2 + 1; i > 0; --i) {
        op_count += opHeapify(arr, heap_size, i - 1) + 3 + 2;
    }

    op_count += 4;
    for (size_t i = 0; i < size; ++i) {
        op_count += 2;
        auto temp = arr[0];
        op_count += 5;
        arr[0] = arr[--heap_size];
        op_count += opHeapify(arr, heap_size, 0) + 3;
        res[i] = temp;
    }

    op_count += 2;
    delete[] arr;
    arr = res;

    return op_count;
}
