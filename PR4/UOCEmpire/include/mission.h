#include "data.h"

/* Get a textual representation of a mission */
void getMissionStr(tMission mission, int maxSize, char *str);

/* Get a mission object from its textual representation */
void getMissionObject(const char *str, tMission *mission);

/* Initialises the given mission */
void missionInit( tMission *mission );

/* Copy the mission data in src to dst*/
void missionCpy(tMission *dst, tMission src);

/* Compares the mission data of m1 and m2*/
int missionCmp(tMission m1, tMission m2);

/* Creates a mission with the given data */
void createMission( tMission *mission, tStarbaseId starbaseId);
                     
/* Initializes the given missions table */
void missionTableInit(tMissionTable *missionsTable);

/* Add a new mission to the table of missions */
void missionTableAdd(tMissionTable *tabMissions, tMission mission, tError *retVal);

/* Find a mission in missions table */
int missionTableFind(tMissionTable missions, tMissionId id);

/* Remove a mission from missions table */
void missionTableDel(tMissionTable *missions, tMissionId id);

/* Load the table of missions from a file */
void missionTableLoad(tMissionTable *tabMissions, const char* filename, tError *retVal);

/* Save a table of missions to a file */
void missionTableSave(tMissionTable tabMissions, const char* filename, tError *retVal);

/* Copies a mission table onto another mission table */
void missionTableCpy(tMissionTable *tabDest, tMissionTable tabSrc );

/* Sorts missions table by number of ships in the same mission */
void missionTableSortByShips(tMissionTable *tabMissions);

/* Copy info from one assigned ship to another */
void assignedShipCpy(tAssignedShip *dst, tAssignedShip src);