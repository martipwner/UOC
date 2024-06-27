/*
* File: restaurant.h
* Author: UOC
* Course: 20232
* Description: PAC5-PEC5-CAA5
*/

#include <stdio.h>

#define MAX_NAME 12+1

typedef struct {
    char name[MAX_NAME];
    float priceMenu;
    int michelinStars;
    float score;
} tRestaurant;

/* Predeclaracions */
void readRestaurant(tRestaurant *rest);
void writeRestaurant(tRestaurant rest);
void copyRestaurant(tRestaurant *dstRest, tRestaurant srcRest);
void compareRestaurants(tRestaurant rest1, tRestaurant rest2, tRestaurant *bestRest);