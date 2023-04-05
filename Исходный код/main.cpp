/*
 * АИСД-2, 2023, КДЗ №1
 * Гладких Иван БПИ219
 * Среда разработки - CLion
 *
 * -----------
 *
 * Что сделано:
 *
 * Написан абстрактный класс Sort, который имеет два метода:
 * - timeSort - сортировка без подсчёта операций; замеряет время и возвращает его.
 * - opSort - считает число элементарных операций и возвращает его.
 *
 * Написаны все 13 сортировок в виде классов-наследников Sort.
 *
 * Генерация массивов описана в классе Generator.
 * Тестирование одной сортировке на одном входном массиве описано в файле Test.cpp.
 * В классе Utility описаны дополнительные функции: копирование массива, проверка на отсортированность.
 *
 * В ходе тестирования было сгенерировано 4 csv файла (2 размера массива x 2 единицы измерения).
 * С помощью этих файлов были составлены графики и написан отчет.
 *
 * -----------
 *
 * Что не сделано:
 *
 * Число операций не усредняется, т.к. это не имеет никакого смысла:
 * - Повторные тесты проводятся на том же массиве (не отсортированном);
 * - Все алгоритмы детерменированные.
 */

#include <iostream>
#include <algorithm>
#include "Sorts/sorts.h"
#include "Generator.h"
#include "Test.cpp"

using std::get;

int main() {
    srand(time(nullptr));

    // Задаём границы массивов и строковое обозначение (для названий файлов).
    std::tuple<size_t, size_t, size_t, std::string> boundaries[] = {{50,  300,  50,  "50-300"},
                                                                    {100, 4100, 100, "100-4100"}};
    // Задаём вектор из сортировок.
    std::vector<Sort *> sorts = {new SelectionSort(),
                                 new BubbleSort(),
                                 new BubbleSortIverson1(),
                                 new BubbleSortIverson2(),
                                 new InsertionSort(),
                                 new BinaryInsertionSort(),
                                 new CountSort(),
                                 new RadixSort(),
                                 new MergeSort(),
                                 new QuickSort(),
                                 new HeapSort(),
                                 new ShellSortCiura(),
                                 new ShellSort()};
    // Задаём вектор из названий сортировок для наименования столбцов таблиц.
    // Можно было добавить в класс, но не хотелось переделывать.
    std::vector<std::string> sort_names = {"Selection",
                                           "Bubble",
                                           "Bubble 1 Iverson's condition",
                                           "Bubble 1 + 2 Iverson's conditions",
                                           "Insertion",
                                           "Binary insertion",
                                           "Count",
                                           "Radix",
                                           "Merge",
                                           "Quick",
                                           "Heap",
                                           "Shell (Ciura sequence)",
                                           "Shell (Shell sequence)"};
    // Названия типов массивов для наименования столбцов таблиц.
    std::vector<std::string> array_types = {"Random 0-5",
                                            "Random 0-4100",
                                            "Almost sorted",
                                            "Reverse sorted"};

    // Проходимся по двум наборов для размеров массива.
    for (const auto &range: boundaries) {
        // Формируем название файлов.
        std::string name = "219_Gladkikh_Ivan_" + get<3>(range);
        // Таблица для замеров времени.
        std::ofstream time_table(name + "_ns.csv");
        // Таблица для элементарных операций.
        std::ofstream eo_table(name + "_EO.csv");

        size_t max_size = get<1>(range);
        size_t step = get<2>(range);

        // Генерируем массивы разных типов.
        std::vector<uint32_t *> arrays = {Generator::randArray(5, max_size),
                                          Generator::randArray(4100, max_size),
                                          Generator::almostSorted(max_size),
                                          Generator::descending(max_size)};

        // Заполняем первую строку таблицы.
        time_table << "Size;";
        eo_table << "Size;";
        // Проходимся по 13 видам сортировок.
        for (size_t i = 0; i < 13; ++i) {
            // Проходимся по типам массивов.
            for (size_t j = 0; j < 4; ++j) {
                // Вписываем название столбца.
                time_table << sort_names[i] << " - " << array_types[j] << ";";
                eo_table << sort_names[i] << " - " << array_types[j] << ";";
            }
        }
        time_table << '\n';
        eo_table << '\n';

        // Проходимся по размеров массивов от меньшей границы к большей из заданного набора.
        for (size_t size = get<0>(range); size <= max_size; size += step) {
            // В первый столбец вписываем текущий размер массива.
            time_table << std::to_string(size) << ";";
            eo_table << std::to_string(size) << ";";

            // Проходимся по 13 видам сортировок.
            for (size_t sort_no = 0; sort_no < 13; ++sort_no) {
                // Проходимся по 4 типам массивов.
                for (size_t arr_no = 0; arr_no < 4; ++arr_no) {
                    // Копируем первые size элементов из сгенерированного массива.
                    auto copy_arr = Utility::copy(arrays[arr_no], size);
                    // Тестируем заданный набор (массив, сортировка).
                    auto res = singleTest(copy_arr, size, sorts[sort_no]);
                    // Вписываем результаты в таблицы.
                    time_table << std::to_string(get<0>(res).count()) << ";";
                    eo_table << std::to_string(get<1>(res)) << ";";

                    delete[] get<2>(res);
                    delete[] get<3>(res);
                    delete[] copy_arr;
                }
            }

            time_table << '\n';
            eo_table << '\n';
        }

        time_table.close();
        eo_table.close();

        for (size_t i = 0; i < 4; ++i) {
            delete[] arrays[i];
        }
    }

    for (size_t i = 0; i < 13; ++i) {
        delete sorts[i];
    }
}
