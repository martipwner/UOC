#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appDataInit(tAppData *object);

/* Load the application data from file */
void appDataLoad(tAppData *object, tError *error);

/* Save the application data to a file */
void appDataSave(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appDataSetPath(tAppData *object, const char *path);

/* 
 * API
 */


/* Return a table with the ships */
void getShips(tAppData object, tShipTable *result);

/* Get the ship information */
void getShip(tAppData object, tShipId shipId, tShip *ship, tError *retVal);

/* Add a new ship */
void addShip(tAppData *object, tShip ship, tError *retVal);
             
/* Says if a certain ship is in an hangar */
bool isShipInHangar( tHangar hangar, tShipId shipId);

/* Says if a certain ship is in a level of a starbase */
bool isShipInLevel( tLevel level, tShipId shipId);

/* Says if a certain ship is in a starbase */
bool isShipInStarbase( tStarbase starbase, tShipId shipId);

/* Says if a certain ship is in any starbase */
bool isShipInAnyStarbase( tStarbaseTable starbases, tShipId shipId );

/* Says if a certain ship is assigned in a certain mission */
bool isShipInMission( tMission mission, tShipId shipId );

/* Says if a certain ship is assigned in any starbase */
bool isShipInAnyMission( tMissionTable missions, tShipId shipId );

/* Remove a certain ship */
void removeShip(tAppData *object, tShip ship, tError *retVal);

/* Return the table of starbases */
void getStarbases(tAppData object, tStarbaseTable *result);

/* Get the starbase information */
void getStarbase(tAppData *object, tStarbaseId starbaseId, tStarbase *starbase, tError *retVal);

/* Add a new starbase */
void addStarbase(tAppData *object, tStarbase starbase, tError *retVal);

/* Return a table with the missions */
void getMissions(tAppData object, tMissionTable *result);

/* Return a mission with certain id */
void getMission(tAppData object, tMissionId id, tMission *mission, tError *retVal);

/* Add a new mission */
void addMission(tAppData *object, tMission mission, tError *retVal);

/* Remove a certain mission */
void removeMission(tAppData *object, int index, tError *retVal);

/* Processes a single mission */
void processMission( tMission *mission, tStarbaseTable *starbases, tError *retVal );

/* Processes all missions */
void processAllMissions(tMissionTable *missions, tStarbaseTable *starbases, tError *retVal);
