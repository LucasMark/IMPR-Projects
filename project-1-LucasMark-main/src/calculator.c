#include "calculator.h"
#include "stdio.h"
#include "math.h"

//This runs the calculator, first asking the use what operation should be run, and then for an operand if needed
//Afterwords the operation is run and the result printed out
void RunCalculator(char operation, double operand, double accumulator){
    printf("Choose a type of operation and an operand: \n"
           "Addition: + \n"
           "Subtraction: - \n"
           "Multiplication: * \n"
           "Division: / \n"
           "Power of: ^ \n"
           "Square root: # \n"
           "Inversion: % \n"
           "Divide by one: ! \n"
           "Show accumulator: a \n"
           "Quit: q \n");
    do {
        ScanData(&operation, &operand);
        do_next_op(operation, operand, &accumulator);
    } while (operation != 'q');
    printf("Quitting!");
}

//This function decides what operation is done and if an operand is needed
void ScanData(char* operation, double* operand) {
    scanf(" %c", operation);
    if (*operation == '#' || *operation == '!' || *operation == '%' || *operation == 'a')
        return;
    else if (*operation == '+' || *operation == '-' || *operation == '*' || *operation == '^' || *operation == '/') {
        scanf(" %lf", operand);
        return;
    }
}

void Addition(double operand, double* accumulator){
    *accumulator = *accumulator + operand;
    printf("%lf \n", *accumulator);
}

void Subtraction(double operand, double* accumulator){
    *accumulator = *accumulator - operand;
    printf("%lf \n", *accumulator);
}

void Multiplication(double operand, double* accumulator){
    *accumulator = *accumulator * operand;
    printf("%lf \n", *accumulator);
}

void Division(double operand, double* accumulator){
    if(operand != 0){
        *accumulator = *accumulator / operand;
        printf("%lf \n", *accumulator);
    }
    else{
        printf("Cannot divide by zero! \n");
    }
}

void PowerOf(double operand, double* accumulator){
    *accumulator = pow(*accumulator, operand);
    printf("%lf \n", *accumulator);
}

void SquareRoot(double* accumulator){

    if(*accumulator >= 0){
        *accumulator = sqrt(*accumulator);
        printf("%lf \n", *accumulator);
    }
    else{
        printf("Cannot take square of a negative value! \n");
    }
}

void Inversion(double* accumulator){
    *accumulator = -*accumulator;
    printf("%lf \n", *accumulator);
}

void DivideByOne(double* accumulator){
    if(*accumulator != 0){
        *accumulator = 1 / *accumulator;
        printf("%lf \n", *accumulator);
    }
    else{
        printf("Cannot divide by zero! \n");
    }
}

//This function selects which mathematical operation should be run based on the output from ScanData
void do_next_op(char operation, double operand, double* accumulator){
    switch(operation){
        case '+':
            Addition(operand, accumulator);
            break;
        case '-':
            Subtraction(operand, accumulator);
            break;
        case '*':
            Multiplication(operand, accumulator);
            break;
        case '/':
            Division(operand, accumulator);
            break;
        case '^':
            PowerOf(operand, accumulator);
            break;
        case '#':
            SquareRoot(accumulator);
            break;
        case '%':
            Inversion(accumulator);
            break;
        case '!':
            DivideByOne(accumulator);
            break;
        case 'a':
            printf("%lf  \n", *accumulator);
        default:
            printf("Invalid operation  \n");
    }
}