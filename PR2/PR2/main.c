/*
* File: main.c
* Author: UOC
* Course: 20232
* Description: PR2
*/

/* System header files */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LENGTH 15+1

/* User defined types */
typedef enum {TRANSPORT=1, FIGHTER, MEDICAL, EXPLORER} tShipType;

typedef struct {    
    char name[MAX_NAME_LENGTH]; /* Ship name */
    tShipType shipType;         /* Ship type */
	bool isInterplanetary;      /* Interplanetary capabilities */
	float autonomy;             /* Autonomy, max range */
	float maxSpeed;             /* Max speed */
	int troopCapacity;          /* Capacity troops it can be transport */
} tShip;

/* Function prototipes */
/* Exercise 2.1 */
void readShip (tShip *ship);
/* Exercise 2.2 */
void writeShip (tShip ship);
/* Exercise 2.3 */
bool isValidShip (tShip ship, float distance, int troops);
/* Exercise 2.4 */
int bestShip (tShip ship1, tShip ship2);

int main(int argc, char **argv)
{
	tShip ship1; 
	tShip ship2;
	
	bool isValidShip1;
	bool isValidShip2;
	
	float distanceTarget;
	int teamSize;
	
	/* Exercise 2.5 */
	/* Data input Ship1 */
    printf("ENTER DATA FOR SHIP 1\n");
    readShip(&ship1);
	/* Data input Ship2 */
    printf("ENTER DATA FOR SHIP 2\n");
    readShip(&ship2);
	
	printf("DISTANCE TO TARGET [KM]?\n");
	scanf("%f", &distanceTarget);
	
	printf("RECON TEAM SIZE?\n");
	scanf("%d", &teamSize);

    /* Exercise 2.6 */
	/* Data processing and Data Output */
	printf("RESULT\n");
	printf("SELECTED SHIP:\n");
	
	isValidShip1 = isValidShip (ship1, distanceTarget, teamSize);
	isValidShip2 = isValidShip (ship2, distanceTarget, teamSize);
	
	if (isValidShip1 && isValidShip2)
	{
		if (bestShip (ship1, ship2) >= 0)
		{
			writeShip(ship1);
		}
		else
		{
			writeShip(ship2);
		}		
	}
	else if (isValidShip1)
	{
		writeShip(ship1);
	}
	else if (isValidShip2)
	{
		writeShip(ship2);
	}
	else 
	{
		printf("NOT AVAILABLE\n");
	}
	
	return 0;
}

/* Exercise 2.1 */
void readShip (tShip *ship) {
	int intToBool; /* Auxiliar cast variable */	
	
	/* Input data */
	printf("NAME (%d CHAR MAX, NO SPACES)?\n", MAX_NAME_LENGTH-1);
    scanf("%s",ship->name);	
	
	printf("SHIP TYPE (TRANSPORT=1, FIGHTER=2, MEDICAL=3, EXPLORER=4)?\n");
	scanf("%u", &ship->shipType);
	
	printf("IS INTERPLANETARY (0-FALSE, 1-TRUE)?\n");
	scanf("%d", &intToBool);
	ship->isInterplanetary = (bool)intToBool;	
	
	printf("AUTONOMY [KM] (A REAL)?\n");
    scanf("%f", &ship->autonomy);
	
	printf("MAX SPEED [KM/H] (A REAL)?\n");
    scanf("%f", &ship->maxSpeed);	
	
	printf("TROOP CAPACITY (AN INTEGER)?\n");
	scanf("%d", &ship->troopCapacity);	
}

/* Exercise 2.2 */
void writeShip(tShip ship)
{
	printf("NAME: %s\n", ship.name);
	printf("SHIP TYPE (TRANSPORT=1, FIGHTER=2, MEDICAL=3, EXPLORER=4): %u\n", ship.shipType);
	printf("IS INTERPLANETARY (0-FALSE, 1-TRUE): %d\n", ship.isInterplanetary);	
	printf("AUTONOMY [KM]: %.2f\n", ship.autonomy);	
	printf("MAX SPEED [KM/H]: %.2f\n", ship.maxSpeed);	
	printf("TROOP CAPACITY: %d\n", ship.troopCapacity);
}

/* Exercise 2.3 */
bool isValidShip (tShip ship, float distance, int troops)
{
	return ((ship.shipType == EXPLORER || ship.shipType == TRANSPORT) && (ship.autonomy >= distance * 2 && ship.troopCapacity >= troops));
}

/* Exercise 2.4 */
int bestShip (tShip ship1, tShip ship2)
{
	int result = 0;  
	
	if (ship1.shipType == EXPLORER && ship2.shipType != EXPLORER) {
		result = 1;  
	} 
	else { 
		if (ship1.shipType != EXPLORER && ship2.shipType == EXPLORER) {
			result = -1; 
		} 
		else {
			if (ship1.autonomy > ship2.autonomy) {
				result = 1; 
			} 
			else { 
				if (ship1.autonomy < ship2.autonomy) {
					result = -1; 
				} 
				else {
					if (ship1.maxSpeed > ship2.maxSpeed) {
						result = 1; 
					} 
					else { 
						if (ship1.maxSpeed < ship2.maxSpeed) {
							result = -1; 
						} 
						else {						
							if (ship1.isInterplanetary && !ship2.isInterplanetary) {
								result = 1;
							} 
							else {
								if (!ship1.isInterplanetary && ship2.isInterplanetary) {
									result = -1;
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}
	


