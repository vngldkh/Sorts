#include <tuple>
#include <cstddef>
#include <chrono>
#include <iostream>
#include <fstream>
#include "Sorts/sorts.h"
#include "Utility.h"
#include "Generator.h"

/**
 * Выводит результаты теста в файл.
 * @param name Название файла.
 * @param init_arr Указатель на изначальный массив.
 * @param size Размер массива.
 * @param test_res Результат проверки.
 */
void writeTestResult(const std::string& name, uint32_t* init_arr, size_t size,
                     const std::tuple<std::chrono::nanoseconds, size_t, uint32_t*, uint32_t*>& test_res) {
    std::ofstream ofs(name);
    ofs << "Initial array: ";
    for (size_t i = 0; i < size; ++i) {
        ofs << init_arr[i] << ";";
    }
    ofs << "\n\nTime test: " << std::get<0>(test_res).count() << " ns\n";
    ofs << "Sorted array: ";
    for (size_t i = 0; i < size; ++i) {
        ofs << std::get<2>(test_res)[i] << ";";
    }
    ofs << "Are equal: " << std::boolalpha << Utility::isSorted(init_arr, std::get<2>(test_res), size);
    ofs << "\n\nEO test: " << std::get<1>(test_res) << " EO\n";
    ofs << "Sorted array: ";
    for (size_t i = 0; i < size; ++i) {
        ofs << std::get<3>(test_res)[i] << ";";
    }
    ofs << "Are equal: " << std::boolalpha << Utility::isSorted(init_arr, std::get<3>(test_res), size);
}

/**
 * Проводит тест сортировка sort на массиве arr.
 * @param arr Указатель на сортируемый массив.
 * @param size Размер массива.
 * @param sort Сортировка.
 * @return Усредненное время сортировки, число элементарный операций, указатели на отсортированные массивы.
 */
std::tuple<std::chrono::nanoseconds, size_t, uint32_t*, uint32_t*> singleTest(uint32_t* arr, size_t size, Sort* sort) {
    std::chrono::nanoseconds total_ns(0);

    uint32_t* copy_time;
    // 100 раз повторяем тест, усредняя время выполнения.
    for (size_t i = 0; i < 100; ++i) {
        if (i != 0) {
            delete[] copy_time;
        }
        copy_time = Utility::copy(arr, size);
        total_ns += sort->timeSort(copy_time, size) / 100;
    }

    uint32_t* copy_eo = Utility::copy(arr, size);
    return {total_ns, sort->opSort(copy_eo, size), copy_time, copy_eo};
}
