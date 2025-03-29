# Компилятор:
CC = gcc

#Фалги компиляции:
CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG


# Объектные файлы(.о-файлы)
OBJ_MAIN = internal/app/app.o pkg/services/bitset/bitset.o pkg/services/output/output.o cmd/bitset/main.o
OBJ_TEST = pkg/services/bitset/bitset.o pkg/services/output/output.o tests/tests.o


# Имена для финальных исполняемых файлов
TARGET = build/package/bitset_main
TEST_TARGET = build/tests/bitset_tests

# Компиляция  main-исполняемого файла:
$(TARGET): $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_MAIN) -o $(TARGET)

# Компиляция tests-исполняемого файла:
$(TEST_TARGET): $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJ_TEST) -o $(TEST_TARGET) 




# Правила компиляции каждого .c-файла в .o-файл
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



# Очистка
clean:
	rm -f $(OBJ_MAIN) $(OBJ_TEST)

all-clean:
	rm -f $(OBJ_MAIN) $(OBJ_TEST) $(TARGET) $(TEST_TARGET)

# Перекомпиляция
rebuild: 
	clean $(TARGET) $(TEST_TARGET)

