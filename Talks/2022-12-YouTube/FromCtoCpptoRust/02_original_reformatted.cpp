// https://godbolt.org/z/EvW9E48Pj
// 102 instructions using gcc 12.2 and -O3
// 29  instructions using gcc 12.2 and -O2

#include "stdio.h"

int calculate(int bottom, int top) {
    if (top > bottom) {
        int sum = 0;
        for (int number = bottom; number <= top; number++) {
            if (number % 2 == 0) {
                sum += number;
            }
        }
        return sum;
    } else {
        return 0;
    }
}

int main()
{
    printf("%i\n", calculate(5, 12)); // 36
    printf("%i\n", calculate(5, 3));  // 0
    return 0;
}
