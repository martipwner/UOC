#include <stdbool.h>

/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

#define TYPEDEF_COMPLETED

#define MAX_PATHNAME 255
#define MAX_FILENAME 25
#define MAX_LINE 514

#define MAX_MODEL_NAME 20+1
#define MAX_PLANET_NAME 20+1
#define MAX_BASE_NAME 15+1

#define MAX_SHIPS 500
#define MAX_HANGARS 20
#define MAX_LEVELS 10
#define MAX_STARBASES 50
#define MAX_HANGAR_SHIPS 30


#define NO_SHIP -1
#define NO_STARBASE -1
#define NO_LEVEL -1
#define NO_HANGAR -1
#define NO_MISSION -1
#define NO_SECTOR -1
#define NO_SHIP_TYPE -1
#define NO_HANGAR_TYPE -1


#define MAX_NAME 25+1
#define MAX_TYPE_NAME 10
#define SHIPS_TYPES 5
#define MAX_MISSIONS 50
#define MAX_MISSION_SHIPS 20

    
/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
              ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
              ERR_ENTRY_NOT_FOUND=-6, ERR_STARBASE_NOT_FOUND=-7, 
              ERR_CANNOT_PROCESS_MISSION=-8, ERR_NO_MISSION=-9, ERR_NO_LEVEL= -10, 
              ERR_NO_HANGAR= -11, ERR_MISSION_ASSIGNED= -12, ERR_SHIP_IN_STARBASE= -13, 
              ERR_SHIP_IN_MISSION= -14, ERR_MISSION_HAS_SHIPS= -15, 
              ERR_CANNOT_PROCESS_ALL= -16, ERR_MISSION_ALREADY_PROCESSED= -17
              } tError;

typedef int tShipId;
typedef int tStarbaseId;
typedef int tLevelId;
typedef int tHangarId;
typedef int tMissionId;
typedef int tSectorId;


typedef enum {CARRIER=1, TRANSPORT, FIGHTER, MEDICAL, EXPLORER} tShipType;
typedef enum {STORAGE=1, SHIPS, OTHERS} tHangarType;

typedef struct {
  tShipId id;
  tShipType shipType;
  int shipEngines;
  char model[MAX_MODEL_NAME];
  bool isInterplanetary;
  float autonomy;
  int troopCapacity; 
} tShip;

typedef struct {
  tShip table[MAX_SHIPS];
  int nShips;
} tShipTable;
  
typedef struct {
  tHangarId id;
  bool isAvailable;
  tHangarType hangarType;
  tShipType hangarShipType;
  int nShips;
  tShipId shipsId[MAX_HANGAR_SHIPS];
} tHangar;

typedef struct {
  tHangar table[MAX_HANGARS];
  int nHangars;
} tHangarTable;

typedef struct {
  tLevelId id;
  tHangarTable hangars;
} tLevel;

typedef struct {
  tLevel table[MAX_LEVELS];
  int nLevels;
} tLevelTable;

typedef struct {
  tStarbaseId id;
  char baseName[MAX_BASE_NAME];
  char planet[MAX_PLANET_NAME];
  tSectorId sector;
  tLevelTable levels;
} tStarbase;


typedef struct {
  tStarbase table[MAX_STARBASES];
  int nStarbases; 
} tStarbaseTable;


/************** PR4 - EX1 ************/
typedef struct {
    tShipId assignedShipId;
    tStarbaseId assignedStarbase;
    tLevelId assignedLevel;
    tHangarId assignedHangar;
} tAssignedShip;
/*************************************/

typedef struct {
    tMissionId id; 
    tStarbaseId startStarbase;
    int shipsNeed;
    int shipsTypes[SHIPS_TYPES];
    int assignedShips;
    tAssignedShip assignedShipsInfo[MAX_MISSION_SHIPS];  // info assigned ships in mission
} tMission;

typedef struct {
  tMission table[MAX_MISSIONS];
  int nMissions; 
} tMissionTable;

/* Definition of the application data structure */
typedef struct 
{
    /* Path where data will be stored */
    char path[MAX_PATHNAME];
    
    /* Starbase */
    tStarbaseTable starbases;
    
    /* Ships table */
    tShipTable ships;

    /* Missions table */
    tMissionTable missions;
    
} tAppData;

/*********************** 
 *    COMMON HEADERS
 **********************/

/* Compares two strings in uppercase */
int strcmpUpper( char *s1, char *s2 );

/* Converts an string to upper case */
void convertToUpper( char *string );

#endif /*__DATA_H*/
