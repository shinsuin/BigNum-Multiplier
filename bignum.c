#include "bignum.h"
#include <stdio.h>
#include <string.h>

// Helper function to reverse a string - static
static void reverse(char *str) {
    if (!str) return;
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Function to add two big numbers represented as strings - static
static char* big_add(const char *num1, const char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = (len1 > len2) ? len1 : len2;
    char *result = (char *)malloc(maxLen + 2);
    int carry = 0, i = len1 - 1, j = len2 - 1, k = 0;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';
        result[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }
    result[k] = '\0';
    reverse(result);
    return result;
}

// Function to multiply a big number (string) by a single digit (int) - static
static char* multiply_by_digit(const char *num, int digit) {
    if (digit == 0) {
        char* result = malloc(2);
        strcpy(result, "0");
        return result;
    }
    int len = strlen(num);
    char *result = (char *)malloc(len + 2);
    int carry = 0, i = len - 1, k = 0;

    while (i >= 0 || carry) {
        int mul = carry;
        if (i >= 0) mul += (num[i--] - '0') * digit;
        result[k++] = (mul % 10) + '0';
        carry = mul / 10;
    }
    result[k] = '\0';
    reverse(result);
    return result;
}

// Function to divide a large decimal string by an integer - static
static char* divide_string(const char* number, int divisor, int* rem) {
    char* quotient = (char*)malloc(strlen(number) + 1);
    int idx = 0;
    long long temp = 0;
    
    for (int i = 0; i < strlen(number); i++) {
        temp = temp * 10 + (number[i] - '0');
        if (temp >= divisor) {
            quotient[idx++] = (temp / divisor) + '0';
            temp = temp % divisor;
        } else if (idx > 0) {
            quotient[idx++] = '0';
        }
    }
    quotient[idx] = '\0';
    *rem = temp;

    if (strlen(quotient) == 0) {
        free(quotient);
        char* zero_str = malloc(2);
        strcpy(zero_str, "0");
        return zero_str;
    }
    return quotient;
}

// Public function implementations
char* big_mult(const char *num1, const char *num2) {
    if (strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0) {
        char* result = malloc(2);
        strcpy(result, "0");
        return result;
    }

    int len2 = strlen(num2);
    char *total_sum = malloc(2);
    strcpy(total_sum, "0");

    for (int i = len2 - 1; i >= 0; i--) {
        int digit = num2[i] - '0';
        if (digit == 0) continue;

        char *partial_product = multiply_by_digit(num1, digit);
        
        int zeros_to_add = len2 - 1 - i;
        int partial_len = strlen(partial_product);
        char *shifted_product = (char *)malloc(partial_len + zeros_to_add + 1);
        strcpy(shifted_product, partial_product);
        for (int j = 0; j < zeros_to_add; j++) {
            shifted_product[partial_len + j] = '0';
        }
        shifted_product[partial_len + zeros_to_add] = '\0';
        
        char *temp_sum = big_add(total_sum, shifted_product);
        free(total_sum);
        total_sum = temp_sum;

        free(shifted_product);
        free(partial_product);
    }
    return total_sum;
}

char* decToHex(char* dec) {
    char* hex = (char*)malloc(strlen(dec) + 1); 
    int hex_idx = 0;
    char hex_chars[] = "0123456789ABCDEF";
    char* current_dec = strdup(dec);

    if (strcmp(current_dec, "0") == 0) {
        strcpy(hex, "0");
        free(current_dec);
        return hex;
    }

    while(strcmp(current_dec, "0") != 0) {
        int remainder = 0;
        char* next_dec = divide_string(current_dec, 16, &remainder);
        hex[hex_idx++] = hex_chars[remainder];
        free(current_dec);
        current_dec = next_dec;
    }
    hex[hex_idx] = '\0';
    reverse(hex);
    free(current_dec);
    return hex;
}
