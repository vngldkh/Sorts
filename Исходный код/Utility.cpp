#include <algorithm>
#include "Utility.h"

/**
 * Копирует первые size элементов массива arr.
 * @param arr Указатель на массив.
 * @param size Размер копии.
 * @return Ссылка на копию.
 */
uint32_t* Utility::copy(const uint32_t* arr, size_t size) {
    uint32_t* copy_arr = new uint32_t[size];
    for (size_t i = 0; i < size; ++i) {
        copy_arr[i] = arr[i];
    }
    return copy_arr;
}

/**
 * Проверяет, является ли массив отсортированным.
 * @param mas Указатель на изначальный массив.
 * @param sorted Указатель на предположительно отсортированный массив.
 * @param size Размер массивов.
 * @return true, если массив отсортирован верно; false, если он не отсортирован или был поврежден.
 */
bool Utility::isSorted(const uint32_t* mas, const uint32_t* sorted, size_t size) {
    auto* arr = copy(mas, size);
    std::sort(arr, arr + size);
    bool flag;
    for (size_t i = 0; i < size; ++i) {
        flag = arr[i] == sorted[i];
        if (!flag) {
            delete[] arr;
            return false;
        }
    }
    delete[] arr;
    return true;
}
