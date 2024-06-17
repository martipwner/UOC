#include "data.h"

/* Get a textual representation of a ship */
void getShipStr(tShip ship, int maxSize, char *str);
    
/* Get a ship object from its textual representation */
void getShipObject(const char *str, tShip *ship);

/* Compare two ships */
int shipCmp(tShip ship1, tShip ship2);

/* Copy the ship data in src to dst*/
void shipCpy(tShip *dst, tShip src);

/* Initialize the table of ships */
void shipTableInit(tShipTable *table);

/* Add a new ship to the table of ships */
void shipTableAdd(tShipTable *table, tShip ship, tError *retVal);

/* Find a ship in the table and returns its position */
int shipTableFind(tShipTable table, tShipId id);

/* Remove the first occurence of a ship in the table */
void shipTableDel(tShipTable *table, tShip ship);

/* Load the table of ships from a file */
void shipTableLoad(tShipTable *table, const char* filename, tError *retVal);

/* Save a table of ships to a file */
void shipTableSave(tShipTable table, const char* filename, tError *retVal);

/* Selects ships with a given type of ship */
void shipTableSelectShips(tShipTable ships, tShipType shipType, tShipTable *result);
