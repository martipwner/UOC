/*
* File: main.c
* Author: UOC
* Course: 20232
* Description: PRA3
*/
#include <stdio.h>
#include <string.h>
#include "galacticempire.h"

int main(int argc, char **argv)
{
	tImperialBaseTable tabImperialBases;
	tImperialBase selectedImperialBase;
	char filename[MAX_FILENAME_LENGTH];
	char basename[MAX_NAME_LENGTH];
	tError retValLoad;	
	tError retValSel;	
	
	/* Exercise 2.3 */
	/* Imperial Bases table initialization */
	initImperialBaseTable(&tabImperialBases);
	/* load data from file*/ 
    printf("LOAD DATA FROM FILE. ENTER FILE NAME:\n");
    scanf("%s", filename);	
	
    loadImperialBaseTable(&tabImperialBases, filename, &retValLoad);	
	
	/* Data processing */
	if (retValLoad == OK) {	
		/* Write Imperial Bases list loaded */
		writeImperialBaseTable (tabImperialBases);
		
		/* Exercise 2.4 */		
		/* Select a Imperial Base by name */
		printf("BASE NAME (A STRING)?\n");
		scanf("%s",basename);
		
		/* Recover imperial base from table */
		selectImperialBase (tabImperialBases, basename, &selectedImperialBase, &retValSel);
		
		if (retValSel == OK) {	
			/* Sort the ships from the selected Imperial Base */
			sortShipsByCapacity(&selectedImperialBase.shipTable);		
			/* Write selected imperial base */
			writeImperialBase(selectedImperialBase);
		}			
		else {
			/* No data recovered */
			printf("NO IMPERIAL BASE RECOVERED\n");	
		}
	}
	else {
		/* No data recovered */
		printf("NO IMPERIAL BASES RECOVERED\n");	
	} 
		
	return 0;
}
