/*
* File: restaurant.c
* Author: UOC
* Course: 20232
* Description: PAC5-PEC5-CAA5
*/

#include <stdio.h>
#include <string.h>
#include "restaurant.h"

void readRestaurant(tRestaurant *rest) {
    printf("NAME?\n");
    scanf("%s", rest->name);
    printf("PRICE MENU?\n");
    scanf("%f", &rest->priceMenu);
    printf("MICHELIN STARS?\n");
    scanf("%d", &rest->michelinStars);
    rest->score = rest->priceMenu / (float)(rest->michelinStars + 2);
}

void writeRestaurant(tRestaurant rest) {
    printf("NAME: %s\n", rest.name);
    printf("PRICE MENU: %.2f\n", rest.priceMenu);
    printf("MICHELIN STARS: %d\n", rest.michelinStars);
    printf("SCORE: %.2f\n", rest.score);
}

void compareRestaurants(tRestaurant rest1, tRestaurant rest2, tRestaurant *bestRest) {
    if (rest1.score < rest2.score) {
        copyRestaurant(bestRest, rest1);
    } else {
        copyRestaurant(bestRest, rest2);
    }
}

void copyRestaurant(tRestaurant *dstRest, tRestaurant srcRest) {
    strcpy(dstRest->name, srcRest.name);
    dstRest->michelinStars = srcRest.michelinStars;
    dstRest->priceMenu = srcRest.priceMenu;
    dstRest->score = srcRest.score;
}