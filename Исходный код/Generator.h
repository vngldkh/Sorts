#ifndef TASK_GENERATOR_H
#define TASK_GENERATOR_H

#include <iostream>
#include <algorithm>

class Generator {
public:
    static uint32_t *randArray(uint32_t, size_t);
    static uint32_t *almostSorted(size_t);
    static uint32_t *descending(size_t);
};

#endif //TASK_GENERATOR_H
