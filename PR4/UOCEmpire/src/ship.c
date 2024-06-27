#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ship.h"
    
void getShipStr(tShip ship, int maxSize, char *str) 
{
    snprintf(str,maxSize-1,"%d %d %d %s %d %0.2f %d", 
        ship.id, (int)ship.shipType, ship.shipEngines, 
        ship.model, (int)ship.isInterplanetary,
        ship.autonomy, ship.troopCapacity);
}

void getShipObject(const char *str, tShip *ship) 
{	
    tShipId id= NO_SHIP;
    int auxIsInterplanetary= 0;
    int auxShipType= 0;

    sscanf(str, "%d %d %d %s %d %f %d ", &(id), &auxShipType, 
    &ship->shipEngines, ship->model, &auxIsInterplanetary, &ship->autonomy,
    &ship->troopCapacity);
    
    ship->id = (tShipId)id;
    ship->shipType = (tShipType)auxShipType;
    ship->isInterplanetary = (bool)auxIsInterplanetary;

}


void convertToUpper( char *string )
{
    int i, len;
    char originalChar;
    
    len= strlen(string);
    for (i= 0; i < len; i++) {
        originalChar= string[i];
        if (originalChar >= 'a' && originalChar <= 'z') 
            string[i]= originalChar + 'A' - 'a';
    }
}

int strcmpUpper( char *s1, char *s2 )
{
    int result= 0;
    char string1[MAX_LINE];
    char string2[MAX_LINE];
    
    strcpy( string1, s1 );
    strcpy( string2, s2 );
    convertToUpper( string1 );
    convertToUpper( string2 );
   
    result= strcmp(string1,string2);

    return result;
}
 
int shipCmp(tShip ship1, tShip ship2) {
    
    int result = 0;

    result= strcmpUpper(ship1.model,ship2.model);
    if (result==0)
    {
        if (ship1.shipEngines > ship2.shipEngines)
            result = 1;
        else if (ship1.shipEngines < ship2.shipEngines)
                result = -1;
             else { 
                 if (ship1.isInterplanetary < ship2.isInterplanetary)
                    result = -1;
                 else if (ship1.isInterplanetary > ship2.isInterplanetary)
                      result = -1;
                      else { 
                          if (ship1.autonomy > ship2.autonomy)
                              result = 1;
                          else if (ship1.autonomy < ship2.autonomy)
                              result = -1;
                      }
             }
    }

    return result;
}
    
void shipCpy(tShip *dst, tShip src) 
{    
    dst->id = src.id;
    dst->shipType = src.shipType;
    dst->shipEngines = src.shipEngines;
    strcpy(dst->model,src.model);
    dst->isInterplanetary = src.isInterplanetary;
    dst->autonomy = src.autonomy;    
    dst->troopCapacity = src.troopCapacity;
}


void shipTableInit(tShipTable *shipTable) {
    
    shipTable->nShips=0;
}


void shipTableAdd(tShipTable *tabShip, tShip ship, tError *retVal) {

    *retVal = OK;

    /* Check if there enough space for the new ship */
    if(tabShip->nShips>=MAX_SHIPS)
        *retVal = ERR_MEMORY;

    if (*retVal == OK) {
        /* Add the new ship to the end of the table */
        shipCpy(&tabShip->table[tabShip->nShips],ship);
        tabShip->nShips++;
    }
}

int shipTableFind(tShipTable tabShip, tShipId id) {

    int idx = NO_SHIP;
    
    int i=0;
    while(i< tabShip.nShips && idx==NO_SHIP) {
        /* Check if the id is the same */
        if(tabShip.table[i].id==id) {
            idx = i;
        }
        i++;
    }
    
    return idx;
}

void shipTableDel(tShipTable *tabShip, tShip ship) 
{	
    int i;
    int pos;

    pos = shipTableFind(*tabShip,ship.id);
    if (pos!=NO_SHIP)
    {
        for(i=pos; i<tabShip->nShips-1; i++) {		
            shipCpy(&tabShip->table[i],tabShip->table[i+1]);
        }
        tabShip->nShips=tabShip->nShips-1;		
    }
}

void shipTableSave(tShipTable tabShip, const char* filename, tError *retVal) {

    *retVal = OK;
    
    FILE *fout=NULL;
    int i;
    char str[MAX_LINE];
    
    /* Open the output file */
    if((fout=fopen(filename, "w"))==0) {
        *retVal = ERR_CANNOT_WRITE;
    } else {
    
        /* Save all ships to the file */
        for(i=0;i<tabShip.nShips;i++) {
            getShipStr(tabShip.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
    }
}

void shipTableLoad(tShipTable *tabShip, const char* filename, tError *retVal) {
    
    *retVal = OK;
    
    FILE *fin=NULL;
    char line[MAX_LINE];
    tShip newShip;
    
    /* Initialize the output table */
    shipTableInit(tabShip);
    
    /* Open the input file */
    if((fin=fopen(filename, "r"))!=NULL) {

        /* Read all the lines */
        while(!feof(fin) && tabShip->nShips<MAX_SHIPS) {
            /* Remove any content from the line */
            line[0] = '\0';
            /* Read one line (maximum 511 chars) and store it in "line" variable */
            fgets(line, MAX_LINE-1, fin);
            /* Ensure that the string is ended by 0*/
            line[MAX_LINE-1]='\0';
            if(strlen(line)>0) {
                /* Obtain the object */
                getShipObject(line, &newShip);
                /* Add the new ship to the output table */
                shipTableAdd(tabShip, newShip, retVal);		
            }
        }
        /* Close the file */
        fclose(fin);
        
    }else {
        *retVal = ERR_CANNOT_READ;
    }
}



void shipTableSelectShips(tShipTable ships, tShipType shipType, tShipTable *result) 
{
/************** PR4 EX8C ***************/
    int i;
    tError retVal;
    bool selected= false;

    shipTableInit(result);
    
    for(i=0;i<ships.nShips;i++) {
        selected = (ships.table[i].shipType == shipType);
        if (selected){
            shipTableAdd(result, ships.table[i], &retVal);
        }
    }
/***************************************/
}
