#include "calculator.h"

double accumulator = 0.0;
double operand;
char operation;

int main(void) {
    RunCalculator(operation, operand, accumulator);
    return 0;
}
