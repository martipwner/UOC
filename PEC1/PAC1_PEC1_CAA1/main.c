/*
* File: main.c
* Author: UOC
* Course: 20232
* Description: PAC1-PEC1-CAA1
*/

/* System header files */
#include <stdio.h>

/* Main function */
int main(int argc, char **argv) {

    /* Definition of variables */
    float celsius;
    float fahrenheit;
   
    /* Input data */
    printf("INPUT\n");
    printf("CELSIUS DEGREES?\n");
    scanf("%f", &celsius);

    /* Calculations */      
    fahrenheit = (9.0/5.0) * celsius + 32.0;

    /* Output results */
    printf("OUTPUT\n");
    printf("FAHRENHEIT DEGREES: %.2f\n", fahrenheit);
    
    return 0;
}