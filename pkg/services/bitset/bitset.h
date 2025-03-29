#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//Наша структура является эсвоего рода шаблоном для будущих 
//созданных объектов(множеств - в нашем случае) - на основе этой 
//структуры, такие объекты созданные на основе структуры/класса
//называются экземпляром структуры/класса - соотвественно.
typedef struct {
    uint64_t* bits; // указатель на динамический массив битов(блок битов) по 64 бита каждый блок
    size_t size; // размер множества
    size_t capacity; // капасити множества(потенциальный размер множества)
} BitSet;


//Конструктор нашей структуры:
BitSet bitset_create(size_t capacity);

//Методы(правильнее функции) нашей структуры BitSet:
void bitset_add(BitSet* set, int element);//добавление одного элемента
void bitset_add_many(BitSet* set, int* array, int length);//добавление множества элемента
void bitset_remove(BitSet* set, int element);//удаление одного элемента
void bitset_remove_many(BitSet* set, int* array, int length);//удаление множества элемента

//функция для сравнения длины capacity:
int max(size_t a, size_t b);

bool bitset_contains(const BitSet* set, int element);//входит ли элемент в множество
bool compare_sets(BitSet* setA, BitSet* setB);//сравнение множеств, являются ли множества одинаковыми
bool set_is_subset(BitSet* setA, BitSet* setB);//является ли множество множество А подмножеством В(входит ли)
bool set_is_strong_subset(BitSet* setA, BitSet* setB);//является ли множество множество А строгим 
//подмножеством В(строгое включение)

BitSet get_union_set(BitSet* setA, BitSet* setB);//обьединение множество
BitSet get_intersection_set(BitSet* setA, BitSet* setB);//персение множеств
BitSet get_difference_set(BitSet* setA, BitSet* setB);//разность множеств
BitSet get_symmetric_difference_set(BitSet* setA, BitSet* setB);//симетрическая разность
BitSet get_complement_set(BitSet* setA);//дополнение множества(отрицание множества)

//Деструктор нашей структуры, который необходим для освобождения память 
void bitset_destroy(BitSet* set);

