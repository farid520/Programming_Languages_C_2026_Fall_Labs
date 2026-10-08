/*
 * week4_1_dynamic_array.c
 * Author: Farid Hajiyev
 * Student ID: 251ADB190
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr = NULL;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    // TODO: Allocate memory for n integers using malloc
    // Example: arr = malloc(n * sizeof(int));
    arr = (int *)malloc((size_t)n * sizeof(int));

    // TODO: Check allocation success
    // If arr is NULL: print "Memory allocation failed." and return 1
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // TODO: Print the prompt "Enter %d integers: " (with n), then read
    //       n integers into the array.
    //       If a value cannot be read: print "Invalid input.",
    //       free the array and return 1
    printf("Enter %d integers: ", n);
    int *cursor = arr;
    for (int count = 0; count < n; count++, cursor++) {
        if (scanf("%d", cursor) != 1) {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    // TODO: Compute the sum and the average (use floating point for the average)
    long long total = 0;
    for (int k = 0; k < n; k++) {
        total += arr[k];
    }
    double mean = (double)total / (double)n;

    // TODO: Print the results exactly as:
    //       Sum = <sum>
    //       Average = <average with 2 decimals, %.2f>
    printf("Sum = %lld\n", total);
    printf("Average = %.2f\n", mean);

    // TODO: Free allocated memory
    free(arr);

    return 0;
}