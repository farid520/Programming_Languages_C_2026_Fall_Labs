#include <stdio.h>

/*
    Task:
    Write a function `long long factorial(int n)` that computes n!
    using a loop (not recursion).

    In main():
      - Ask user for an integer n
      - If n is negative, print an error and exit
      - Otherwise, call factorial and print the result
*/

long long factorial(int n) {
    // TODO: compute factorial iteratively
      long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result; // placeholder
}

int main(void) {
    int n;

    printf("Enter a non-negative integer n: ");
    scanf("%d", &n);
if (n < 0) {
        printf("Error: n must be greater than or equal to 0.\n");
        return 1;
    }
 
    long long result = factorial(n);
    printf("%d! = %lld\n", n, result);
 
    // TODO: validate input, call function, print result

    return 0;
}
