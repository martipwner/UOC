#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "starbase.h"
#include "mission.h"
#include "ship.h"

/* The content of the fields of the mission structure is written into the string str */
void getMissionStr(tMission mission, int maxSize, char *str) 
{
    char tempStr[MAX_LINE];
    int i;
    
    /* Build the string */	
    snprintf(str,maxSize-1,"%d %d %d", 
             (int)mission.id, (int)mission.startStarbase, mission.shipsNeed);
             
    /* Add the number of each ship type */	
    for (i= 0; i < SHIPS_TYPES; i++) {
        strcpy(tempStr,str);
        snprintf(str,maxSize-1,"%s %d", tempStr, mission.shipsTypes[i]); 
    }        

    /* Add the number of assigned ships */
    strcpy(tempStr,str);
    snprintf(str,maxSize-1,"%s %d", tempStr, mission.assignedShips);

    /* Add the data of assigned ships in mission */
    for (i= 0; i < mission.assignedShips; i++) {
        strcpy(tempStr,str);
#ifdef TYPEDEF_COMPLETED
        snprintf(str,maxSize-1,"%s %d %d %d %d", tempStr, 
             (int)mission.assignedShipsInfo[i].assignedShipId, (int)mission.assignedShipsInfo[i].assignedStarbase, 
             (int)mission.assignedShipsInfo[i].assignedLevel, (int)mission.assignedShipsInfo[i].assignedHangar); 
#endif
    }        
}


void missionInit( tMission *mission ) 
{    
    int i;

    mission->startStarbase =  NO_STARBASE;
    mission->shipsNeed = 0;
    for (i=0; i < SHIPS_TYPES; i++) {
        mission->shipsTypes[i] = 0;
    }
    mission->assignedShips = 0;
#ifdef TYPEDEF_COMPLETED
    for (i=0; i < MAX_MISSION_SHIPS; i++) {
        mission->assignedShipsInfo[i].assignedShipId = NO_SHIP;
        mission->assignedShipsInfo[i].assignedStarbase = NO_STARBASE;
        mission->assignedShipsInfo[i].assignedLevel = NO_LEVEL;
        mission->assignedShipsInfo[i].assignedHangar = NO_HANGAR;
    }
#endif
}



/* The content of the string str is parsed into the fields of the mission structure */
void getMissionObject(const char *str, tMission *mission) 
{
    char buffer[MAX_LINE];   
    int i, auxMissionId, auxStartStarbaseId, auxShipId, auxStarbaseId, auxLevelId, auxHangarId;

    /* clear previous mission data */
    missionInit(mission);
    
    /* read mission data */
    sscanf(str, "%d %d %d %[^\n]s", 
        &auxMissionId, &auxStartStarbaseId, &mission->shipsNeed, buffer);

    mission->id = (tMissionId)auxMissionId;
    mission->startStarbase = (tStarbaseId)auxStartStarbaseId;

    /* read number of each ship type */
    for (i=0; i < SHIPS_TYPES ; i++)
        sscanf(buffer, "%d %[^\n]s", &mission->shipsTypes[i], buffer);
         
    /* read number of assigned ships */
    sscanf(buffer, "%d %[^\n]s", &mission->assignedShips, buffer);
    
    /* read info assigned ships to mission */
    for (i=0; i < mission->assignedShips; i++){
        sscanf(buffer, "%d %d %d %d %[^\n]s", &auxShipId, &auxStarbaseId, 
            &auxLevelId, &auxHangarId, buffer);
#ifdef TYPEDEF_COMPLETED
        mission->assignedShipsInfo[i].assignedShipId = (tShipId)auxShipId;
        mission->assignedShipsInfo[i].assignedStarbase = (tStarbaseId)auxStarbaseId;
        mission->assignedShipsInfo[i].assignedLevel = (tLevelId)auxLevelId;
        mission->assignedShipsInfo[i].assignedHangar = (tHangarId)auxHangarId;
#endif        
    }
}


void assignedShipCpy(tAssignedShip *dst, tAssignedShip src)
{
#ifdef TYPEDEF_COMPLETED
    dst->assignedShipId = src.assignedShipId;
    dst->assignedStarbase = src.assignedStarbase;
    dst->assignedLevel = src.assignedLevel;
    dst->assignedHangar = src.assignedHangar;
#endif
}

void missionCpy(tMission *dst, tMission src) 
{
    int i;
    
    dst->id= src.id;
    dst->startStarbase = src.startStarbase;
    dst->shipsNeed = src.shipsNeed;
    for (i= 0; i < SHIPS_TYPES; i++)
         dst->shipsTypes[i]= src.shipsTypes[i];
    dst->assignedShips = src.assignedShips;
    for (i= 0; i < src.assignedShips; i++)
        assignedShipCpy(&dst->assignedShipsInfo[i], src.assignedShipsInfo[i]);
}


int missionCmp(tMission m1, tMission m2)
{
    int result = 0;

    if (m1.startStarbase < m2.startStarbase)
        result= 1;
    else if (m1.startStarbase > m2.startStarbase)
            result= -1;
        else if (m1.shipsNeed < m2.shipsNeed)
                result= 1;
            else if (m1.shipsNeed > m2.shipsNeed)
                    result= -1;
                else if (m1.assignedShips > m2.assignedShips)
                        result= 1;
                     else if (m1.assignedShips < m2.assignedShips)
                             result= -1;
                          else if (m1.shipsTypes[FIGHTER-1] > m2.shipsTypes[FIGHTER-1])
                                  result= 1;
                               else if (m1.shipsTypes[FIGHTER-1] < m2.shipsTypes[FIGHTER-1])
                                       result= -1;

    return result;
}


void missionTableInit(tMissionTable *missionsTable) {
    
    missionsTable->nMissions= 0;
}

void missionTableAdd(tMissionTable *tabMissions, tMission mission, tError *retVal) {

    *retVal = OK;

    /* Check if there enough space for the new mission */
    if(tabMissions->nMissions>=MAX_MISSIONS)
        *retVal = ERR_MEMORY;

    if (*retVal == OK) {
        /* Add the new mission to the end of the table */
        missionCpy(&tabMissions->table[tabMissions->nMissions],mission);
        tabMissions->nMissions++;
    }
}

void missionTableSave(tMissionTable tabMissions, const char* filename, tError *retVal) {

    *retVal = OK;

    FILE *fout=NULL;
    int i;
    char str[MAX_LINE];
    
    /* Open the output file */
    if((fout=fopen(filename, "w"))==0) {
        *retVal = ERR_CANNOT_WRITE;
    } 
    else {
        /* Save mission data to the file */
        for(i=0;i<tabMissions.nMissions;i++) 
        {
            getMissionStr(tabMissions.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
                    
        /* Close the file */
        fclose(fout);
    }
}

void missionTableLoad(tMissionTable *tabMissions, const char* filename, tError *retVal) 
{	
    char line[MAX_LINE];
    tMission newMission;
    FILE *fin=NULL;
    *retVal = OK;

    /* Initialize the output table */
    missionTableInit(tabMissions);
    
    /* Open the input file */
    if((fin=fopen(filename, "r"))!=NULL) {

        /* Read all the missions */
        while(!feof(fin) && tabMissions->nMissions<MAX_MISSIONS) 
        {
            /* Read the mission object */
            line[0] = '\0';
            fgets(line, MAX_LINE-1, fin);
            line[MAX_LINE-1]='\0';
            if (strlen(line)>0) {
                /* Obtain the object */
                getMissionObject(line, &newMission);

                /* Add the new mission to the output table */
                missionTableAdd(tabMissions, newMission, retVal);	
            }	
        }
        /* Close the file */
        fclose(fin);
        
    }else {
        *retVal = ERR_CANNOT_READ;
    }
}

void missionTableCpy(tMissionTable *tabDest, tMissionTable tabSrc )
{
    int i;
    
    tabDest->nMissions = tabSrc.nMissions;
    for (i = 0; i < tabSrc.nMissions; i++) {
        missionCpy(&tabDest->table[i], tabSrc.table[i]);
    }
}


int missionTableFind(tMissionTable missions, tMissionId id) {

    int idx = NO_MISSION;
    
    int i=0;
    while(i< missions.nMissions && idx==NO_MISSION) {
        /* Check if the id is the same */
        if(missions.table[i].id==id) {
            idx = i;
        }
        i++;
    }
    
    return idx;
}

void missionTableDel(tMissionTable *missions, tMissionId id) 
{	
    int i;
    int pos;

    pos = missionTableFind(*missions, id);
    if (pos!=NO_MISSION)
    {
        for(i=pos; i<missions->nMissions-1; i++) {		
            missionCpy(&missions->table[i],missions->table[i+1]);
        }
        missions->nMissions=missions->nMissions-1;		
    }
}


void missionTableSortByShips(tMissionTable *tabMissions)
{
/************* PR4 - EX5C *************/
// No funciona Xwiki aunque sí los PDF's
    int i, j, maxIdx;
    tMission temp;

    for (i = 0; i < tabMissions->nMissions - 1; i++) {
        // Inicializar el índice del máximo
        maxIdx = i;
        // Buscar el índice de la mejor misión
        for (j = i + 1; j < tabMissions->nMissions; j++) {
            if (missionCmp(tabMissions->table[j], tabMissions->table[maxIdx]) > 0) {
                maxIdx = j;
            }
        }

        // Intercambiar la misión con el mejor parámetro con la primera misión no ordenada
        if (maxIdx != i) {
            temp = tabMissions->table[i];
            tabMissions->table[i] = tabMissions->table[maxIdx];
            tabMissions->table[maxIdx] = temp;
        }
    }

/**************************************/
}

