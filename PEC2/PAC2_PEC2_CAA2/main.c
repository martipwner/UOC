/*
* File: main.c
* Author: UOC
* Course: 20232
* Description: PAC2-PEC2-CAA2
*/

/* System header files */
#include <stdio.h>
#include <stdbool.h>

#define TOTAL_FIREFIGHTERS 12
#define MIN_PCT_FIREFIGHTERS 25  /* Minimum percentage of firefighters for support */ 

typedef enum {TRAFFIC_ACCIDENT, FIRE_HOUSE, OTHERS} tAlarmType;

int main(int argc, char **argv)
{
    /* Definition of variables */
    tAlarmType alarmType;
    int numVictims;
    int numFirefighters;
    bool isAlarmAttended;
    
    /* Input data */
    printf("INPUT\n");
    printf("ALARM TYPE (0-TRAFFIC ACCIDENT, 1-FIRE HOUSE, 2-OTHERS)?\n");
    scanf("%u", &alarmType);
    printf("NUMBER OF VICTIMS?\n");
    scanf("%d", &numVictims);
    printf("NUMBER OF FIREFIGHTERS REQUIRED?\n");
    scanf("%d", &numFirefighters);  
    
    /* Expresions */
    isAlarmAttended = (alarmType == FIRE_HOUSE || alarmType == TRAFFIC_ACCIDENT) 
        && TOTAL_FIREFIGHTERS - numFirefighters >= TOTAL_FIREFIGHTERS * MIN_PCT_FIREFIGHTERS / 100
        && numVictims > 0 && numFirefighters > 0;
    
    /* Output results */
    printf("OUTPUT\n");
    printf("THE ALARM IS ATTENDED (0-FALSE, 1-TRUE): %d\n", isAlarmAttended);
    
    return 0;
}
