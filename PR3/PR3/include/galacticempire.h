/*
* File: galacticempire.h
* Author: UOC
* Course: 20232
* Description: PR3
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_SHIPS  10  /* Max. ships */
#define MAX_IMPERIAL_BASES  5/* Max. Imperial bases */

#define MAX_LINE 514
#define MAX_FILENAME_LENGTH 15+1
#define MAX_NAME_LENGTH 15+1 

/* User defined types */

/* Error type */
typedef enum {OK = 0, ERR_CANNOT_READ = -1, ERR_MEMORY = -2, ERR_NOT_FOUND = -3} tError;

/* Ship type */
typedef enum {TRANSPORT=1, FIGHTER, MEDICAL, EXPLORER} tShipType;


typedef struct {    
    char name[MAX_NAME_LENGTH]; /* Ship name */
    tShipType shipType;         /* Ship type */
	int troopCapacity;          /* Capacity troops it can be transport */
} tShip;


/* Ship table */
typedef struct {
	tShip ships[MAX_SHIPS];
	int numShips;
} tShipTable;

typedef struct {
	char name[MAX_NAME_LENGTH]; /* imperial base name */
	tShipTable shipTable;       /* Ships deployed */
} tImperialBase;

/* Imperial Bases table */
typedef struct {
	tImperialBase imperialBases[MAX_IMPERIAL_BASES];
	int numImperialBases;
} tImperialBaseTable;

/* Auxiliary Actions */
/* Imperial base table init*/
void initImperialBaseTable(tImperialBaseTable *tabImperialBases);
/* Load imperial base table from file */
void loadImperialBaseTable(tImperialBaseTable *tabImperialBases, const char* filename, tError *retVal);
/* Write a imperial base */
void writeImperialBase(tImperialBase imperialBase) ;
/* Write a imperial bases table  */
void writeImperialBaseTable(tImperialBaseTable tabImperialBases);


/* Exercise 2.1 */
void selectImperialBase (tImperialBaseTable tabImperialBases, char* baseName, tImperialBase *imperialBase, tError *retVal);
/* Exercise 2.2 */
void sortShipsByCapacity (tShipTable *tabShips);