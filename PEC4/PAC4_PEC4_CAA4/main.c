/*
* File: main.c
* Author: UOC
* Course: 20232
* Description: PAC4-PEC4-CAA4
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 15+1

typedef struct {
    char name[MAX_NAME];
    float distance;
    int cumulativeElevationDifference;
} tRoute;

int main(int argc, char **argv)
{
    /* Definition of variables */
    tRoute route1;
    tRoute route2;
    char hardestRouteName[MAX_NAME];

    /* Input data */
    printf("INPUT\n");
    
    /* Route 1 */
    printf("ROUTE 1\n");
    printf("NAME?\n");
    scanf("%s", route1.name);
    printf("DISTANCE?\n");
    scanf("%f", &route1.distance);
    printf("CUMULATIVE ELEVATION DIFFERENCE?\n");
    scanf("%d", &route1.cumulativeElevationDifference);
    
    /* Route 2 */
    printf("ROUTE 2\n");
    printf("NAME?\n");
    scanf("%s", route2.name);
    printf("DISTANCE?\n");
    scanf("%f", &route2.distance);
    printf("CUMULATIVE ELEVATION DIFFERENCE?\n");
    scanf("%d", &route2.cumulativeElevationDifference);
        
    /* Calculations */
    if (route1.distance > route2.distance) {
        strcpy(hardestRouteName, route1.name);
    } else {
        if (route1.distance < route2.distance) {
            strcpy(hardestRouteName, route2.name);
        } else {
            if (route1.cumulativeElevationDifference > route2.cumulativeElevationDifference) {
                strcpy(hardestRouteName, route1.name);
            } else {
                strcpy(hardestRouteName, route2.name);
            }
        }
    }

    /* Output results */
    printf("OUTPUT\n");
    printf("THE HARDEST ROUTE IS %s\n", hardestRouteName);
    return 0;
}