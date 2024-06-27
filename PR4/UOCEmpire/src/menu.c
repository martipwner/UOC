#include <stdio.h>
#include <string.h>

#include "data.h"
#include "menu.h"
#include "starbase.h"
#include "ship.h"
#include "mission.h"

int getOption(int numOptions) {
    int option=0;
        
    while(option<1 || option>numOptions) {
        /* Read the input */
        printf(">> ");
            scanf("%u", &option);
        getchar();
        
        /* Check the user input */
        if(option<1 || option>numOptions) {
            printf("Incorrect option.\n");
        }
    }
     return option;
}

void readShip(tShip *ship, tError *retVal)
{	
    int number, auxShipType;
    float real;
    char buffer[MAX_LINE];
    int length;

    printf("Enter the information for the new ship:\n");

    *retVal = ERROR;
    
    /* Request information from ship */ 
    while (*retVal == ERROR) {
        printf("Ship id (integer greater than %d):\n>> ", 0);
        scanf("%d",&number);
        if (number >= 1 ) {
            ship->id = (tShipId)number;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Ship type (1-CARRIER, 2-TRANSPORT, 3-FIGHTER, 4-MEDICAL, 5-EXPLORER)\n>> ");
        scanf("%d", &auxShipType); 
        if ( auxShipType>= CARRIER && auxShipType <= EXPLORER) {
            ship->shipType = (tShipType)auxShipType;           
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Ship number engines (integer greater than %d):\n>> ", 0);
        scanf("%d",&number);
        if (number >= 1) {
            ship->shipEngines = number;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Ship model (%d char max, no spaces):\n>> ", MAX_MODEL_NAME-1);
        scanf("%s",buffer);
        length = strlen(buffer);
        if (length > 0 && length <= MAX_MODEL_NAME-1) {
            strncpy(ship->model,buffer,MAX_MODEL_NAME);
            *retVal = OK;
        }
    }
    
    
    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Is interplanetary? (0-NO, 1-YES):\n>> ");
        scanf("%d",&number);
        if(number>=0 && number <=1) {
            ship->isInterplanetary= (bool)number;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Autonomy (KM, real greater than %d):\n>> ", 0);
        scanf("%f",&real);
        if (real > 0.0) {
            ship->autonomy = real;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Troop capacity (integer greater than %d):\n>> ", 0);
        scanf("%d",&number);
        if (number >= 1) {
            ship->troopCapacity = number;
            *retVal = OK;
        }
    }
    
    
}

void readHangar(tHangar *hangar, tHangarId id, tShipTable shipTable, tError *retVal) 
{
    int number, auxHangarType, auxHangarShipType, nShips, shipId;
    int i;
    
    /* autoassign id */
    hangar->id = (tHangarId)id;

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Is available? (0-NO, 1-YES):\n>> ");
        scanf("%d",&number);
        if(number>=0 && number <=1) {
            hangar->isAvailable = (bool)number;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Hangar type? (1-STORAGE, 2-SHIPS, 3-OTHERS)\n>> ");
        scanf("%d", &auxHangarType); 
        if ( auxHangarType >= STORAGE && auxHangarType <= OTHERS) {
            hangar->hangarType = auxHangarType;           
            //*retVal = OK;
            /* Hangar stores ships */
            if ( auxHangarType == SHIPS ) {
/**************************** PR4 - EX4 ***********************/
                //*retVal = ERROR;
                while (*retVal == ERROR) {
                    printf("Hangar ship type? (1-CARRIER, 2-TRANSPORT, 3-FIGHTER, 4-MEDICAL, 5-EXPLORER)\n>> ");
                    scanf("%d", &auxHangarShipType); 
                    if ( auxHangarShipType >= CARRIER && auxHangarShipType <= EXPLORER) {
                        hangar->hangarShipType = auxHangarShipType;
                        printf("Number of ships in hangar? (integer greater than %d and less than %d):\n>> ", 0, MAX_HANGAR_SHIPS);
                        scanf("%d", &nShips);
                        while (nShips<=0 || nShips>=MAX_HANGAR_SHIPS){
                            printf("Incorrect value, try again\n");
                            printf("Number of ships in hangar? (integer greater than %d and less than %d):\n>> ", 0, MAX_HANGAR_SHIPS);
                            scanf("%d", &nShips);
                        }
                        for (i=0; i < nShips ; i++){
                            printf("Identifier ship %d in hangar\n", i+1);
                            scanf("%d", &shipId);
                            /* Check ship is in ships table */
                            while (shipTableFind(shipTable, (tShipId) shipId)== NO_SHIP){
                                printf("Ship unknown in ships table. Please, select another one.\n");
                                printf("Identifier ship %d in hangar\n", i+1);
                                scanf("%d", &shipId);
                            }
                            
                            hangar->shipsId[i] = (tShipId)shipId;
                            hangar->nShips++;
                            
                        }
                        *retVal = OK;
                    }
                    else
                        printf("Incorrect type of ship\n");
                }
             } 
/******************************************************************************/
             else {
                 /* Hangar not stores ships */
                 hangar->hangarShipType = NO_SHIP_TYPE;
                 hangar->nShips = 0;
                 for (i=0; i<MAX_HANGAR_SHIPS; i++) 
                     hangar->shipsId[i] = NO_SHIP;
                 *retVal = OK;
             }

        }
    }
 
}

void hangarTableInit(tHangarTable *hangarsTable)
{	
    hangarsTable->nHangars=0;
}


void hangarTableAdd(tHangarTable *hangarsTable, tHangar hangar, tError *retVal)
{
    *retVal = OK;

    /* Check if there enough space for the new level */
    if(hangarsTable->nHangars >= MAX_HANGARS)
    *retVal = ERR_MEMORY;

    if (*retVal == OK) {
        /* Add the new hangar to the end of the table */
        hangarCpy(&hangarsTable->table[hangarsTable->nHangars], hangar);
    hangarsTable->nHangars++;
    }
}


void readLevel(tLevel *level, tLevelId id, tShipTable shipTable, tError *retVal) 
{
    int nHangars;
    int i;
    tHangar auxHangar;

    /* autoassign id */
    level->id = id;

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Number of hangars of level (integer greater or equal to 1 and less or equal to %d)\n>> ", MAX_HANGARS);
        scanf("%d",&nHangars);
        if (nHangars >= 1 && nHangars < MAX_HANGARS) {
            *retVal = OK;
            /* read hangars data */
            hangarTableInit(&level->hangars);
            for (i=0; i < nHangars; i++) {
                *retVal = ERROR;
                while (*retVal == ERROR) {
                    printf("Info hangar %d\n", i+1);
                    readHangar(&auxHangar, (tHangarId)i+1, shipTable, retVal);
                }
                hangarTableAdd(&level->hangars, auxHangar, retVal);
            }
        }
    }
  
        
}

void levelTableInit(tLevelTable *levelsTable)
{
    levelsTable->nLevels=0;
}

void levelTableAdd(tLevelTable *levelsTable, tLevel level, tError *retVal)
{
    *retVal = OK;

    /* Check if there enough space for the new level */
    if(levelsTable->nLevels >= MAX_LEVELS)
        *retVal = ERR_MEMORY;

    if (*retVal == OK) {
        /* Add the new level to the end of the table */
        levelCpy(&levelsTable->table[levelsTable->nLevels], level);
    levelsTable->nLevels++;
    }
}


void readStarbase(tStarbase *starbase, tShipTable shipTable, tError *retVal)
{	
    char buffer[MAX_LINE];
    int number, i, length, nLevels;
    tLevel auxLevel;

    
    *retVal = ERROR;

    while (*retVal == ERROR) {
        printf("Starbase id (integer greater than %d):\n>> ", 0);
        scanf("%d",&number);
        if (number >= 1 ) {
            starbase->id = (tStarbaseId)number;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Starbase name (max %d char, no spaces):\n>> ", MAX_BASE_NAME-1);
        scanf("%s",buffer);
        length = strlen(buffer);
        if (length<MAX_NAME) {
            strncpy(starbase->baseName,buffer,MAX_BASE_NAME);
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Starbase planet (max %d char, no spaces):\n>> ", MAX_PLANET_NAME-1);
        scanf("%s",buffer);
        length = strlen(buffer);
        if (length<MAX_PLANET_NAME) {
            strncpy(starbase->planet,buffer,MAX_PLANET_NAME);
            *retVal = OK;
        }
    }
    
    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Starbase sector identifier (integer greater than %d):\n>> ", 0);
        scanf("%d",&number);
        if(number>=1) {
            starbase->sector = (tSectorId)number;
            *retVal = OK;
        }
    }
    
    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Number of levels of starbase (integer greater or equal to 1 and less or equal to %d)\n>> ", MAX_LEVELS);
        scanf("%d",&nLevels);
        if (nLevels >= 1 && nLevels <= MAX_LEVELS) {
            *retVal = OK;
            /* read levels data */
            levelTableInit(&starbase->levels);
            for (i=0; i < nLevels; i++) {
                *retVal = ERROR;
                while (*retVal == ERROR) {
                    printf("Info level %d\n", i+1);
                    readLevel(&auxLevel, (tLevelId)i+1, shipTable, retVal);
                }
                levelTableAdd(&starbase->levels, auxLevel, retVal);
            }
        }
    }
    
}


void printStarbaseInfo(tStarbase starbase) 
{    
    char starbaseStr[MAX_LINE];
    int i,j;
    
    getStarbaseStr(starbase, MAX_LINE, starbaseStr);
    printf("%s\n", starbaseStr);
    for(i=0; i<starbase.levels.nLevels ; i++){
        getLevelStr(starbase.levels.table[i], MAX_LINE, starbaseStr);
        printf("Level%u - %s\n", i+1, starbaseStr);
        for(j=0; j<starbase.levels.table[i].hangars.nHangars; j++){
            getHangarStr(starbase.levels.table[i].hangars.table[j], MAX_LINE, starbaseStr);
            printf("Hangar%u - %s\n", j+1, starbaseStr);
        }
    }
}


void printStarbase(tStarbase starbase, int index) 
{    
    char starbaseStr[MAX_LINE];
    
    getStarbaseStr(starbase, MAX_LINE, starbaseStr);
    printf("[%u] - %s\n", index, starbaseStr);
}


void printStarbaseTable(tStarbaseTable table) 
{
    int i;	
    
    if(table.nStarbases==0)
        printf("No starbases.\n");
    else {
        for(i=0; i < table.nStarbases; i++)
            printStarbase(table.table[i], i+1);		
    }
}

void printShip(tShip ship, int index) 
{    
    char shipStr[MAX_LINE];
    
    getShipStr(ship, MAX_LINE, shipStr);
    printf("[%u] - %s\n", index, shipStr);
}


void printShipTable(tShipTable table) 
{
    int i;	
    
    if(table.nShips==0)
        printf("No ships.\n");
    else {
        for(i=0; i < table.nShips; i++)
            printShip(table.table[i], i+1);		
    }
}


void printMission( tMission mission, int index) 
{    
    char missionStr[MAX_LINE];
    getMissionStr(mission, MAX_LINE, missionStr);
    printf("[%u] - %s\n", index, missionStr);
}

void printMissionTable(tMissionTable table)
{
    int i;	
    
    if(table.nMissions==0)
        printf("No missions.\n");
    else {
        for(i=0; i < table.nMissions; i++)
            printMission( table.table[i], i+1 );
    }
}

void getTypeName(int orderTypeName, char *typeName)
{
    
    strcpy( typeName, "");
    if (orderTypeName == 1)
        strcpy( typeName, "CARRIER");
    else if (orderTypeName == 2)
            strcpy( typeName, "TRANSPORT");
         else if (orderTypeName == 3)
                 strcpy( typeName, "FIGHTER");
              else if (orderTypeName == 4)
                      strcpy( typeName, "MEDICAL");
                   else
                       strcpy( typeName, "EXPLORER");
}


void readMission(tMission *mission, tError *retVal)
{	
    int number, auxStarbaseId;
    char typeName[MAX_TYPE_NAME];
    int i;

    *retVal = ERROR;
    
    /* Request information from mission */ 
    while (*retVal == ERROR) {
        printf("Mission id (integer greater than %d):\n>> ", 0);
        scanf("%d",&number);
        if (number >= 1 ) {
            mission->id = (tMissionId)number;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Starbase initial (integer greater than %d):\n>> ", 0);
        scanf("%d", &auxStarbaseId); 
        if ( auxStarbaseId >= 1 ) {
            mission->startStarbase = (tStarbaseId)auxStarbaseId;           
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        printf("Number of ships needed (integer greater than %d and less than %d):\n>> ", 0, MAX_MISSION_SHIPS);
        scanf("%d",&number);
        if (number > 0 || number <= MAX_MISSION_SHIPS) {
            mission->shipsNeed = number;
            *retVal = OK;
        }
    }

    *retVal = ERROR;
    while (*retVal == ERROR) {
        number = 0;
        printf("Number of each type of ships\n");
        for (i=0; i < SHIPS_TYPES; i++){
            getTypeName(i+1, typeName);
            printf("Number of %s ships:\n>> ", typeName);
            scanf("%d",&mission->shipsTypes[i]);
            number = number + mission->shipsTypes[i]; 
        }
        
        if (number == mission->shipsNeed)
            *retVal = OK;
    }
    
}


void printMissionInfo(tMission mission, tStarbaseTable starbases)
{
/************************ PR4 - EX7 **************************/
    int pStarbase,i;
    char typeName[MAX_TYPE_NAME];

    pStarbase = starbaseTableFind(starbases, mission.startStarbase);

    printf("------------------------------------------------------\n");
    printf("  Mission identifier: %d \n", mission.id );               
    printf("------------------------------------------------------\n");
    printf("  Mission starbase initial.... \n" );               
    printf("  Identifier: %d\n", (int)mission.startStarbase );               
    printf("  Name: %s\n", starbases.table[pStarbase].baseName );               
    printf("  Planet: %s \n", starbases.table[pStarbase].planet );
    printf("------------------------------------------------------\n");
    printf("  Mission resources.... \n" );
    
    for (i=0; i < SHIPS_TYPES ; i++){
        getTypeName(i+1, typeName);
        printf("  Ships %s type: %d\n", typeName, mission.shipsTypes[i] );               
    }         

    printf("------------------------------------------------------\n");

    if (mission.assignedShips > 0){
        printf("  Assigned ships.... \n" );

        for (i=0; i < mission.assignedShips ; i++){
            pStarbase = starbaseTableFind(starbases, mission.assignedShipsInfo[i].assignedStarbase);
            printf("  [%d] Id: %d Starbase: %s Level: %d Hangar: %d\n", i+1, mission.assignedShipsInfo[i].assignedShipId, 
                    starbases.table[pStarbase].baseName, mission.assignedShipsInfo[i].assignedLevel, 
                    mission.assignedShipsInfo[i].assignedHangar );
        } 
    }
    else 
        printf("  Ships: Not yet assigned\n" );               
   
    printf("------------------------------------------------------\n");

/***********************************************************/
}

/*****************
 **   MAIN MENU **
*****************/
void printMainMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Main Menu \n");
    printf("=======================\n");
    printf("1) Load data from file\n");
    printf("2) Save data to file\n");
    printf("3) Manage ships\n");
    printf("4) Manage starbases\n");
    printf("5) Manage missions\n");
    printf("6) View statistics\n");
    printf("7) Exit\n");	
}

tMainMenuOptions getMainMenuOption() {
    /* Convert to the correct type */
    return (tMainMenuOptions)(getOption(7)-1);
}

void mainMenu(tAppData *appData) 
{
    tMainMenuOptions option;
    tError retVal;
        
    /* Assign the data path */
    appDataSetPath(appData,"../");
        
    /* Start the menu */
    
    /* Show list of options and ask the user for an option */
    printMainMenuOptions();
    option=getMainMenuOption();
    
    while (option!=MAIN_MENU_EXIT) 
    {
        /* Do the action for the given option */
        if (option == MAIN_MENU_LOAD) {
            appDataLoad(appData,&retVal);
            if(retVal==OK) {
                printf("Data loaded\n");
            } else {	
                printf("No previous data loaded\n");
            }
        } else if (option == MAIN_MENU_SAVE) {
            appDataSave(*appData,&retVal);
            if(retVal==OK) {
                printf("Data saved\n");
            } else {	
                printf("Cannot save the data\n");
            }
        } else if (option == MAIN_MENU_SHIP) {
            shipMenu(appData);
        } else if (option == MAIN_MENU_STARBASE) {
            starbaseMenu(appData);
        } else if (option == MAIN_MENU_MISSION) {
            missionMenu(appData);
        } else if (option == MAIN_MENU_STAT) {
            statMenu(appData);
        } 
        
        /* Show list of options and ask the user for an option */
        printMainMenuOptions();
        option=getMainMenuOption();
    }
}

/*********************************
 **   SHIP MANAGEMENT MENU **
*********************************/
void printShipMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Manage Ships\n");
    printf("=======================\n");
    printf("1) List ships\n");	
    printf("2) Add ship\n");
    printf("3) Delete ship\n");	
    printf("4) Clear all ships\n");
    printf("5) Exit\n");	
}

tShipMenuOptions getShipMenuOption() {
    /* Convert to the correct type */
    return (tShipMenuOptions)(getOption(5)-1);
}

void shipMenu(tAppData *appData) {
    tShipMenuOptions option;
    tShip newShip;
    tShipTable shipTable; 
    char shipStr[MAX_LINE];
    int i, pos=0, skipped;
    tError retVal;
            
    /* Start the menu */
    /* Show list of options and ask the user for an option */
    printShipMenuOptions();
    option=getShipMenuOption();    
    
    while(option!=SHIP_MENU_EXIT)
    {		
        /* Do the action for the given option */
        if (option == SHIP_MENU_LIST ) {
            getShips(*appData, &shipTable);
            printShipTable(shipTable);
        } else if (option == SHIP_MENU_ADD) {
            readShip(&newShip, &retVal);
            getShipStr(newShip, MAX_LINE, shipStr);
            if(retVal==OK) {
                addShip(appData, newShip, &retVal);
                if(retVal==OK){
                    printf("Ship added: %s\n", shipStr);
                } else if(retVal==ERR_DUPLICATED_ENTRY) {
                    printf("Duplicated ship identifier. Ship not added: %s\n", shipStr);
                } else {
                    printf("No more space. Ship not added: %s\n", shipStr);
                }
            } else {
                printf("Error in input. Ship not added: \n%s\n", shipStr);
            }
        } else if (option == SHIP_MENU_DEL) {
            getShips(*appData, &shipTable);			
            /* Print the ships */			
            printShipTable(shipTable);		

            if (shipTable.nShips > 0) {
                /* Ask the number of the register to be removed */
                printf("Enter the number of the ship to delete:\n");
                pos=getOption(shipTable.nShips);
                removeShip(appData, shipTable.table[pos-1], &retVal);
            
                if(retVal==OK){
                    printf("Ship removed.\n");
                } else if(retVal==ERR_SHIP_IN_STARBASE) {
                    printf("Ship found in starbase. Ship was not removed.\n");
                    } else {
                        printf("Ship found in mission. Ship was not removed.\n");
                      }
            }
        } else if (option == SHIP_MENU_CLEAR_ALL) {
            
                      skipped= 0;
                      getShips(*appData, &shipTable);	
            
                      if (shipTable.nShips > 0) {

                          for (i= shipTable.nShips-1; i >= 0; i--) {                   
                              removeShip(appData, shipTable.table[i], &retVal);
                
                              if(retVal==OK){
                                  printf("Ship removed.\n");
                              } else if(retVal==ERR_SHIP_IN_STARBASE) {
                                    printf("Ship found in starbase. Ship was not removed.\n");
                                    skipped++;
                              } else {
                                    printf("Ship found in mission. Ship was not removed.\n");
                                    skipped++;
                              }
                         }
                         if (skipped > 0)
                             printf("Some ships could not be removed because they were found either in starbase or in a mission.\n");
                         } else
                               printf("No ships.\n");
                
        } 
        
        /* Show list of options and ask the user for an option */
        printShipMenuOptions();
        option=getShipMenuOption();        
    }
}

/********************************
 **   STARBASE MANAGEMENT MENU **
********************************/
void printStarbaseMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Manage starbases\n");
    printf("=======================\n");
    printf("1) List starbases\n");	
    printf("2) View starbase info\n");
    printf("3) Add starbase\n");
    printf("4) Copy starbase\n");
    printf("5) Starbase occupation\n");
    printf("6) View sector starbases\n");
    printf("7) Sort starbases by occupation\n");
    printf("8) Exit\n");	
}

tStarbaseMenuOptions getStarbaseMenuOption() {
    /* Convert to the correct type */
    return (tStarbaseMenuOptions)(getOption(8)-1);
}

void starbaseMenu(tAppData *appData) {
    
    tError retVal = OK;
    tStarbaseMenuOptions option;
    tStarbase newStarbase;
    char starbaseStr[MAX_LINE];
    int pos, number;
    int pStarbase= NO_STARBASE;
    tStarbaseTable starbaseTable;


    /* Start the menu */
    /* Show list of options and ask the user for an option */
    printStarbaseMenuOptions();
    option=getStarbaseMenuOption();	
    
    while(option!=STARBASE_MENU_EXIT)
    {
        /* Do the action for the given option */
        if (option == STARBASE_MENU_LIST) {
            getStarbases(*appData, &starbaseTable);
            printStarbaseTable(starbaseTable);
        }    
        else if (option == STARBASE_MENU_INFO_STARBASE) {
            getStarbases(*appData, &starbaseTable);
            if (starbaseTable.nStarbases > 0) {
                printStarbaseTable(starbaseTable);
                /* Ask the number of the register to be printed */
                printf("Enter the number of the starbase to view info:\n");
                pStarbase=getOption(starbaseTable.nStarbases)-1;
                printStarbaseInfo(starbaseTable.table[pStarbase]);
            }
            else
                printf("No starbases\n");
        }
        else if (option == STARBASE_MENU_ADD) {
            readStarbase(&newStarbase, appData->ships, &retVal);
            getStarbaseStr(newStarbase, MAX_LINE, starbaseStr);    
            if(retVal==OK) {
                addStarbase(appData, newStarbase, &retVal);
                if (retVal == OK) { 
                    printf("Starbase added: %s\n", starbaseStr);
                } else if(retVal==ERR_DUPLICATED_ENTRY) {
                        printf("Duplicated starbase identifier. Starbase not added: %s\n", starbaseStr);                     
                } else {
                       printf("No more space. Starbase not added: %s\n", starbaseStr);
                }       
            } else
                  printf("ERROR in input. Starbase not added: %s\n", starbaseStr);            

        } 
        else if (option == STARBASE_MENU_COPY) {
            getStarbases(*appData, &starbaseTable);
            
            if (starbaseTable.nStarbases > 0) {
                printStarbaseTable(starbaseTable);
                /* Ask the number of the register to be copied */
                printf("Enter the number of the starbase to copy:\n");
                pStarbase=getOption(starbaseTable.nStarbases)-1;
                starbaseCpy(&newStarbase, starbaseTable.table[pStarbase]);
                starbaseAssignId(&newStarbase, (tStarbaseId)(starbaseTable.nStarbases+1));
                starbaseTableAdd(&appData->starbases, newStarbase, &retVal);
                getStarbaseStr(newStarbase, MAX_LINE, starbaseStr);
                if (retVal == OK)
                     printf("Starbase copied and added: %s\n", starbaseStr);
                else 
                        printf("ERROR: Not enough space to store the copied starbase\n"); 
            }
            else
                printf("No starbases\n");
         }
         else if (option == STARBASE_MENU_OCCUPATION) {
             getStarbases(*appData, &starbaseTable);
             if (starbaseTable.nStarbases > 0) {
                 printStarbaseTable(starbaseTable);
                 /* Ask the number of the starbase to view occupancy */
                 printf("Enter the number of the starbase:\n");
                 pos=getOption(starbaseTable.nStarbases)-1;
                 printf("Starbase occupation: %d\n", starbaseOccupation(starbaseTable.table[pos]));
             }
            else
                printf("No starbases\n");
         } 
         else if (option == STARBASE_MENU_FILTER_BY_SECTOR) {
             
             if (appData->starbases.nStarbases > 0) {
             
                 printf("Enter the number of the sector:\n");
                 scanf("%d",&number);
                 starbaseTableFilterBySector(appData->starbases, (tSectorId)number, &starbaseTable);
                 if (starbaseTable.nStarbases > 0){
                     /* Print the starbases */			
                     printStarbaseTable(starbaseTable);	
                 } else	
                     printf("No starbases in sector: %d\n", number);
             }
             else
                printf("No starbases\n");
            
         } 
         else if (option == STARBASE_MENU_ORDER_BY_OCCUPATION) {
             
             if (appData->starbases.nStarbases > 0) {
                 /* Order the table of starbases  */
                 starbaseTableOrderByOccupation(&appData->starbases);
                 /* Print the starbases */			
                 printStarbaseTable(appData->starbases);	
             } else
                 printf("No starbases\n");
         }
        
        /* Show list of options and ask the user for an option */
        printStarbaseMenuOptions();
        option=getStarbaseMenuOption();
    }
}



/*********************
 **   MISSION MENU **
**********************/



void printMissionMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Mission \n");
    printf("=======================\n");
    printf("1) List missions\n");	
    printf("2) Add mission\n");	
    printf("3) Delete mission\n");	
    printf("4) Check can process mission\n");	
    printf("5) Process mission\n");	
    printf("6) Process all missions\n");	
    printf("7) Print details mission\n");	
    printf("8) Print processes missions\n");	
    printf("9) Exit\n");	
}

tMissionMenuOptions getMissionMenuOption() {
    /* Convert to the correct type */
    return (tMissionMenuOptions)(getOption(9)-1);
}

void missionMenu(tAppData *appData) 
{
    tError retVal;
    tMissionMenuOptions option;

    tMissionTable missionTable;
    tMission newMission, missionAux;
    tStarbaseTable starbaseTable, starbaseTableAux;
    char missionStr[MAX_LINE];
    int pos,i;
    
    /* Start the menu */
    /* Show list of options and ask the user for an option */
    printMissionMenuOptions();
    option=getMissionMenuOption();
    
    while(option!=MISSION_MENU_EXIT)
    {
         /* Do the action for the given option */
         if (option == MISSION_MENU_LIST) {
            getMissions(*appData, &missionTable);			
            printMissionTable(missionTable);	
         } else if (option == MISSION_MENU_ADD) {
               readMission(&newMission, &retVal);
               getMissionStr(newMission, MAX_LINE, missionStr);
               if(retVal==OK) {
                  addMission(appData, newMission, &retVal);
                  if(retVal==OK){
                      printf("Mission added: %s\n", missionStr);
                  } else if(retVal==ERR_DUPLICATED_ENTRY) {
                              printf("Duplicated mission identifier. Mission not added: %s\n", missionStr);
                          } else {
                                 printf("No more space. Mission not added: %s\n", missionStr);
                            }
               } else {
                      printf("Error in input. Mission not added: \n%s\n", missionStr);
               }          
         } else if (option == MISSION_MENU_DEL) {
              getMissions(*appData, &missionTable);
              /* Print the missions */			
              printMissionTable(missionTable);	

              if (missionTable.nMissions > 0) {
                  /* Ask the number of the register to be removed */
                  printf("Enter the number of the mission to delete:\n");
                  pos=getOption(missionTable.nMissions);
                  removeMission(appData, pos-1, &retVal);
                  if(retVal==ERR_MISSION_ASSIGNED){
                      printf("Mission with ships assigned. Mission was not removed.\n");
                  } else {
                      printf("Mission removed.\n");
                  }
              } else
                  printf("No missions\n");

         } else if (option == MISSION_MENU_CAN_PROCESS) {
              getMissions(*appData, &missionTable);
              /* Print the missions */			
              printMissionTable(missionTable);	

              if (missionTable.nMissions > 0) {
                  /* Ask the number of the register to test */
                  printf("Enter the number of the mission to test:\n");
                  pos=getOption(missionTable.nMissions);
                  getStarbases(*appData, &starbaseTable);
                  
                  /* Copy source data to avoid mission and starbase data lost */
                  missionCpy(&missionAux, missionTable.table[pos-1]);
                  starbaseTableCpy(&starbaseTableAux, starbaseTable);
                  
                  processMission(&missionAux, &starbaseTableAux, &retVal);
            
                  if(retVal==ERR_CANNOT_PROCESS_MISSION){
                      printf("No ships enough in sector. Mission cannot be processed \n");
                  } else {
                      printf("Mission can be processed.\n");
                  }
              } else
                  printf("No missions\n");

         } else if (option == MISSION_MENU_PROCESS_MISSION) {
              getMissions(*appData, &missionTable);
              /* Print the missions */			
              printMissionTable(missionTable);	

              if (missionTable.nMissions > 0) {
                  /* Ask the number of the register to test */
                  printf("Enter the number of the mission to process:\n");
                  pos=getOption(missionTable.nMissions);
                  getStarbases(*appData, &starbaseTable);
                  
                  /* Copy source data to avoid mission cannot be processed */
                  missionCpy(&missionAux, missionTable.table[pos-1]);
                  starbaseTableCpy(&starbaseTableAux, starbaseTable);

                  processMission(&missionAux, &starbaseTableAux, &retVal);
            
                  if(retVal==OK){
                      /* update app info */
                      missionCpy(&appData->missions.table[pos-1], missionAux);
                      starbaseTableCpy(&appData->starbases, starbaseTableAux);
                      printf("Mission processed.\n");
                  } else {
                      if (retVal==ERR_MISSION_ALREADY_PROCESSED){
                          printf("Mission already processed.\n");
                      } else {
                          printf("Mission cannot be processed.\n");
                      
                      }
                  }
              } else
                  printf("No missions\n");

         } else if (option == MISSION_MENU_PROCESS_ALL) {

              if (appData->missions.nMissions > 0) {
                  
                  processAllMissions(&appData->missions, &appData->starbases, &retVal);
            
                  if(retVal==OK){
                      printf("All missions processed.\n");
                  } else {
                      printf("Some missions cannot be processed.\n");
                  }
              } else
                  printf("No missions\n");

         } else if (option == MISSION_MENU_PRINT) {
              getMissions(*appData, &missionTable);
              /* Print the missions */			
              printMissionTable(missionTable);	

              if (missionTable.nMissions > 0) {
                  /* Ask the number of the register to show details */
                  printf("Enter the number of the mission to print:\n");
                  pos=getOption(missionTable.nMissions);

                  getStarbases(*appData, &starbaseTable);
                  printMissionInfo(missionTable.table[pos-1], starbaseTable); 

              } else
                  printf("No missions\n");

         } else if (option == MISSION_MENU_PRINT_ALL) {
              getMissions(*appData, &missionTable);
              /* Print the missions */			

              if (missionTable.nMissions > 0) {

                  getStarbases(*appData, &starbaseTable);
                  for (i=0; i < missionTable.nMissions ; i++){

                      printMissionInfo(missionTable.table[i], starbaseTable); 
                  }
              } else
                  printf("No missions\n");
         }        
        /* Show list of options and ask the user for an option */
        printMissionMenuOptions();
        option=getMissionMenuOption();
    }
}

/******************
 **   STAT MENU **
******************/
void printStatMenuOptions() {
    /* Show menu options */
    printf("=======================\n");
    printf(" Statistics \n");
    printf("=======================\n");
    printf("1) Get starbases over occupation\n");	
    printf("2) Get average occupation in a sector\n");	
    printf("3) Get ships by ship type\n");	
    printf("4) Exit\n");	
}

tStatMenuOptions getStatMenuOption() {
    /* Convert to the correct type */
    return (tStatMenuOptions)(getOption(4)-1);
}

void statMenu(tAppData *appData) 
{
    tStatMenuOptions option;
    float minPercent, avgOccupation;
    tStarbaseTable starbaseTable, resultStarbaseTable;
    int shipType, sector;
    tShipTable shipTable;

    /* Start the menu */
    /* Show list of options and ask the user for an option */
    printStatMenuOptions();
    option=getStatMenuOption();
    
    while(option!=STAT_MENU_EXIT)
    {
        /* Do the action for the given option */
        if (option == STAT_MENU_OVER_OCCUPATION) {
        
            if (appData->starbases.nStarbases > 0) {
             
                printf("Enter the mínimum percentage of occupation:\n");
                 scanf("%f",&minPercent);
                 starbaseTableFilterByOccupation(appData->starbases, minPercent, &starbaseTable);
                 if (starbaseTable.nStarbases > 0){
                     /* Print the starbases */			
                     printStarbaseTable(starbaseTable);	
                 } else	
                     printf("No starbases over %f percent of occupation\n", minPercent);
             }
             else
                printf("No starbases\n");
            
        } else if (option == STAT_MENU_AVERAGE_OCCUPATION_IN_SECTOR ) {

            if (appData->starbases.nStarbases > 0) {

                printf("Enter the sector to calculate occupation:\n");
                 scanf("%d",&sector);      
                 starbaseTableFilterBySector(appData->starbases, (tSectorId)sector, &resultStarbaseTable);       
                 avgOccupation = starbaseTableAvgOccupation(resultStarbaseTable);
                 printf("The average occupation of sector %d is %.2f\n", sector, avgOccupation);	
             }
             else
                printf("No starbases\n");
            
        } else if (option == STAT_MENU_SELECT_SHIPS) {
            
            if (appData->ships.nShips > 0) {
                printf("Enter the ship type (1-CARRIER, 2-TRANSPORT, 3-FIGHTER, 4-MEDICAL, 5-EXPLORER): \n");
                scanf("%d", &shipType); 
                shipTableSelectShips(appData->ships, (tShipType)shipType, &shipTable);                 
                if (shipTable.nShips > 0){
                     /* Print the starbases */			
                     printShipTable(shipTable);	
                 } else	
                     printf("No ships of type = %d\n", shipType);

            }
            else
               printf("No ships\n");            
        }

        /* Show list of options and ask the user for an option */
        printStatMenuOptions();
        option=getStatMenuOption();
    }
}
