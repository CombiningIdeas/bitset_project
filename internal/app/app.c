#include <stdio.h>

#include "app.h"
#include "../../pkg/services/bitset/bitset.h"
#include "../../pkg/services/output/output.h"

int laboratory_work() {

    const size_t lengthCapacity = 10;
    // Создаем множества с подходящей емкостью:
    BitSet A = bitset_create(lengthCapacity);
    BitSet B = bitset_create(lengthCapacity);
    BitSet C = bitset_create(lengthCapacity);
    BitSet D = bitset_create(lengthCapacity);

    //Создаем массивы для множеств:
    int arrayForSetA[] = {1, 2, 3};
    int arrayForSetB[] = {1, 3, 5};
    int arrayForSetC[] = {1, 2};
    int arrayForSetD[] = {9, 10};

    // Добавляем элементы в множества:
    bitset_add_many(&A, arrayForSetA, 3);
    bitset_add_many(&B, arrayForSetB, 3);
    bitset_add_many(&C, arrayForSetC, 2);
    bitset_add_many(&D, arrayForSetD, 2);
    
    // А теперь поочередно выполним описанные в документации шаги:
    // 1)Операция пересечения
    BitSet intersection_CD = get_intersection_set(&C, &D);

    // 2)Операция симметрической разности
    BitSet symmetric_difference_CD_A = get_symmetric_difference_set(&intersection_CD, &A);
    
    // 3)Операция дополнения
    BitSet complement_CD_A = get_complement_set(&symmetric_difference_CD_A);

    // 4)Операция разности
    BitSet difference_B_intersection_CD = get_difference_set(&B, &intersection_CD);

    // 5)Операция разности
    BitSet difference_B_complement_CD_A = get_difference_set(&B, &complement_CD_A);

    // 6)Операция объединения
    BitSet union_A_difference_B_complement_CD_A = get_union_set(&A, &difference_B_complement_CD_A);

    // 7)Операция объединения - финальная операция:
    BitSet final_result = get_union_set(&union_A_difference_B_complement_CD_A, &difference_B_intersection_CD);

    

    final_result.capacity = lengthCapacity;

    printf("Final result: \n");
    printf("Размер final_result.capacity: %zu\n", final_result.capacity);
    print_set_elements(&final_result, lengthCapacity);



    return 0;
}