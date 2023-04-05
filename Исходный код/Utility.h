#ifndef TASK_UTILITY_H
#define TASK_UTILITY_H

#include <cstddef>
#include <cstdint>

class Utility {
public:
    static uint32_t* copy(const uint32_t *, size_t);
    static bool isSorted(const uint32_t *, const uint32_t *, size_t);
};

#endif //TASK_UTILITY_H
