#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>
#include <time.h>

#include "data.h"
#include "ship.h"
#include "starbase.h"
#include "mission.h"

void appDataInit(tAppData *object) 
{
    /* Set parent folder as the default path */
    strcpy(object->path, "../");
    
    /* Initialize the ship table */
    shipTableInit(&(object->ships));
    
    /* Initialize the starbases table */
    starbaseTableInit(&(object->starbases));
    
    /* Initialize the missions table */
    missionTableInit(&(object->missions));
}

void appDataLoad(tAppData *object, tError *retVal) {
    char path[MAX_LINE];
    *retVal = OK;
    
    /* Load the table of starbases */
    snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sstarbases.txt", object->path);
    starbaseTableLoad(&(object->starbases), path, retVal);
    if(*retVal!=OK) {
        printf("ERROR: Error reading the file of starbases\n");
    }

    /* Load the table of ships */
    snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sships.txt", object->path);
    shipTableLoad(&(object->ships), path, retVal);
    if(*retVal!=OK) {
        printf("ERROR: Error reading the file of ships\n");
    }
    
    /* Load the table of missions */
    snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%smissions.txt", object->path);
    missionTableLoad(&(object->missions), path, retVal);
    if(*retVal!=OK) {
        printf("ERROR: Error reading the file of missions\n");
    }
}

void appDataSave(tAppData object, tError *retVal)  {
    char path[MAX_LINE];
    *retVal = OK;
    
    /* Save the table of starbases */
    snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sstarbases.txt", object.path);
    starbaseTableSave(object.starbases, path, retVal);
    if(*retVal!=OK) {
        printf("ERROR: Error saving the file of starbases\n");
    }
    
    /* Save the table of ships */
    snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%sships.txt", object.path);
    shipTableSave(object.ships, path, retVal);
    if(*retVal!=OK) {
        printf("ERROR: Error saving the file of ships\n");
    }
    
    /* Save the table of missions */
    snprintf(path,MAX_PATHNAME+MAX_FILENAME,"%smissions.txt", object.path);
    missionTableSave(object.missions, path, retVal);
    if(*retVal!=OK) {
        printf("ERROR: Error saving the file of missions\n");
    }
}

void appDataSetPath(tAppData *object, const char *path)  {		
    strncpy(object->path, path, MAX_PATHNAME-1);	
}


/*********************** 
 *        API
 **********************/

void getMissions(tAppData object, tMissionTable *result) {
    *result = object.missions;	    
}

void getStarbases(tAppData object, tStarbaseTable *result) {
    *result = object.starbases;	
}

void getStarbase(tAppData *object, tStarbaseId starbaseId, tStarbase *starbase, tError *retVal) {
    
    int i;
    *retVal = OK;

    /* Check if there is a starbase with this id */
    i = starbaseTableFind(object->starbases, starbaseId);
    if (i!=NO_STARBASE) {
        starbaseCpy(starbase,object->starbases.table[i]);
    } else {
        *retVal = ERR_ENTRY_NOT_FOUND;
    }
}

void addStarbase(tAppData *object, tStarbase starbase, tError *retVal) 
{
    *retVal = OK;
    tStarbase tmp;

    /* Check if there is another starbase with the same id */
    getStarbase(object, starbase.id, &tmp, retVal);
    if(*retVal==OK) {
        *retVal = ERR_DUPLICATED_ENTRY;
    } else {
        /* Add the new starbase using the starbase table method */
        starbaseTableAdd(&(object->starbases), starbase, retVal);
    }
}

void getShips(tAppData object, tShipTable *result) {
    *result = object.ships;	
}

void getShip(tAppData object, tShipId id, tShip *ship, tError *retVal) {
    
    int i;
    *retVal = OK;
    
    /* Check if there is a ship with this id */
    i = shipTableFind(object.ships, id);
    if (i!=NO_SHIP) {
        shipCpy(ship,object.ships.table[i]);
    } else {
        *retVal = ERR_ENTRY_NOT_FOUND;
    }
}

void addShip(tAppData *object, tShip ship, tError *retVal) 
{
    *retVal = OK;
    tShip tmpShip;
    
    /* Check if there is another ship with the same id */
    getShip(*object, ship.id, &tmpShip, retVal);
    if(*retVal==OK) {
        *retVal = ERR_DUPLICATED_ENTRY;
    } else {
        /* Add the new ship using the ship table method */
        shipTableAdd(&(object->ships), ship, retVal);
    }
}

void removeShip(tAppData *object, tShip ship, tError *retVal) 
{	
    *retVal = OK;
    
    if (isShipInAnyStarbase( object->starbases, ship.id))
        *retVal = ERR_SHIP_IN_STARBASE;
    else if (isShipInAnyMission( object->missions, ship.id))
        *retVal = ERR_SHIP_IN_MISSION;
    else {
        /* Call the method from the ships table*/
        shipTableDel(&(object->ships), ship);        
    }
}


bool isShipInHangar( tHangar hangar, tShipId shipId )
{
    bool found= false;
/********************** PR4 - EX3A *****************/
    int i= 0;
 
    while (i < hangar.nShips && !found)
    {
        found = hangar.shipsId[i] == shipId ;
        i++;
    }
/***************************************************/
    return found;
}


bool isShipInLevel( tLevel level, tShipId shipId )
{
    bool found= false;
/********************** PR4 - EX3B *****************/
    int i= 0;
 
    while (i < level.hangars.nHangars && !found)
    {
        found = isShipInHangar( level.hangars.table[i], shipId );
        i++;
    }
/***************************************************/
    return found;
}


bool isShipInStarbase( tStarbase starbase, tShipId shipId )
{
    bool found= false;
/********************** PR4 - EX3C *****************/
    int i= 0;
 
    while (i < starbase.levels.nLevels && !found)
    {
        found = isShipInLevel( starbase.levels.table[i], shipId );
        i++;
    }
/***************************************************/
    return found;
}

bool isShipInAnyStarbase( tStarbaseTable starbases, tShipId shipId )
{
    bool found= false;
/********************** PR4 - EX3D *****************/
    int i= 0;
 
    while (i < starbases.nStarbases && !found)
    {
        found = isShipInStarbase( starbases.table[i], shipId );
        i++;
    }
/***************************************************/
    return found;
}

bool isShipInMission( tMission mission, tShipId shipId )
{
    bool found = false;
    int i= 0;
 
    while (i < mission.shipsNeed && !found)
    {
        found = mission.assignedShipsInfo[i].assignedShipId == shipId;
        i++;
    }

    return found;
}


bool isShipInAnyMission( tMissionTable missions, tShipId shipId )
{
    bool found= false;
    int i= 0;
 
    while (i < missions.nMissions && !found)
    {
        found= isShipInMission( missions.table[i], shipId );
        i++;
    }

    return found;
}


bool foundAllShips( int shipsTypesNeeded[SHIPS_TYPES] )
{
    int i;
    bool found = true;

    for (i=0; i < SHIPS_TYPES ; i++)
        found = found && shipsTypesNeeded[i] <= 0;

    return found;
}


int starbaseNumberShipsType(tStarbase starbase, tShipType shipType)
{
    int nShips = 0;
    int i, j;

    for (i=0; i < starbase.levels.nLevels ; i++){
        for (j=0; j < starbase.levels.table[i].hangars.nHangars ; j++){
            if (starbase.levels.table[i].hangars.table[j].hangarType == SHIPS &&
                starbase.levels.table[i].hangars.table[j].hangarShipType == shipType)
                nShips = nShips + starbase.levels.table[i].hangars.table[j].nShips;
        }
    }

    return nShips;
}



void getMission(tAppData object, tMissionId id, tMission *mission, tError *retVal)
{
    
    int i;
    *retVal = OK;
    
    /* Check if there is a ship with this id */
    i = missionTableFind(object.missions, id);
    if (i!=NO_MISSION) {
        missionCpy(mission,object.missions.table[i]);
    } else {
        *retVal = ERR_ENTRY_NOT_FOUND;
    }
 
    
}

void addMission(tAppData *object, tMission mission, tError *retVal)
{
    *retVal = OK;
    tMission tmp;

    /* Check if there is another starbase with the same id */
    getMission(*object, mission.id, &tmp, retVal);
    if(*retVal==OK) {
        *retVal = ERR_DUPLICATED_ENTRY;
    } else {
        /* Add the new mission using the mission table method */
        missionTableAdd(&(object->missions), mission, retVal);
    }
}


bool missionHasAssignedShips( tMissionTable missions, int index )
{
    return missions.table[index].assignedShips != 0;
}



void removeMission(tAppData *object, int index, tError *retVal) 
{	
    *retVal = OK;
    
    if (missionHasAssignedShips( object->missions, index))
        *retVal = ERR_MISSION_ASSIGNED;
    else {
        /* Call the method from the ships table*/
        missionTableDel(&(object->missions), object->missions.table[index].id);        
    }
}


void delShipFromStarbase(tStarbase *starbase, tShipId shipId)
{
    int pLevel, pHangar, pShip, i;
    bool found = false;

    pLevel = 0;
    while ( pLevel < starbase->levels.nLevels && !found){
        pHangar = 0;
        while ( pHangar < starbase->levels.table[pLevel].hangars.nHangars && !found){
            pShip = 0;
            while ( pShip < starbase->levels.table[pLevel].hangars.table[pHangar].nShips && !found){
                found = starbase->levels.table[pLevel].hangars.table[pHangar].shipsId[pShip] == shipId;       
                pShip++; 
            }
            pHangar++;        
        }
        pLevel++;
    }

    /* Shift other ships in hangar table */    
    for( i=pShip-1; i < starbase->levels.table[pLevel-1].hangars.table[pHangar-1].nShips-1; i++) {		
        starbase->levels.table[pLevel-1].hangars.table[pHangar-1].shipsId[i] =     
            starbase->levels.table[pLevel-1].hangars.table[pHangar-1].shipsId[i+1];
    }
    /* Update number of ships in hangar */
    starbase->levels.table[pLevel-1].hangars.table[pHangar-1].nShips--;
}

  
void assignShipsToMission(tMission *mission, tStarbase *starbase, int shipsNeed, tShipType shipType)
{  
    int i,j;
    tAssignedShip infoShip;

    i = 0;
    while ( i < starbase->levels.nLevels && shipsNeed > 0){
        j = 0;
        while ( j < starbase->levels.table[i].hangars.nHangars && shipsNeed > 0){
            if ( starbase->levels.table[i].hangars.table[j].hangarType == SHIPS && 
                 starbase->levels.table[i].hangars.table[j].hangarShipType == shipType){
                while ( starbase->levels.table[i].hangars.table[j].nShips > 0 &&
                        shipsNeed > 0){
                    infoShip.assignedShipId = starbase->levels.table[i].hangars.table[j].shipsId[0];
                    infoShip.assignedStarbase = starbase->id;
                    infoShip.assignedLevel = starbase->levels.table[i].id;
                    infoShip.assignedHangar = starbase->levels.table[i].hangars.table[j].id;
                    
                    assignedShipCpy(&mission->assignedShipsInfo[mission->assignedShips], infoShip);    
                    mission->assignedShips++;

                    /* Delete ship from starbase */
                    delShipFromStarbase(starbase, infoShip.assignedShipId);

                    /* Update number of ships needed of this type */
                    shipsNeed--;

                }            
            }
        j++;
        }
    i++;    
    }
    
}



void processMission( tMission *mission, tStarbaseTable *starbases, tError *retVal )
{
/******************************** PR4 - EX6 ***************************************/
    int pStarbase;
    tSectorId sector;
    tStarbaseTable sectorTab;
    int shipsNeed[SHIPS_TYPES];
    int i, j = 0;
    bool shipsFound = false;
    int shipsAvailable;
    tShipType shipType;
    
    *retVal= OK;

    if (mission->assignedShips != mission->shipsNeed){  
        /* Number of each ship needed*/
        for (i=0; i < SHIPS_TYPES; i++)
            shipsNeed[i] = mission->shipsTypes[i];

        /* Check if there are ships enough in start starbase */

        /* Find starbase position in starbases table*/
        pStarbase = starbaseTableFind(*starbases, mission->startStarbase);

        if (pStarbase!= NO_STARBASE){
            for (i=0; i < SHIPS_TYPES; i++){
                shipType = (tShipType)i+1;
                shipsAvailable = starbaseNumberShipsType(starbases->table[pStarbase], shipType);
                if (shipsAvailable > 0){
                    assignShipsToMission(mission, &starbases->table[pStarbase], shipsNeed[i], shipType); 
                    shipsNeed[i] = shipsNeed[i] - shipsAvailable;
                }
            }
        
            shipsFound = foundAllShips(shipsNeed);
        
            if (!shipsFound){
                /* Find if there are ships enough in other starbases of sector */

                sector = starbases->table[pStarbase].sector;

                /* Filter starbases by sector */
                starbaseTableFilterBySector(*starbases, sector, &sectorTab);
                
                /* Exclude start starbase */
                starbaseTableDel(&sectorTab, mission->startStarbase);

                if (sectorTab.nStarbases > 0){
                    j = 0;
                    while (!shipsFound && j < sectorTab.nStarbases){
                        for (i=0; i < SHIPS_TYPES; i++){
                            shipType = (tShipType)i+1;
                            shipsAvailable = starbaseNumberShipsType(sectorTab.table[j], shipType);
                            if (shipsAvailable > 0){
                                pStarbase = starbaseTableFind(*starbases, sectorTab.table[j].id);
                                assignShipsToMission(mission, &starbases->table[pStarbase], shipsNeed[i], shipType);  
                                shipsNeed[i] = shipsNeed[i] - shipsAvailable;
                            }
                        }
                        shipsFound = foundAllShips(shipsNeed);
                        j++;    
                    }

                    if (!shipsFound)
                        *retVal = ERR_CANNOT_PROCESS_MISSION;
                 } else
                     *retVal = ERR_CANNOT_PROCESS_MISSION;
            }
        } else
            *retVal = ERR_STARBASE_NOT_FOUND;
        
    } else {
        *retVal = ERR_MISSION_ALREADY_PROCESSED;
    }
/******************************************************************************************/    
}


void processAllMissions(tMissionTable *missions, tStarbaseTable *starbases, tError *retVal)
{    
    int i;
    tError retValMis;
    tMission missionAux;
    tStarbaseTable starbaseTableAux;
    
    *retVal = OK;
    
    for (i=0; i < missions->nMissions ; i++){
        /* Copy mission and starbase info */
        missionCpy(&missionAux, missions->table[i]);
        starbaseTableCpy(&starbaseTableAux, *starbases);
        
        retValMis = OK;
        processMission(&missionAux, &starbaseTableAux, &retValMis);
        if(retValMis==OK){
            /* Update info tables */
            missionCpy(&missions->table[i], missionAux);
            starbaseTableCpy(starbases, starbaseTableAux); 
        }
        else{
             printf("Can't process mission %d\n", i+1);
             *retVal = ERR_CANNOT_PROCESS_ALL;
        }
    }
        
}
