/*
* File: main.c
* Author: UOC
* Course: 20232
* Description: PAC3-PEC3-CAA3
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_ELEMS 3

int main(int argc, char **argv)
{
    /* Definition of variables */
    int magicSquare[MAX_ELEMS][MAX_ELEMS];
    int magicConstant;
    bool isMagicSquare;
    bool isMagicDiagonals;
    
    /* Initialization of variables */
    isMagicSquare = false;
    isMagicDiagonals = false;
    
    /* Input data */
    printf("INPUT\n");
    printf("SQUARE(0,0)?\n");
    scanf("%d", &magicSquare[0][0]);
    printf("SQUARE(1,0)?\n");
    scanf("%d", &magicSquare[1][0]);
    printf("SQUARE(2,0)?\n");
    scanf("%d", &magicSquare[2][0]); 
    printf("SQUARE(2,1)?\n");
    scanf("%d", &magicSquare[2][1]);
    printf("SQUARE(1,1)?\n");
    scanf("%d", &magicSquare[1][1]);    
    printf("SQUARE(0,1)?\n");
    scanf("%d", &magicSquare[0][1]);
    printf("SQUARE(0,2)?\n");
    scanf("%d", &magicSquare[0][2]);
    printf("SQUARE(1,2)?\n");
    scanf("%d", &magicSquare[1][2]);
    printf("SQUARE(2,2)?\n");
    scanf("%d", &magicSquare[2][2]);
    
    /* Calculations */ 
    magicConstant = magicSquare[0][0]+magicSquare[0][1]+magicSquare[0][2];
    
    /* First, we check that the sum of columns and rows have the same result */
    if (magicConstant == magicSquare[1][0] + magicSquare[1][1] + magicSquare[1][2] 
        && magicConstant == magicSquare[2][0] + magicSquare[2][1] + magicSquare[2][2] 
        && magicConstant == magicSquare[0][0] + magicSquare[1][0] + magicSquare[2][0]
        && magicConstant == magicSquare[0][1] + magicSquare[1][1] + magicSquare[2][1]
        && magicConstant == magicSquare[0][2] + magicSquare[1][2] + magicSquare[2][2]) {
        
        isMagicSquare = true;
        
        /* Then, we check if diagonals have the same result too */
        if (magicConstant == magicSquare[0][0] + magicSquare[1][1] + magicSquare[2][2]
            && magicConstant == magicSquare[0][2] + magicSquare[1][1] + magicSquare[2][0]) {
                
            isMagicDiagonals = true;   
        }
    } 
    
    /* Output results */
    printf("OUTPUT\n");
    /* The output is based on the results obtained previously */
    if (isMagicSquare) {
        if (isMagicDiagonals) {
            printf("It is a magic square and its magic constant is %d\n", magicConstant);
        } else {
            printf("It is not a magic square because of the diagonals\n");
        }
    } else {
        printf("It is not a magic square\n");
    }
    
    return 0;
}