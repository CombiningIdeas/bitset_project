#include <stdio.h>

#include "output.h"
#include "../bitset/bitset.h"

// Вывод множества в битовом виде:
void print_bitwise_set(const char* setName, uint64_t* bits, const size_t capacity) {
    // Вывод названия множества:
    printf("Множество %s в битовом виде: \n", setName);

    // Перебираем каждый бит
    for (size_t iter = 0; iter < capacity; iter++) {
        size_t block_index = iter / 64;  // Индекс блока
        size_t bit_index = 63 - (iter % 64);  // Индекс бита внутри блока

        if (((bits[block_index] >> bit_index) & 1) == 1) {
            printf("%zu ", iter);  // Печатаем индекс элемента
        }
    }
    printf("\n");
}

// Вывод множества в обычном виде:
void print_set_elements(const BitSet* set, size_t capacity) {
    printf("Множество в обычном виде: \n");

    for (int iter = 0; iter < (int)(capacity); iter++) {
        if (bitset_contains(set, iter)) {
            printf("%d ", iter);
        }
    }

    printf("\n");
}