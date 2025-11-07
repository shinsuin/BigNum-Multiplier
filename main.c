#include <stdio.h>
#include <stdlib.h> // For free()
#include "bignum.h" // Include the custom header

int main() {
    char *num1 = "100000";
    char *num2 = "100000";

    printf("Multiplying %s x %s\n", num1, num2);

    char *decimal_result = big_mult(num1, num2);
    printf("Decimal result: %s\n", decimal_result);

    char *hex_result = decToHex(decimal_result);
    printf("Hexadecimal result: %s\n", hex_result);

    // Free allocated memory
    free(decimal_result);
    free(hex_result);

    return 0;
}