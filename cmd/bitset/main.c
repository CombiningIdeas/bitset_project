#include <stdio.h>
#include "../../internal/app/app.h"

int main() {
    int result = laboratory_work();

    if (result == 0)
        printf("Лабараторная работа успешно отработала! \n");
    else
        printf("Лабараторная работа не отработала успешно... \n");

    return 0;
}