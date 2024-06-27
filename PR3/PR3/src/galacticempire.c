/*
* File: galacticempire.c
* Author: UOC
* Course: 20232
* Description: PR3
*/
#include <stdlib.h>
#include <string.h>
#include "galacticempire.h"


/* Copy ship structure */
void shipCpy(tShip *dst, tShip src)
{
	strcpy(dst->name,src.name);
    dst->shipType= src.shipType;
	dst->troopCapacity = src.troopCapacity;
}

/* Copy imperial base structure */
void imperialBaseCpy(tImperialBase *dst, tImperialBase src) 
{    
    int i;
    strcpy(dst->name,src.name);
	dst->shipTable.numShips = src.shipTable.numShips;
    for (i = 0; i < src.shipTable.numShips; i++) {
        shipCpy(&dst->shipTable.ships[i],src.shipTable.ships[i]);		
	}
}


/* Add an imperial base to an imperial base table */
void imperialBaseTableAdd(tImperialBaseTable *tabImperialBases, tImperialBase imperialBase, tError *retVal) {
	
	*retVal = OK;
	
	/* Check if there is enough space for the new imperial base */
	if(tabImperialBases->numImperialBases == MAX_IMPERIAL_BASES) {
		/* Full table, no space */
		*retVal = ERR_MEMORY;
	}
	else{
		/* Add the new imperial base to the end of the table */
		imperialBaseCpy(&tabImperialBases->imperialBases[tabImperialBases->numImperialBases], imperialBase);
		/* Increase the number of imperial bases */
		tabImperialBases->numImperialBases++;	
	}
}

/* The content of the string str is parsed into the fields of the Imperial Base structure */
void getImperialBaseObject(const char *str, tImperialBase *imperialBase) 
{
    /* read suporter data */
    sscanf(str, "%s %d", imperialBase->name, &imperialBase->shipTable.numShips);
}

/* The content of the string str is parsed into the fields of the ship structure */
void getShipObject(const char *str, tShip *ship) 
{
	int auxShipType;
	
    /* read tTicket data */
    sscanf(str, "%s %d %d", ship->name, &auxShipType, &ship->troopCapacity);
	ship->shipType = (tShipType)auxShipType;
}


/* Load Imperial Base Table from file */
void loadImperialBaseTable(tImperialBaseTable *tabImperialBases, const char* filename, tError *retVal){
	FILE *fin=NULL;
	char line[MAX_LINE];
	tImperialBase newImperialBase;
	int i;
	
	*retVal = OK;	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {
		/* Read all the supporters */
		while(!feof(fin) && tabImperialBases->numImperialBases < MAX_IMPERIAL_BASES && *retVal == OK) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line) > 1) {
				/* Get data supporter */
				getImperialBaseObject(line, &newImperialBase);	
				
				/* Load all ships in the Imperial base */
                for (i = 0; i < newImperialBase.shipTable.numShips; i ++) {		
					line[0] = '\0';
                    fgets(line, MAX_LINE-1, fin);
                    line[MAX_LINE-1]='\0';
                    if(strlen(line) > 1) {	
						/*Get data screen */					
                        getShipObject(line, &newImperialBase.shipTable.ships[i]);						
					}
				}
				/* Add the new imperial base to the output table */                
				imperialBaseTableAdd (tabImperialBases, newImperialBase, retVal);			
			}			
		}	
		/* Close the file */
		fclose(fin);	
	}
	else {
		*retVal = ERR_CANNOT_READ;
	}	
}


/* Imperial base table init*/
void initImperialBaseTable(tImperialBaseTable *tabImperialBases) 
{
	/* Empty table, no imperial bases*/
	tabImperialBases->numImperialBases = 0;
}


/* Write a imperial base */
void writeImperialBase(tImperialBase imperialBase) {
	
	int i;
	
	/* Write imperial base data */
	printf("\n");
	printf("BASE NAME                    \n");
	printf("-----------------------------\n");	
	printf("%s\n",imperialBase.name);		
	printf("\n");
	/* Write imperial base ships */
	printf("SHIP NAME   TYPE     CAPACITY\n");
	printf("-----------------------------\n");
	for (i = 0; i < imperialBase.shipTable.numShips; i++){
		printf("%-14s %d %12d\n",imperialBase.shipTable.ships[i].name, imperialBase.shipTable.ships[i].shipType, imperialBase.shipTable.ships[i].troopCapacity);		
	}
	printf("\n");			
}

/* Write a imperial base table */
void writeImperialBaseTable(tImperialBaseTable tabImperialBases) {
	int i;
	
    /* Processing the table */	
	for (i = 0; i < tabImperialBases.numImperialBases; i++){
		/* Writing the imperial base data */
		writeImperialBase(tabImperialBases.imperialBases[i]);
	}		
}


/* Exercise 2.1 */
/* Select imperial base by name */
void selectImperialBase(tImperialBaseTable tabImperialBases, char* baseName, tImperialBase *imperialBase, tError *retVal) {
    *retVal = ERR_NOT_FOUND;   /* Initialize the return value, not found by default */
    int n = 0; 
    
    /* Iterate over the imperial bases table until the end or until a base is found */
    while (n < tabImperialBases.numImperialBases && *retVal == ERR_NOT_FOUND) {
        /* Check if the name of the current base matches the provided baseName */
        if (strcmp(tabImperialBases.imperialBases[n].name, baseName) == 0) {
            /* If a match is found, copy the details of the base to the provided imperialBase variable */
            imperialBaseCpy(imperialBase, tabImperialBases.imperialBases[n]);
            /* Update the return value to indicate success */
            *retVal = OK;
        }
        n++;  /* Move to the next base in the table */
    }
}

/* Exercise 2.2 */
/* Sort a table of ships by their troop capacity */
void sortShipsByCapacity(tShipTable *tabShips) {
    int i, j, posMin; /* Index and minimum position variables */
    tShip shipAux;    /* Auxiliary ship for swapping */
    
    i = 0; /* Initialize the iteration index */
    
    /* Iterate over all ships in the ship table */
    while (i < tabShips->numShips) {
        /* Assume the current ship has the minimum troop capacity */
        posMin = i;
        
        /* Start comparing with the following ships onwards */
        j = i + 1;
        while (j < tabShips->numShips) {
            /* If the next ship has less troop capacity, update the minimum position to j */
            if (tabShips->ships[j].troopCapacity < tabShips->ships[posMin].troopCapacity) {
                posMin = j;
            }
            /* Move to the next ship to compare */
            j++;
        }
        
        /* Swap the ships: place the ship with the minimum troop capacity at the current position (i) */
        /* and move the current ship (i) to the position where the ship with minimum capacity was (posMin) */
        shipCpy(&shipAux, tabShips->ships[posMin]);
        shipCpy(&tabShips->ships[posMin], tabShips->ships[i]);
        shipCpy(&tabShips->ships[i], shipAux);
        
        /* Move to the next ship to continue the sorting process */
        i++;
    }
}
 
