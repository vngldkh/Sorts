#include <chrono>
#include "sorts.h"

/**
 * Рекурсивная функция для быстрой сортировки без подсчёта ЭО.
 * @param arr Указатель на сортируемую часть массива.
 * @param size Размер сортируемой части массива.
 */
void timeQuickSort(uint32_t* arr, size_t size) {
    if (size <= 1) {
        return;
    }

    // Обозначаем первый элемент как опорный.
    uint32_t pivot = arr[0], temp;
    // Обозначаем позицию первого элемента больше опорного.
    size_t pivot_pos = 1;

    // Проходимся по всем элементам (кроме опорного).
    for (size_t i = 1; i < size; ++i) {
        // Если находится элемент < опорного, меняем его с первым элементом > опорного и сдвигаем эту позицию.
        if (arr[i] < pivot) {
            temp = arr[i];
            arr[i] = arr[pivot_pos];
            arr[pivot_pos++] = temp;
        }
    }

    // Обмениваем опорноый элемент, с последним меньше его.
    arr[0] = arr[pivot_pos - 1];
    arr[pivot_pos - 1] = pivot;

    // Рекурсивно сортируем левую и правую части относительно опорного.
    if (size >= pivot_pos) {
        timeQuickSort(arr, pivot_pos);
        timeQuickSort(arr + pivot_pos, size - pivot_pos);
    }
}

/**
 * Быстрая сортировка с замером времени.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Время сортировки.
 */
std::chrono::nanoseconds QuickSort::timeSort(uint32_t*& arr, size_t size) {
    auto begin = std::chrono::steady_clock::now();

    timeQuickSort(arr, size);

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
}

size_t opQuickSort(uint32_t* arr, size_t size) {
    size_t op_count = 2;

    if (size == 1) {
        return op_count;
    }

    op_count += 2;
    uint32_t pivot = arr[0], temp;
    size_t pivot_pos = 1;

    op_count += 4;
    for (size_t i = 1; i < size; ++i) {
        op_count += 4;
        if (arr[i] < pivot) {
            op_count += 3;
            temp = arr[i];
            op_count += 4;
            arr[i] = arr[pivot_pos];
            op_count += 3 + 2;
            arr[pivot_pos++] = temp;
        }
    }

    op_count += 4;
    arr[0] = arr[pivot_pos - 1];
    op_count += 4;
    arr[pivot_pos - 1] = pivot;

    if (size >= pivot_pos) {
        op_count += opQuickSort(arr, pivot_pos);
        op_count += opQuickSort(arr + pivot_pos, size - pivot_pos);
    }

    return op_count;
}

/**
 * Быстрая сортировка с подсчётом ЭО.
 * @param arr Сортируемый массив.
 * @param size Размер массива.
 * @return Число ЭО.
 */
size_t QuickSort::opSort(uint32_t*& arr, size_t size) {
    return opQuickSort(arr, size);
}
