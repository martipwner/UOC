#include <stdio.h>
#include <string.h>
#include <math.h>

#include "data.h"
#include "test.h"
#include "ship.h"
#include "starbase.h"
#include "mission.h"
#include "api.h"
#include "menu.h"

/* global missions list */
char *missionsList[] = { 
"1 1 15 3 3 3 3 3 0",
"2 2 10 1 1 6 1 1 0",
"3 1 5 1 1 1 1 1 0",
"4 3 5 0 2 1 1 1 0"
};

/* global ships list */
char *shipsList[] = {
"1 1 2 GALACTIC 1 500.00 300",
"2 1 3 IMPERIAL_ESCORT 1 500.00 300",
"3 1 2 DEFENDER 1 500.00 300",
"4 1 3 ENDURANCE 1 500.00 300",
"5 1 2 GALACTIC 1 500.00 300",
"6 2 3 SHUTTLE 1 150.00 100",
"7 2 2 SHUTTLE 1 150.00 100",
"8 2 3 SHUTTLE 1 150.00 100",
"9 2 4 SHUTTLE 1 150.00 100",
"10 2 3 SHUTTLE 1 150.00 100",
"11 3 2 TIE_STRIKER 1 100.00 3",
"12 3 4 TIE_FIGHTER 1 100.00 1",
"13 3 2 TIE_BOMBER 1 100.00 2",
"14 3 4 TIE_INTERCEPTOR 1 100.00 3",
"15 3 6 TIE_BOMBER 1 100.00 2",
"16 3 6 TIE_FIGHTER 1 100.00 1",
"17 4 2 PARAMEDIC 1 50.00 5",
"18 4 3 PARAMEDIC 1 50.00 5",
"19 4 2 PARAMEDIC 1 50.00 5",
"20 4 3 PARAMEDIC 1 50.00 5",
"21 4 2 PARAMEDIC 1 50.00 5",
"22 5 6 CRUISER 1 1000.00 200",
"23 5 7 CRUISER 1 1000.00 200",
"24 5 8 CRUISER 1 1000.00 200",
"25 5 6 CRUISER 1 1000.00 200",
"26 5 8 CRUISER 1 1000.00 200",
"27 3 2 TIE_STRIKER 1 100.00 3",
"28 3 4 TIE_FIGHTER 1 100.00 1",
"29 3 2 TIE_BOMBER 1 100.00 2",
"30 3 4 TIE_INTERCEPTOR 1 100.00 3",
"31 3 6 TIE_BOMBER 1 100.00 2",
"32 3 6 TIE_FIGHTER 1 100.00 1",
"33 4 2 PARAMEDIC 1 50.00 5",
"34 4 3 PARAMEDIC 1 50.00 5",
"35 1 10 VENATOR 1 19500.00 1000",
"36 2 15 SENTINEL 1 10300.00 4000",
"37 2 14 SENTINEL 1 10300.00 4000",
"38 3 4 CORVETTE 1 400.00 5",
"39 3 4 CORVETTE 1 400.00 5",
"40 3 4 CORVETTE 1 400.00 5",
"41 3 4 CORVETTE 1 400.00 5",
"42 3 4 CORVETTE 1 400.00 5",
"43 3 4 CORVETTE 1 400.00 5",
"44 3 4 CORVETTE 1 400.00 5",
"45 3 4 CORVETTE 1 400.00 5",
"46 3 4 CORVETTE 1 400.00 5",
"47 3 2 TIE_STRIKER 1 100.00 3",
"48 3 4 TIE_FIGHTER 1 100.00 1",
"49 3 2 TIE_BOMBER 1 100.00 2",
"50 3 4 TIE_INTERCEPTOR 1 100.00 3",
"51 3 6 TIE_BOMBER 1 100.00 2",
"52 3 6 TIE_FIGHTER 1 100.00 1",
"53 2 3 TIRIDIUM 1 200.00 3",
"54 2 3 TIRIDIUM 1 200.00 3",
"55 2 3 TIRIDIUM 1 200.00 3",
"56 5 8 RAIDER 1 20000.00 100",
"57 5 8 RAIDER 1 20000.00 100",
"58 4 9 SCIENCE 1 4000.00 20",
"59 4 9 SCIENCE 1 4000.00 20",
"60 4 9 SCIENCE 1 4000.00 20"
};


/* action to read a test starbase */
void readTestStarbase( tStarbase *starbase )
{
    getStarbaseObject(STARBASE3, starbase);
    getLevelObject(LEVEL11, &starbase->levels.table[0]);
    getHangarObject(HANGAR111, &starbase->levels.table[0].hangars.table[0]);
    getHangarObject(HANGAR112, &starbase->levels.table[0].hangars.table[1]);
    getHangarObject(HANGAR113, &starbase->levels.table[0].hangars.table[2]);
    getLevelObject(LEVEL12, &starbase->levels.table[1]);
    getHangarObject(HANGAR121, &starbase->levels.table[1].hangars.table[0]);
    getHangarObject(HANGAR122, &starbase->levels.table[1].hangars.table[1]);
    getLevelObject(LEVEL13, &starbase->levels.table[2]);
    getHangarObject(HANGAR131, &starbase->levels.table[2].hangars.table[0]);
    getHangarObject(HANGAR132, &starbase->levels.table[2].hangars.table[1]);
    getHangarObject(HANGAR133, &starbase->levels.table[2].hangars.table[2]);
    getHangarObject(HANGAR134, &starbase->levels.table[2].hangars.table[3]);

}


/* action to read a test starbase in the first position of a table */
void readTestStarbases( tStarbaseTable *starbases )
{
    starbaseTableInit(starbases);

    readTestStarbase( &starbases->table[0] );
    starbases->nStarbases= 1;
}

/* action to read test ships */
void readTestShips( tShipTable *ships )
{
    tShip ship;
    tError retVal;
    int i;
    
    shipTableInit(ships);
    
    for (i= 0; i < MAX_TEST_SHIPS; i++) {
        getShipObject(shipsList[i], &ship);
        shipTableAdd(ships, ship, &retVal);
    } 
}

/* action to read test missions */
void readTestMissions( tMissionTable *missions )
{
    tMission mission;
    tError retVal;
    int i;
    
    missionTableInit(missions);
    
    for (i= 0; i < MAX_TEST_MISSIONS; i++) {
        getMissionObject(missionsList[i], &mission);
        missionTableAdd(missions, mission,&retVal);
    } 
}

/* start DSLab */
void addLine(tLinesTable *lines, char line[]) {
    strcpy(lines->lines[lines->nLines], line);
    lines->nLines++;
}

void printLines(int mode, tLinesTable lines, char *dsLabOutput) {
    for (int i=0; i<lines.nLines; i++) {
       if (mode==TEST_MODE) {
           printf("%s", lines.lines[i]);
       } else {
           strcat(dsLabOutput, lines.lines[i]);
       }
    }
}
/* end DSLab */

/* action to execute all the tests */
void runTests(int mode) 
{
    int passedTest= 0;
    int totalTest= 0;
    float percent= 0.0;
    /* start DSLab */
    tLinesTable lines;
    char summary[MAX_CHARS];
    char dsLabOutput[MAX_CHARS * MAX_LINES];
    lines.nLines = 0;
    /* end DSLab */

    addLine(&lines, "===============================================\n");
    addLine(&lines, "====       PRACTICAL ACTIVITY TESTS        ====\n");
    addLine(&lines, "===============================================\n");

    testCpyCmp(&totalTest, &passedTest, mode, &lines);
    testTableOperations(&totalTest, &passedTest, mode, &lines);
    testSortAndFilters(&totalTest, &passedTest, mode, &lines);
    testMissions(&totalTest, &passedTest, mode, &lines);
    testStatistics(&totalTest, &passedTest, mode, &lines);
    
    if (totalTest>0)
        percent= (float)passedTest/totalTest*100.0;
    else {
        percent= 0.0;
    }

    addLine(&lines, "===================================\n");
    addLine(&lines, "====       TEST SUMMARY        ====\n");
    addLine(&lines, "===================================\n");
    sprintf(summary, "\tPR: Passed %d of %d [%0.2f%%]\n", passedTest, totalTest, percent);
    addLine(&lines, summary);
    addLine(&lines, "===================================\n");
    
    printLines(mode, lines, dsLabOutput);  
}

/* action to execute the copy & comparison tests */
void testCpyCmp(int *totalTest, int *passedTest, int mode, tLinesTable *lines) 
{
    tStarbase starbase1, starbase2, starbase3;
    tHangar hangar1, hangar2, hangar3;

    /* Init */
    starbaseInit(&starbase1);
    starbaseInit(&starbase2);
    hangarInit(&hangar1);
    hangarInit(&hangar2);

    /* Read the starbase */
    readTestStarbase(&starbase3);

    addLine(lines, "==================================\n");
    addLine(lines, " COPY AND COMPARE (Exercise 2)\n");
    addLine(lines, "==================================\n");

    addLine(lines, "\nTest 2.1: Copy empty zones\n");

    (*totalTest)++;

    hangarCpy(&hangar2, hangar1);
  
    if (hangar2.id == hangar1.id &&
        hangar2.isAvailable == hangar1.isAvailable &&
        hangar2.hangarType == hangar1.hangarType &&
        hangar2.hangarShipType == hangar1.hangarShipType &&
        hangar2.nShips == hangar1.nShips)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        addLine(lines, "\n\t-> FAIL (different values found after copying null hangars)\n");
    }

    addLine(lines, "\nTest 2.2: Copy hangars (ships not checked)\n");
    (*totalTest)++;

    hangarCpy(&hangar3, starbase3.levels.table[0].hangars.table[0]);
  
    if (hangar3.id == starbase3.levels.table[0].hangars.table[0].id &&
        hangar3.isAvailable == starbase3.levels.table[0].hangars.table[0].isAvailable &&
        hangar3.hangarType == starbase3.levels.table[0].hangars.table[0].hangarType &&
        hangar3.hangarShipType == starbase3.levels.table[0].hangars.table[0].hangarShipType &&
        hangar3.nShips == starbase3.levels.table[0].hangars.table[0].nShips)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        addLine(lines, "\n\t-> FAIL (different values found after copying non-null hangars)\n");
    }

    addLine(lines, "\nTest 2.3: Compare empty starbases\n");
    (*totalTest)++;
    
    if (starbaseCmp(starbase1, starbase2) == 0) 
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        addLine(lines, "\n\t-> FAIL (differences found in equal empty starbases)\n");
    }
    
    addLine(lines, "\nTest 2.4: Compare non-empty starbases. Different occupation (first > second).\n");
    (*totalTest)++;

    starbaseCpy(&starbase2, starbase3);
    starbase2.levels.table[0].hangars.table[0].nShips = 10;
    
    if (starbaseCmp(starbase2, starbase3) > 0) 
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
    addLine(lines, "\n\t-> FAIL (First starbase expected to be greater than second one)\n");
    }
    
    addLine(lines, "\nTest 2.5: Compare non-empty starbases. Different levels (first < second).\n");
    (*totalTest)++;
        
    starbaseCpy(&starbase2, starbase3);
    starbase2.levels.nLevels = 10;
    starbase2.levels.table[3].hangars.nHangars = 0;
    starbase2.levels.table[4].hangars.nHangars = 0;
    starbase2.levels.table[5].hangars.nHangars = 0;
    starbase2.levels.table[6].hangars.nHangars = 0;
    starbase2.levels.table[7].hangars.nHangars = 0;
    starbase2.levels.table[8].hangars.nHangars = 0;
    starbase2.levels.table[9].hangars.nHangars = 0;


    if (starbaseCmp(starbase3, starbase2) < 0) 
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        addLine(lines, "\n\t-> FAIL (Second starbase expected to be greater than first one)\n");
    }
    
    addLine(lines, "\nTest 2.6: Compare non-empty starbases. Different number of operative hangars (first > second).\n");
    (*totalTest)++;
    
    starbaseCpy(&starbase2, starbase3);
    starbase2.levels.table[2].hangars.table[0].isAvailable = true;
    
    if (starbaseCmp(starbase2, starbase3) > 0) 
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        addLine(lines, "\n\t-> FAIL (First starbase expected to be greater than second one)\n");
    }
    
}

/* action to execute the table operations tests */
void testTableOperations(int *totalTest, int *passedTest, int mode, tLinesTable *lines) 
{
    tStarbase starbase1, starbase2;
    
    /* Init */
    starbaseInit(&starbase2);
    /* Read the starbase */
    readTestStarbase(&starbase1);


    addLine(lines, "======================================\n");
    addLine(lines, "    TABLE OPERATIONS (Exercise 3)\n");
    addLine(lines, "======================================\n");

    addLine(lines, "\nTest 3.1: Check on empty starbase table\n");
    (*totalTest)++;

  
    if (!isShipInStarbase(starbase2,(tShipId)1))
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        addLine(lines, "\n\t-> FAIL (Expected ship not found in empty starbase)\n");
    }
    
    addLine(lines, "\nTest 3.2: Check on starbase with many ships\n");
    (*totalTest)++;
    
  
    if (isShipInStarbase(starbase1,(tShipId)57))
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        addLine(lines, "\n\t-> FAIL (Expected ship found in starbase, but returned false)\n");
    }
    
    addLine(lines, "\nTest 3.3: Check on non-empty starbase. No ship \n");
    (*totalTest)++;
    
  
    if (!isShipInStarbase(starbase1,(tShipId)15))
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        addLine(lines, "\n\t-> FAIL (Expected: ship not found, but returned true)\n");
    }
    
}

/* action to execute the sort & filtering tests */
void testSortAndFilters(int *totalTest, int *passedTest, int mode, tLinesTable *lines) 
{	
    tStarbaseTable starbaseTab, starbaseResTab;
    tStarbase starbase1;
    tMissionTable missionTab;
    tMission mission1;
    tError retVal;
    /* start DSLab */
    char lineAux[MAX_CHARS];
    /* end DSLab */

    /* Init */
    starbaseTableInit(&starbaseTab);

    
    addLine(lines, "======================================\n");
    addLine(lines, " SORT AND FILTERS (Exercise 5)\n");
    addLine(lines, "======================================\n");

    addLine(lines, "\nTest 5.1: Starbases of sector. Check on empty table.\n");
    (*totalTest)++;
  
    starbaseTableFilterBySector(starbaseTab, (tSectorId)15, &starbaseResTab);
    
    if (starbaseResTab.nStarbases == 0)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected empty result table, but returns %d elements)\n", 
            starbaseResTab.nStarbases);
        addLine(lines, lineAux);
    }
    
    addLine(lines, "\nTest 5.2: Starbases of sector. Check on non-empty table. Sector empty\n");
    (*totalTest)++;
    
    /* Read the starbase */
    readTestStarbases(&starbaseTab);
    starbaseCpy(&starbase1, starbaseTab.table[0]);
    getStarbaseObject(STARBASE2, &starbase1);
    starbaseTableAdd(&starbaseTab, starbase1, &retVal);
    starbaseCpy(&starbase1, starbaseTab.table[0]);
    getStarbaseObject(STARBASE1, &starbase1);
    getLevelObject(LEVEL14, &starbase1.levels.table[3]);
    getHangarObject(HANGAR141, &starbase1.levels.table[3].hangars.table[0]);
    starbaseTableAdd(&starbaseTab, starbase1, &retVal);

    starbaseTableFilterBySector(starbaseTab, (tSectorId)17, &starbaseResTab);

    if (starbaseResTab.nStarbases == 0)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected empty result table, returned table with %d starbases)\n",
            starbaseResTab.nStarbases);
        addLine(lines, lineAux);
    }

    addLine(lines, "\nTest 5.3: Starbases of sector. Check on non-empty table. Sector non-empty\n");
    (*totalTest)++;


    starbaseTableFilterBySector(starbaseTab, (tSectorId)13, &starbaseResTab);

    if (starbaseResTab.nStarbases == 2 && 
        strcmpUpper(starbaseResTab.table[0].baseName, "RESURGENT") == 0  && 
        strcmpUpper(starbaseResTab.table[1].baseName, "DEATH_STAR_II") == 0)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else if (starbaseResTab.nStarbases != 2)
           {
             sprintf(lineAux, "\n\t-> FAIL (Expected %d starbases and returned %d)\n", 
                2, starbaseResTab.nStarbases);
             addLine(lines, lineAux);
           } else	
            {
            sprintf(lineAux, "\n\t-> FAIL (Expected starbases %s and %s and returned %s and %s)\n", 
                "RESURGENT", "DEATH_STAR_II", 
                starbaseResTab.table[0].baseName, starbaseResTab.table[1].baseName );
            addLine(lines, lineAux);
            }
    
    addLine(lines, "\nTest 5.4: Order starbases by occupation. Check on non-empty table. \n");
    (*totalTest)++;
  
    starbaseTableOrderByOccupation(&starbaseTab);

    if (strcmpUpper(starbaseTab.table[0].baseName, "RESURGENT") == 0 && 
        strcmpUpper(starbaseTab.table[1].baseName, "STARKILLER") == 0 && 
        strcmpUpper(starbaseTab.table[2].baseName, "DEATH_STAR_II") == 0 )
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected order %s %s %s and returned %s %s %s)\n", 
                "RESURGENT", "STARKILLER", "DEATH_STAR_II", 
                starbaseTab.table[0].baseName,starbaseTab.table[1].baseName,
                starbaseTab.table[2].baseName);
        addLine(lines, lineAux);
    }
    addLine(lines, "\nTest 5.5: Order starbases by occupation. Check on non-empty table. \n");
    (*totalTest)++;
  
    starbaseCpy(&starbase1, starbaseTab.table[0]);
    starbaseCpy(&starbaseTab.table[0], starbaseTab.table[2]);
    starbaseCpy(&starbaseTab.table[2], starbase1);

    starbaseTableOrderByOccupation(&starbaseTab);

    if (strcmpUpper(starbaseTab.table[0].baseName, "STARKILLER") == 0 && 
        strcmpUpper(starbaseTab.table[1].baseName, "RESURGENT") == 0 && 
        strcmpUpper(starbaseTab.table[2].baseName, "DEATH_STAR_II") == 0 )
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected order %s %s %s and returned %s %s %s)\n", 
                "STARKILLER", "RESURGENT", "DEATH_STAR_II", 
                starbaseTab.table[0].baseName,starbaseTab.table[1].baseName,
                starbaseTab.table[2].baseName);
        addLine(lines, lineAux);
    }
    
    
    addLine(lines, "\nTest 5.6: Sort missions. Diferent start starbases\n");
    (*totalTest)++;
      
    missionTableInit(&missionTab);
    getMissionObject(MISSION1, &mission1);
    missionTableAdd(&missionTab, mission1, &retVal);
    getMissionObject(MISSION2, &mission1);
    missionTableAdd(&missionTab, mission1, &retVal);
    getMissionObject(MISSION3, &mission1);
    missionTableAdd(&missionTab, mission1, &retVal);
    getMissionObject(MISSION4, &mission1);
    missionTableAdd(&missionTab, mission1, &retVal);
        
    missionTableSortByShips(&missionTab);

    if (missionTab.table[0].id == 3 && missionTab.table[1].id == 1 &&
        missionTab.table[2].id == 2 && missionTab.table[3].id == 4 )
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected order: 3,1,2,4  Returned order: %d,%d,%d,%d)\n",
            missionTab.table[0].id, missionTab.table[1].id, 
            missionTab.table[2].id, missionTab.table[3].id);
        addLine(lines, lineAux);
    }
    
    addLine(lines, "\nTest 5.7: Sort missions. Number fighters\n");
    (*totalTest)++;
          
    missionTab.table[0].shipsNeed = 15;
    missionTableSortByShips(&missionTab);

    if (missionTab.table[0].id == 1 && missionTab.table[1].id == 3 &&
        missionTab.table[2].id == 2 && missionTab.table[3].id == 4 )
     {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected order: 1,3,2,4  Returned order: %d,%d,%d,%d)\n",
            missionTab.table[0].id, missionTab.table[1].id, 
            missionTab.table[2].id, missionTab.table[3].id);
        addLine(lines, lineAux);
    }
    
}

/* action to execute the statistics tests */
void testStatistics(int *totalTest, int *passedTest, int mode, tLinesTable *lines) 
{	
    tShipTable ships, resultShips;
    tStarbaseTable starbaseTable, resultStarbaseTable;
    tError retVal;
    float avg=0.0;
    tAppData app;
    /* start DSLab */
    char lineAux[MAX_CHARS];
    /* end DSLab */


    /* Init */    
    appDataInit(&app);

    /* Read data */    

    appDataLoad(&app, &retVal);   
    /* Init */    
    starbaseTableInit(&starbaseTable);

    addLine(lines, "======================================\n");
    addLine(lines, " STATISTICS (Exercise 8)\n");
    addLine(lines, "======================================\n");

    addLine(lines, "\nTest 8.1: Search for occupation starbases in empty table.\n");
    (*totalTest)++;

    starbaseTableFilterByOccupation(starbaseTable, 50.0, &resultStarbaseTable);

    if (resultStarbaseTable.nStarbases == 0)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected empty result table, returned table with %d starbases)\n", 
            resultStarbaseTable.nStarbases);
        addLine(lines, lineAux);
    }
    
    addLine(lines, "\nTest 8.2: Search for occupation starbases in non-empty table.\n");
    (*totalTest)++;
 
    starbaseTableFilterByOccupation(app.starbases, 10.0, &resultStarbaseTable);

    if (resultStarbaseTable.nStarbases == 1 && resultStarbaseTable.table[0].id == 2) 
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        if (resultStarbaseTable.nStarbases != 1) {
            sprintf(lineAux, "\n\t-> FAIL (Expected result %d starbases, returned %d starbases)\n", 
                1, resultStarbaseTable.nStarbases);
            addLine(lines, lineAux);
        }
        else
            addLine(lines, "\n\t-> FAIL (Returned starbases not correct)\n");
    }

    
    addLine(lines, "\nTest 8.3: Get average occupation in a sector with no starbases.\n");
    (*totalTest)++;

    starbaseTableFilterBySector(starbaseTable, (tSectorId)17, &resultStarbaseTable);  
    avg = starbaseTableAvgOccupation(resultStarbaseTable);
    if (avg < 0.1)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected %.2f, returned %.2f)\n", 
            0.0, avg);
        addLine(lines, lineAux);
    }
    
    addLine(lines, "\nTest 8.4: Get average occupation in a sector with several starbases.\n");
    (*totalTest)++;
  
    starbaseTableFilterBySector(starbaseTable, (tSectorId)25, &resultStarbaseTable);
    avg = starbaseTableAvgOccupation(app.starbases);
    
    if (fabs(avg-8.67) < 0.1)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (Expected %.2f, returned %.2f)\n", 37.1, avg);
        addLine(lines, lineAux);
    }
    
    addLine(lines, "\nTest 8.5: Select ships in empty table.\n");
    (*totalTest)++;
    
    shipTableInit(&ships);    
    shipTableSelectShips(ships, FIGHTER, &resultShips);
    
    if (resultShips.nShips == 0)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        printf("\n\t-> FAIL (Expected empty ships list, returned %d ships)\n", resultShips.nShips);
        addLine(lines, lineAux);
    }

    addLine(lines, "\nTest 8.6: Select ships type FIGHTER in non-empty table\n");
    (*totalTest)++;

    readTestShips(&ships);
    shipTableSelectShips(ships, FIGHTER, &resultShips);

    if (resultShips.nShips == 27)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected %d ships in list, returned %d)\n", 
            27, resultShips.nShips);
        addLine(lines, lineAux);
    }

    addLine(lines, "\nTest 8.7: Select ships type CARRIER in non-empty table.\n");
    (*totalTest)++;

    
    shipTableSelectShips(ships, CARRIER, &resultShips);

    if (resultShips.nShips == 6)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected %d ships in list, returned %d)\n", 
            6, resultShips.nShips);
        addLine(lines, lineAux);
    }
    
    addLine(lines, "\nTest 8.8: Select ships type EXPLORER in non-empty table.\n");
    (*totalTest)++;


    shipTableSelectShips(ships, EXPLORER, &resultShips);

    if (resultShips.nShips == 7)
    {
       addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
        sprintf(lineAux, "\n\t-> FAIL (Expected %d ships in list, returned %d)\n", 
            7, resultShips.nShips);
        addLine(lines, lineAux);
    }
    

}

/* action to execute the missions tests */
void testMissions( int *totalTest, int *passedTest, int mode, tLinesTable *lines) 
{
    tAppData app;
    tError retVal;
    bool allInOne, allInTwo;
    int i;
    tMission missionAux;
    tStarbaseTable starbaseTableAux;
    /* start DSLab */
    char lineAux[MAX_CHARS];
    /* end DSLab */

    /* Init */    
    appDataInit(&app);

    /* Read data */    

    appDataLoad(&app, &retVal);

    addLine(lines, "======================================\n");
    addLine(lines, " MISSIONS (Exercise 6)\n");
    addLine(lines, "======================================\n");

    addLine(lines, "\nTest 6.1: Process mission with all ships in one starbase.\n");
    (*totalTest)++;

    /* Copy source data to avoid mission cannot be processed */
    missionCpy(&missionAux, app.missions.table[0]);
    starbaseTableCpy(&starbaseTableAux, app.starbases);
    
    processMission(&missionAux, &starbaseTableAux, &retVal);

    if (retVal == OK){
        /* update app info */
        missionCpy(&app.missions.table[0], missionAux);
        starbaseTableCpy(&app.starbases, starbaseTableAux);
        
        allInOne = true;
        for (i=0; i<app.missions.table[0].assignedShips; i++){
            allInOne = allInOne && app.missions.table[0].assignedShipsInfo[i].assignedStarbase == (tStarbaseId)1;
        } 
        if (allInOne)    
        {
          addLine(lines, "\n\t-> OK\n");
             (*passedTest)++;
        } else {
               addLine(lines, "\n\t-> FAIL (Expected all ships assigned from starbase with id = 1)\n");
        }
    }
    else {
         sprintf(lineAux, "\n\t-> FAIL (Expected mission can be processed, but returned error code: %d)\n", 
            (int)retVal);
         addLine(lines, lineAux);
    }


    addLine(lines, "\nTest 6.2: Process mission with ships in more than one starbase.\n");
    (*totalTest)++;

    /* Copy source data to avoid mission cannot be processed */
    missionCpy(&missionAux, app.missions.table[1]);
    starbaseTableCpy(&starbaseTableAux, app.starbases);
    
    processMission(&missionAux, &starbaseTableAux, &retVal);

    if (retVal == OK){
        /* update app info */
        missionCpy(&app.missions.table[1], missionAux);
        starbaseTableCpy(&app.starbases, starbaseTableAux);
       
        allInTwo = true;
        for (i=0; i<app.missions.table[1].assignedShips; i++){
            allInTwo = allInTwo && (app.missions.table[1].assignedShipsInfo[i].assignedStarbase == (tStarbaseId)1 || 
                                    app.missions.table[1].assignedShipsInfo[i].assignedStarbase == (tStarbaseId)2);
        } 
        if (allInTwo)    
        {
          addLine(lines, "\n\t-> OK\n");
          (*passedTest)++;
        } else {
               addLine(lines, "\n\t-> FAIL (Expected all ships assigned from starbase with id = 1 or id = 2)\n");
        }
    }
    else {
         sprintf(lineAux, "\n\t-> FAIL (Expected mission can be processed, but returned error code: %d)\n", 
            (tError)retVal);
         addLine(lines, lineAux);
    }


    addLine(lines, "\nTest 6.3: Process mission with not enough ships in sector.\n");
    (*totalTest)++;

        processMission(&app.missions.table[3], &app.starbases, &retVal);

    if (retVal == ERR_CANNOT_PROCESS_MISSION){
          addLine(lines, "\n\t-> OK\n");
        (*passedTest)++;
    } else {
         sprintf(lineAux, "\n\t-> FAIL (Expected mission cannot be processed, but returned error code: %d)\n", 
            (tError)retVal);
         addLine(lines, lineAux);
    }
  
  
}
