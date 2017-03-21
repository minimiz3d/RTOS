#include "RTA.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int max;
    printf("Número máximo do intervalo: ");
    scanf("%d", &max);

    int result = randomNumber(max);
    printf("Número gerado, entre 1 e %d, foi: %d\n", max,result);

    return 0;
}
