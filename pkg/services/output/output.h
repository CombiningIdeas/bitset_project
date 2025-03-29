#pragma once

#include <stdint.h>
#include "../bitset/bitset.h"

// Вывод множества в битовом виде:
void print_bitwise_set(const char* setName, uint64_t* bits, const size_t capacity);

// Вывод множества в стандартном виде:
void print_set_elements(const BitSet* set, size_t capacity);