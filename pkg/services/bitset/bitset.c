#include "bitset.h"


int max(size_t a, size_t b) {
    return (a > b) ? a : b;
}


// Функция(Деструктор) для создания нового битового множества 
BitSet bitset_create(size_t capacity) {
    BitSet set;
    set.size = 0;//текущая длинна равно 0
    set.capacity = capacity;

    // Выделяем память для массива битов а так как calloc работает с байтами то переведем в байты,
    // беря с запасом, то есть коругляя в большую сторону, и выделенную память преобрузем к типу 
    // указателя (uint64_t*) и присваеваем её в поле структуры 
    // calloc(кол-во элементов, размер каждого элемента в байтах):
    set.bits = (uint64_t*)calloc((capacity + 63) >> 6, sizeof(uint64_t));
    // Поскольку каждый элемент массива типа uint64_t может содержать 64 бита, 
    // деление на 64(или же битовое >> 6) и добавление 63 обеспечивают 
    //округление lj до большего (если capacity не кратно 64).

    return set;//возращаем созданное множество 
}

// Функция для добавления одного элемента в множество
void bitset_add(BitSet* set, int element) {
    // Проверяем, находится ли элемент в допустимом диапазоне:
    if ((element >= 0) && (((size_t)element) < set->capacity)) {
        
        // Вычисляем индекс в массиве и номер бита в конкретном индексе:
        size_t index = element >> 6;  // Сдвигаем на 6 битов вправо (деление на 64)
        // Деление на 64 можно заменить на сдвиг влево на 6 битов, потому что 64 — это 2 в 
        // степени 6. Сдвиг на 6 битов вправо эквивалентен делению на 64. Это быстрее, чем 
        // обычное деление, так как сдвиг является операцией, выполняемой за один такт процессора.

        size_t bit = element & 63;    // Маска для извлечения последних 6 битов (остаток от деления 
        // на 64). Остаток от деления на 64 можно извлечь с помощью побитовой операции И (&). 
        // Маска 63 (в двоичной записи 111111) оставляет только последние 6 бит числа, что 
        // эквивалентно взятию остатка от деления на 64.
        
        unsigned long long mask = 1ULL << bit;  // Маска для нужного бита
        if (!(set->bits[index] & mask)) {  // Проверка, если бит ещё не установлен
            set->bits[index] = set->bits[index] | mask;  // Устанавливаем бит в 1
            set->size++;  // Увеличиваем количество установленных битов
        }
    }
}

// Функция для добавления множества элементов
void bitset_add_many(BitSet* set, int* array, int length) {
    for (int iter = 0; iter < length; iter++) {
        bitset_add(set, array[iter]);
    }
}

// Функция для удаления одного элемента из множества
void bitset_remove(BitSet* set, int element) {
    // Проверяем, находится ли элемент в допустимом диапазоне:
    if ((element >= 0) && (((size_t)element) < set->capacity)) {
        size_t index = element >> 6; // index - это конкретный элемент массива, которые является 64-битным числом.
        size_t bit   = element & 63; // bit - это позиция конкретного бита в 64-битном числе. 
        
        // Используем маску для сброса бита:
        unsigned long long mask = 1ULL << bit;
        if (set->bits[index] & mask) {
            set->bits[index] = set->bits[index] & ~mask; // Сбрасываем бит, делаем побитовую 
            // инверсию каждого числа, каждый бит числа меняется на противоположный
            set->size--; // Уменьшаем размер установленных битов
        }
    }
}

// Функция для удаления множества элементов
void bitset_remove_many(BitSet* set, int* array, int length) {
    for (int iter = 0; iter < length; iter++) {
        bitset_remove(set, array[iter]);
    }
}

// Функция для проверки наличия элемента в множестве
bool bitset_contains(const BitSet* set, int element) {

    bool result = true;//если бит установлен и все проверки будут успешно 
    // пройдены, то значение не измениться

    // Не учитываем элементы вне диапазона:
    if ((element < 0) || (((size_t)element) >= set->capacity)) {
        result = false;  // Элемент вне диапазона, возвращаем false
    } else {
        size_t index = element >> 6; // Индекс в массиве, где хранится бит
        size_t bit   = element & 63; // Номер бита в 64-битном числе

        // Проверяем, установлен ли нужный бит:
        unsigned long long mask = 1ULL << bit;  // Создаём маску для нужного бита
        unsigned long long is_bit_set = set->bits[index] & mask;
        // Проверяем, установлен ли бит:
        if (is_bit_set == 0)
            result = false;// Если не бит установлен, result = false
    
    }

    return result;  // Возвращаем результат
}

// Функция для сравнения множеств
bool compare_sets(BitSet* setA, BitSet* setB) {
    bool result = true; //предположим, что множества равны

    if (setA->size != setB->size) {
        result = false;  // Если размеры не равны, множества разные
    } else {
            size_t capacityBlocks = (setA->capacity + 63) >> 6;
            for (size_t iter = 0; iter < capacityBlocks; iter++) {
                if (setA->bits[iter] != setB->bits[iter]) {
                    result = false; // Если хотя бы один бит не совпадает,
                    break; //то множества разные
                }
            }
    }

    return result;
}

// Функция для проверки, является ли setA подмножеством setB
bool set_is_subset(BitSet* setA, BitSet* setB) {
    bool result = true;  // Изначально предполагаем, что setA является подмножеством setB
    
    size_t capacityWords = (setA->capacity + 63) >> 6;
    for (size_t iter = 0; iter < capacityWords; iter++) {
        if ((setA->bits[iter] & ~setB->bits[iter]) != 0) {
            result = false;  // Если хотя бы один бит из setA не содержится в setB
            break;  // Прерываем цикл, так как подмножество не выполнено
        }
    }
    
    return result;  // Возвращаем результат
}

// Функция для проверки, является ли setA строгим подмножеством setB
bool set_is_strong_subset(BitSet* setA, BitSet* setB) {
    // Проверяем, является ли setA подмножеством setB:
    bool isSubset = set_is_subset(setA, setB); 
    // Проверяем, что размер setA меньше размера setB, 
    // так как равенство множеств не допустимо(дискретная математика):
    bool isSmaller = (setA->size) < (setB->size);  

    bool result;
    // Возвращаем true только если оба условия выполнены:
    if (isSubset && isSmaller) {
        result = true;  // setA является строгим подмножеством setB
    } else {
        result = false; // Либо setA не подмножество setB, 
        //либо его размер не меньше
    }

    return result;
}

// Функция для объединения двух множеств
BitSet get_union_set(BitSet* setA, BitSet* setB) {
    // Создаем новое множество, которое будет объединением двух множеств:
    // сначала находим максимальное капасити:
    size_t maxCapacity = (setA->capacity > setB->capacity) ? 
    setA->capacity : setB->capacity;

    BitSet resultSet = bitset_create(maxCapacity);

    size_t capacityBlocks = (resultSet.capacity + 63) >> 6;
    for (size_t iter = 0; iter < capacityBlocks; iter++) {
        // операция побитового "или", тут применяется 
        // к этим самым блокам(массивам) битов; по 64-бита в 1-блок:
        resultSet.bits[iter] = setA->bits[iter] | setB->bits[iter];
    }

    return resultSet;
}

// Функция для пересечения двух множеств
BitSet get_intersection_set(BitSet* setA, BitSet* setB) {
    // Это другой способ узнать максимальную емкость из обоих множеств
    // Но можно и тернарный оператор использовать:
    BitSet resultSet = bitset_create(max(setA->capacity, setB->capacity));

    size_t capacityWords = (resultSet.capacity + 63) >> 6;
    for (size_t iter = 0; iter < capacityWords; iter++)
        resultSet.bits[iter] = setA->bits[iter] & setB->bits[iter];// побитовое "И"

    return resultSet;
}

// Функция для нахождения разности двух множеств
BitSet get_difference_set(BitSet* setA, BitSet* setB) {
    // Таким образом мы гарантируем, что результирующее множество будет 
    // достаточно большим, чтобы учесть все элементы из обоих множеств:
    BitSet resultSet = bitset_create(max(setA->capacity, setB->capacity));

    size_t capacityWords = (resultSet.capacity + 63) >> 6;
    for (size_t iter = 0; iter < capacityWords; iter++) {
        // Тут мы инвертируем все биты в блоке setB->bits[iter]:
        resultSet.bits[iter] = (setA->bits[iter]) & (~setB->bits[iter]);
        // Операция побитового "И" между блоком из множества setA и инвертированным 
        // блоком из множества setB. Это позволяет сохранить в результирующем 
        // множестве только те биты, которые присутствуют в setA, но отсутствуют в setB.
    }

    return resultSet;
}

// Функция для нахождения симметрической разности двух множеств
BitSet get_symmetric_difference_set(BitSet* setA, BitSet* setB) {
    BitSet resultSet = bitset_create(max(setA->capacity, setB->capacity));

    size_t capacityWords = (resultSet.capacity + 63) >> 6;
    for (size_t iter = 0; iter < capacityWords; iter++) 
        resultSet.bits[iter] = (setA->bits[iter] ^ setB->bits[iter]);// Тут мы используем "исключающее ИЛИ"

    return resultSet;
}

// Функция для нахождения дополнения множества
BitSet get_complement_set(BitSet* setA) {
    BitSet resultSet = bitset_create(setA->capacity);

    size_t capacityWords = (resultSet.capacity + 63) >> 6;
    for (size_t iter = 0; iter < capacityWords; iter++)
        resultSet.bits[iter] = ~setA->bits[iter];
        // Побитовое инвертирование каждого 64-битного блока в множестве
        // Ну или более замороченный способ вводить какой-нибудь универсал 
        // и из него вычитать

    return resultSet;
}

// Деструктор для освобождения памяти
void bitset_destroy(BitSet* set) {
    set->size = 0;
    set->capacity = 0;

    free(set->bits);//Сначала освобождаем память через free
    set->bits = NULL; // Очищаем(затираем) указатель после освобождения 
    // памяти, ни в коме случае не наоборот, иначе произойдет утечка памяти
}