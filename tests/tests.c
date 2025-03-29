#include <assert.h>
#include <time.h>

#include "../pkg/services/bitset/bitset.h"

// Макрос assert помогает автоматически завершать программу с сообщением об 
// ошибке, если указанное условие оказывается ложным.

// Тестирование добавления множества значений 
// не имеет смысла так как та функция, которая это делает вызывает через цикл ту 
// функцию которая добавляет 1 значение

// Тестирование добавления 1 значения
void test_add() {
    const size_t length = 100;

    // Создаем новый экземпляр структуры с заданным capacity
    BitSet set = bitset_create(length);
    
    // Добавляем несколько элементов в множество
    bitset_add(&set, 0);   // Добавляем элемент 0
    bitset_add(&set, 25);  // Добавляем элемент 25
    bitset_add(&set, 55);  // Добавляем элемент 55
    bitset_add(&set, 99);  // Добавляем элемент 64

    // Проверяем, что элементы были добавлены в множество
    assert(bitset_contains(&set, 99) && "Ошибка: 64 не найден");
    assert(bitset_contains(&set, 55) && "Ошибка: 55 не найден");
    assert(bitset_contains(&set, 25) && "Ошибка: 25 не найден");
    assert(bitset_contains(&set, 0) && "Ошибка: 0 не найден");

    // Очистка памяти, связанной с множеством, после завершения теста
    bitset_destroy(&set);
}

// Тестирование удаления 1 значения
void test_remove() {
    const size_t length = 1000;
    
    //  Создаем новый экземпляр структуры с заданным capacity
    BitSet workSet = bitset_create(length);

    // Добавляем некоторые элементы в множество
    bitset_add(&workSet, 15); // Добавляем элемент 15
    bitset_add(&workSet, 10); // Добавляем элемент 10

    // Удаляем один элемент
    bitset_remove(&workSet, 15);

    // Проверяем, что размер множества изменился корректно
    assert(workSet.size == 1 && 
        "Неправильный размер множества после удаления");

    // Проверяем, что элемент 15 был удалён
    assert(!bitset_contains(&workSet, 15) && 
        "Элемент 15 не был удалён");

    // Проверяем, что элемент 10 остался в множестве
    assert(bitset_contains(&workSet, 10) && 
        "Элемент 10 был удалён, хотя не должен был");

    // Удаляем элемент 10
    bitset_remove(&workSet, 10);

    // Проверяем, что после удаления множества размер стал 0
    assert(workSet.size == 0 && 
        "Неправильный размер множества после удаления всех элементов");
    
    // Проверяем, что элемент 10 был удалён
    assert(!bitset_contains(&workSet, 10) && 
        "Элемент 10 не был удалён");

    // Освобождаем память
    bitset_destroy(&workSet);
}

// Тестирование функции является ли множество A подмножеством множества B
void test_is_subset() {
    size_t lengthSetA = 500;
    size_t lengthSetB = 750;

    // Тест #1: Проверка, что множество A является подмножеством множества B, 
    // при абсолютно одинаковых элементах в обоих множествах
    {
        // Создаем два множества
        BitSet setA = bitset_create(lengthSetA);
        BitSet setB = bitset_create(lengthSetB);

        // Добавляем одинаковые значения в оба множества
        int arrayForSets[] = {0, 5, 1, 55, 20, 30, 400, 8, 9, 10};

        bitset_add_many(&setA, arrayForSets, 10);
        bitset_add_many(&setB, arrayForSets, 10);

        // Проверяем, что множество A является подмножеством множества B
        assert(set_is_subset(&setA, &setB) && 
            "Множество не является подмножеством");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
    }

    // Тест #2: Проверка, что множество A не является подмножеством множества B, 
    // при абсолютно разных элементах в обоих множествах
    {
        // Создаем два множества
        BitSet setA = bitset_create(lengthSetA);
        BitSet setB = bitset_create(lengthSetB);
        
        // Добавляем различные значения в множества
        int arrayForSetA[] = {3, 5, 9, 15, 50, 100};
        int arrayForSetB[] = {0, 1, 2, 5, 15, 50, 60, 80, 100, 200};

        bitset_add_many(&setA, arrayForSetA, 6);
        bitset_add_many(&setB, arrayForSetB, 10);

        // Проверяем, что множество A не является подмножеством множества B
        assert(!set_is_subset(&setA, &setB) && 
            "Множество является подмножеством");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
    }
}

// тестирование функции является ли множество множество А строгим подмножеством В(строгое включение)
void test_strong_subset() {
    size_t lengthSetA = 500;
    size_t lengthSetB = 750;

    // Тест #1: Проверка, является ли множество A строгим подмножеством 
    // множества B, при абсолютно одинаковых элементах в обоих множествах
    {
        BitSet setA = bitset_create(lengthSetA);
        BitSet setB = bitset_create(lengthSetB);

        int arrayForSets[] = {0, 5, 1, 55, 20, 30, 400, 8, 9, 10};

        bitset_add_many(&setA, arrayForSets, 10);
        bitset_add_many(&setB, arrayForSets, 10);
        
        assert(!set_is_strong_subset(&setA, &setB) && 
            "Множество не является строгим подмножеством");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
    }

    // Тест #2: Проверка, является ли множество A строгим подмножеством 
    // множества B, при частично одинаковых элементах в обоих множествахх
    {
        BitSet setA = bitset_create(lengthSetA);
        BitSet setB = bitset_create(lengthSetB);

        int arrayForSetA[] = {3, 5, 9, 15, 50, 100};
        int arrayForSetB[] = {0, 1, 2, 3, 15, 50, 9, 5, 100, 200};

        bitset_add_many(&setA, arrayForSetA, 6);
        bitset_add_many(&setB, arrayForSetB, 10);

        assert(set_is_strong_subset(&setA, &setB) && 
            "Множество не является строгим подмножеством");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
    }
}

// тестирование функции по объединению
void test_union_set() {
    const size_t length = 500;

    // Тест #1: Проверка объединения двух множеств с одинаковыми значениями
    {
        BitSet setA = bitset_create(length);
        BitSet setB = bitset_create(length);
        BitSet resultSet = bitset_create(length);
        
        int arrayForSet[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
             10, 11, 12, 13, 14, 15};

        bitset_add_many(&setA, arrayForSet, 16);
        bitset_add_many(&setB, arrayForSet, 16);
        bitset_add_many(&resultSet, arrayForSet, 16);

        BitSet result = get_union_set(&setA, &setB);

        // Проверяем корректность объединения
        assert(compare_sets(&result, &resultSet) &&
            "Объединение множеств некорректно");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }

    // Тест #2: Проверка объединения с непересекающимися множествами
    {
        BitSet setA = bitset_create(length);
        BitSet setB = bitset_create(length);
        BitSet resultSet = bitset_create(length);

        // Заполняем первое множество разными значениями:
        int arrayForSetA[]     = {1, 5, 10, 33, 44, 66, 77, 99, 101};
        // Заполняем второе множество немного другими и теми же значениями:
        int arrayForSetB[]     = {1, 3, 54, 30};
        // объединение множеств должно содержать все элементы обоих множеств:
        int arrayForUnionSet[] = {1, 5, 10, 33, 44, 66, 77, 99, 101, 3, 54, 30};

        bitset_add_many(&setA, arrayForSetA, 9);
        bitset_add_many(&setB, arrayForSetB, 4);
        bitset_add_many(&resultSet, arrayForUnionSet, 12);

        BitSet result = get_union_set(&setA, &setB);

        // Проверяем корректность объединения
        assert(compare_sets(&result, &resultSet) &&
            "Объединение множеств некорректно");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }
}

// тестирование функции по пересечению
void test_intersection_set() {
    const size_t length = 500; 

    // Тест #1: Проверка пересечения двух одинаковых множеств
    {
        BitSet setA = bitset_create(length); // Создаем первое множество
        BitSet setB = bitset_create(length); // Создаем второе множество
        BitSet resultSet = bitset_create(length); // Множество, которое будет хранить результат пересечения
        
        // Заполняем оба множества одинаковыми значениями
        int arrayForSet[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
            10, 11, 12, 13, 14, 15};
        
        bitset_add_many(&setA, arrayForSet, 16);
        bitset_add_many(&setB, arrayForSet, 16);
        bitset_add_many(&resultSet, arrayForSet, 16);

        // Пересечение множеств setA и setB должно быть равно самому множеству setA (и setB)
        BitSet result = get_intersection_set(&setA, &setB);

        // Проверяем, что пересечение корректное
        assert(compare_sets(&result, &resultSet) && 
            "Пересечение множеств некорректно");

        // Очищаем память 
        bitset_destroy(&setA);
        bitset_destroy(&setB);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }

    // Тест #2: Проверка пересечения множеств с частично общими элементами
    {
        BitSet setA = bitset_create(length); // Создаем первое множество
        BitSet setB = bitset_create(length); // Создаем второе множество
        BitSet resultSet = bitset_create(length); // Множество, которое будет хранить результат пересечения

        // Заполняем первое множество
        int arrayForSetA[] = {0, 1, 2, 11, 32, 39, 49, 88, 66, 90};
        // Заполняем второе множество
        int arrayForSetB[] = {0, 1, 58, 5, 100};
        // Пересечение должно содержать только общие элементы двух множеств:
        int arrayForIntersectionSet[] = {0, 1};

        bitset_add_many(&setA, arrayForSetA, 10);
        bitset_add_many(&setB, arrayForSetB, 5);
        bitset_add_many(&resultSet, arrayForIntersectionSet, 2);

        // Пересечение множеств setA и setB должно быть из 0 и 1
        BitSet result = get_intersection_set(&setA, &setB);

        // Проверяем, что пересечение корректное
        assert(compare_sets(&result, &resultSet) && 
            "Пересечение множеств некорректно");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }
}

// тестирование функции, отвечающей за разность множеств
void test_difference_set() {
    const size_t length = 500; 

    // Тест #1: Разность двух множеств с пересекающимися элементами
    {
        BitSet setA = bitset_create(length); // Создаем первое множество
        BitSet setB = bitset_create(length); // Создаем второе множество
        BitSet resultSet = bitset_create(length); // Множество для ожидаемого результата

        // Заполняем первое множество 
        int values1[] = {0, 1, 2, 3, 4, 5, 6, 7, 90};
        // Заполняем второе множество 
        int values2[] = {4, 5, 6, 7, 8, 9, 10, 100, 50};
        // Разность множеств А - В должна содержать: 0, 1, 2, 3, 90;
        int arrayForSymmetricDifferenceSet[] = {0, 1, 2, 3};

        bitset_add_many(&setA, values1, 9);
        bitset_add_many(&setB, values2, 9);
        bitset_add_many(&resultSet, arrayForSymmetricDifferenceSet, 5); // Заполняем ожидаемый результат

        // Получаем разность множеств setA - setB
        BitSet result = get_difference_set(&setA, &setB);

        // Проверяем, что разность корректна
        assert(compare_sets(&resultSet, &result) && 
            "Разность множеств некорректна");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }

    // Тест #2: Разность двух одинаковых множеств
    {
        BitSet setA = bitset_create(length); // Создаем первое множество
        BitSet setB = bitset_create(length); // Создаем второе множество
        BitSet resultSet = bitset_create(length); // Множество для ожидаемого результата

        // Заполняем оба множества
        int values1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int values2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        // Ожидаем, что разность будет пустым множеством, так как множества одинаковы
        int arrayForDifferenceSet[] = {};

        bitset_add_many(&setA, values1, 10);
        bitset_add_many(&setB, values2, 10);
        bitset_add_many(&resultSet, arrayForDifferenceSet, 0); 

        // Получаем разность множеств А и В
        BitSet result = get_difference_set(&setA, &setB);

        // Проверяем, что разность корректна (должна быть пустой)
        assert(compare_sets(&result, &resultSet) && 
            "Разность множеств некорректна");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }
}

// тестирование функции, отвечающей за симетрическую разность множеств
void test_symmetric_difference_set() {
    const size_t length = 500;

    // Тест #1: Симметричная разность двух множеств с несколькими общими элементами
    {
        BitSet setA = bitset_create(length); // Создаем первое множество
        BitSet setB = bitset_create(length); // Создаем второе множество
        BitSet resultSet = bitset_create(length); // Множество для ожидаемого результата

        // Заполняем первое множество 
        int values1[] = {11, 0, 1, 23, 54, 65, 12, 76};
        // Заполняем второе множество 
        int values2[] = {17, 21, 23, 54, 65, 12, 76, 60};
        // Получение симметрической разности: элементы, которые есть в одном из множеств, но не в обоих
        int arrayForSymmetricDifferenceSet[] = {0, 1, 11, 17, 21, 60};

        bitset_add_many(&setA, values1, 8);
        bitset_add_many(&setB, values2, 8); 
        bitset_add_many(&resultSet, arrayForSymmetricDifferenceSet, 6); 

        // Получаем симметричную разность множеств A и B
        BitSet result = get_symmetric_difference_set(&setA, &setB);

        // Проверяем, что симметричная разность корректна:
        assert(compare_sets(&result, &resultSet) && 
            "Симметричная разность множеств некорректна");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }

    // Тест #2: Симметричная разность двух одинаковых множеств
    {
        BitSet setA = bitset_create(length); // Создаем первое множество
        BitSet setB = bitset_create(length); // Создаем второе множество
        BitSet resultSet = bitset_create(length); // Множество для ожидаемого результата

        // Заполняем оба множества одинаковыми значениями
        int values1[] = {0, 33, 23, 54, 65, 12, 76, 43, 38, 84};
        int values2[] = {0, 33, 23, 54, 65, 12, 76, 43, 38, 84};
        // Ожидаем, что разность будет пустым множеством, так как множества одинаковы
        int arrayForSymmetricDifferenceSet[0] = {};

        bitset_add_many(&setA, values1, 10);
        bitset_add_many(&setB, values2, 10); 
        bitset_add_many(&resultSet, arrayForSymmetricDifferenceSet, 0);

        // Получаем симметричную разность множеств setA и setB
        BitSet result = get_symmetric_difference_set(&setA, &setB);

        // Проверяем, что симметричная разность корректна, она должна быть пустой:
        assert(compare_sets(&result, &resultSet) && 
            "Симметричная разность множеств некорректна");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&setB);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }
}

//Тестирование функции, отвечающей за дополнение множества
void test_complement_set() {
    const size_t length = 500;

    // Тест 1: Дополнение множества с несколькими элементами:
    {
        BitSet setA = bitset_create(length); // Создаем множество setA
        BitSet resultSet = bitset_create(length); // Множество для ожидаемого результата

        // Заполняем множество:
        int arrayForSetA[] = {1, 9, 19, 4, 3, 175, 212, 455};

        // Тут у нас создается универсальное множество:
        int arrayForComplementSet[length];
        int counterLength = 0;
        for (int iter = 0; iter < (int)length; iter++) {
            bool tmpResult = true;

            for (int counterForSetA = 0; counterForSetA < 8; counterForSetA++)
                if (iter == arrayForSetA[counterForSetA])
                    tmpResult = false;

            if (tmpResult) {
                arrayForComplementSet[counterLength] = iter;
                counterLength++;
            }
        }
        
        
        // Заполняем множество A:
        bitset_add_many(&setA, arrayForSetA, 8); 
        // Заполняем разность универсального множества и множества А:
        bitset_add_many(&resultSet, arrayForComplementSet, length - 8); 

        // Получаем дополнение множества A:
        BitSet result = get_complement_set(&setA);

        // Проверяем, что дополнение корректно
        assert(compare_sets(&result, &resultSet) && 
            "Дополнение множества некорректно");

        // Очищаем память
        bitset_destroy(&setA);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }

    // Тест 2: Дополнение пустого множества (должно быть полное множество)
    {
        BitSet setA = bitset_create(length); // Создаем пустое множество
        BitSet resultSet = bitset_create(length); // Множество для ожидаемого результата

        // Заполняем множество:
        int arrayForSetA[] = {};

        // Тут у нас создается универсальное множество:
        int arrayForComplementSet[length];
        int counterLength = 0;
        for (int iter = 0; iter < (int)length; iter++) {
            bool tmpResult = true;

            for (int counterForSetA = 0; counterForSetA < 8; counterForSetA++)
                if (iter == arrayForSetA[counterForSetA])
                    tmpResult = false;

            if (tmpResult) {
                arrayForComplementSet[counterLength] = iter;
                counterLength++;
            }
        }

        // Так как множество А пустое, то мы его не заполняем
        // Заполняем универсальное множество
        bitset_add_many(&resultSet, arrayForComplementSet, length); 

        // Получаем дополнение пустого множества
        BitSet result = get_complement_set(&setA);

        // Проверяем, что результат — это полное множество
        assert(compare_sets(&result, &resultSet) && 
            "Дополнение пустого множества некорректно");

        // Очищаем память после теста
        bitset_destroy(&setA);
        bitset_destroy(&result);
        bitset_destroy(&resultSet);
    }
}


int main() {
    test_add();
    test_remove();
    test_is_subset();
    test_strong_subset();
    test_union_set();
    test_intersection_set();
    test_difference_set();
    test_symmetric_difference_set();
    test_complement_set();

    printf("Тестирование написанных функций успешно пройдено.\n");

    return 0;
}