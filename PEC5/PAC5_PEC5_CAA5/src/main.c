/*
* File: main.c
* Author: UOC
* Course: 20232
* Description: PAC5-PEC5-CAA5
*/

#include <stdio.h>
#include "restaurant.h"

int main(int argc, char **argv)
{
    tRestaurant rest1;
    tRestaurant rest2;
    tRestaurant bestRestaurant;

    /* Input data */
    printf("INPUT\n");
    printf("RESTAURANT 1\n");
    readRestaurant(&rest1);
    printf("RESTAURANT 2\n");
    readRestaurant(&rest2);

    /* Calculations */
    compareRestaurants(rest1, rest2, &bestRestaurant);

    /* Output data */
    printf("OUTPUT\n");
    printf("THE BEST RESTAURANT IS:\n");
    writeRestaurant(bestRestaurant);

    return 0;
}