#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
int getOption(int numOptions);

/* Define the main menu options type */
typedef enum {  MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_SHIP, 
                MAIN_MENU_STARBASE, MAIN_MENU_MISSION, MAIN_MENU_STAT,
                MAIN_MENU_EXIT} tMainMenuOptions;

/* Define the ships management menu options type */
typedef enum {  SHIP_MENU_LIST, SHIP_MENU_ADD, SHIP_MENU_DEL, 
                SHIP_MENU_CLEAR_ALL,
                SHIP_MENU_EXIT} tShipMenuOptions;
    
/* Define the missions management menu options type */
typedef enum {  MISSION_MENU_LIST, 
                MISSION_MENU_ADD, 
                MISSION_MENU_DEL,
                MISSION_MENU_CAN_PROCESS, 
                MISSION_MENU_PROCESS_MISSION, 
                MISSION_MENU_PROCESS_ALL, 
                MISSION_MENU_PRINT, 
                MISSION_MENU_PRINT_ALL, 
                MISSION_MENU_EXIT } tMissionMenuOptions;
                
/* Define the starbases management menu options type */
typedef enum {  STARBASE_MENU_LIST, 
                STARBASE_MENU_INFO_STARBASE, 
                STARBASE_MENU_ADD, 
                STARBASE_MENU_COPY, 
                STARBASE_MENU_OCCUPATION, 
                STARBASE_MENU_FILTER_BY_SECTOR, 
                STARBASE_MENU_ORDER_BY_OCCUPATION, 
                STARBASE_MENU_EXIT} tStarbaseMenuOptions;

/* Define the stats menu options type */
typedef enum {  STAT_MENU_OVER_OCCUPATION, 
                STAT_MENU_AVERAGE_OCCUPATION_IN_SECTOR,
                STAT_MENU_SELECT_SHIPS, 
                STAT_MENU_EXIT} tStatMenuOptions;

/* Print the main menu options */
void printMainMenuOptions();

/* Get the option for the main menu */
tMainMenuOptions getMenuOption();

/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the ship management menu options */
void printShipMenuOptions();

/* Get the option for the ship management menu */
tShipMenuOptions getShipMenuOption();

/* Perform the actions for the ship management menu */
void shipMenu(tAppData *appData);

/* Get interactive info from a ship */
void readShip(tShip *ship, tError *retVal);

/* Print ship table */
void printShipTable(tShipTable table); 

/* Print the starbases management menu options */
void printStarbaseMenuOptions();

/* Get the option for the starbases management menu */
tStarbaseMenuOptions getStarbaseMenuOption();

/* Perform the actions for the starbases management menu */
void starbaseMenu(tAppData *appData);

/* Get interactive info from a hangar */
void readHangar(tHangar *hangar, tHangarId id, tShipTable shipTable, tError *retVal);

/* Get interactive info from a hangar */
void readLevel(tLevel *level, tLevelId id, tShipTable shipTable, tError *retVal);

/* Get interactive info from a starbase */
void readStarbase(tStarbase *starbase, tShipTable shipTable, tError *retVal);

/* Initialize the table of hangars */
void hangarTableInit(tHangarTable *hangarsTable);

/* Add a new hangar to the table of hangars */
void hangarTableAdd(tHangarTable *hangarsTable, tHangar hangar, tError *retVal);

/* Initialize the table of levels */
void levelTableInit(tLevelTable *levelsTable);

/* Add a new level to the table of levels */
void levelTableAdd(tLevelTable *levelsTable, tLevel level, tError *retVal);

/* Print the missions menu options */
void printMissionMenuOptions();

/* Get the option for the mission menu */
tMissionMenuOptions getMissionMenuOption();

/* Perform the actions for the mission menu */
void missionMenu(tAppData *appData);

/* Print the stats menu options */
void printStatMenuOptions();

/* Get the option for the stats menu */
tStatMenuOptions getStatMenuOption();

/* Perform the actions for the stats menu */
void statMenu(tAppData *appData);

void printStarbaseTable(tStarbaseTable table);

void printStarbaseInfo(tStarbase starbase);