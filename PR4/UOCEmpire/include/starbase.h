#include "data.h"

/* Get a textual representation of the hangars within the level */
void getHangarStr(tHangar hangar, int maxSize, char *str);

/* Get a textual representation of a level */
void getLevelStr(tLevel level, int maxSize, char *str);

/* Get a textual representation of a starbase */
void getStarbaseStr(tStarbase starbase, int maxSize, char *str);

/* Get a level object from its textual representation */
void getLevelObject(const char *str, tLevel *level);

/* Get a hangar object from its textual representation */
void getHangarObject(const char *str, tHangar *hangar);

/* Get a starbase object from its textual representation */
void getStarbaseObject(const char *str, tStarbase *starbase);

/* Inits the given starbase */
void starbaseInit( tStarbase *starbase );

/* Copy the starbase data in src to dst*/
void starbaseCpy(tStarbase *dst, tStarbase src);

/* Assigns an id to a starbase */
void starbaseAssignId(tStarbase *starbase, tStarbaseId id);

/* Compares the starbase data of s1 and s2*/
int starbaseCmp(tStarbase s1, tStarbase s2);

/* Copy the hangar data in src to dst */
void hangarCpy(tHangar *dst, tHangar src);

/* Copy the level data in src to dst */
void levelCpy(tLevel *dst, tLevel src);

/* Initializes the hangar data */
void hangarInit( tHangar *hangar);

/* Initializes the given starbases table */
void starbaseTableInit(tStarbaseTable *starbaseTable);

/* Add a new starbase to the table of starbases */
void starbaseTableAdd(tStarbaseTable *tabStarbases, tStarbase starbase, tError *retVal);

/* Delete a starbase wich certain id from starbase table */
void starbaseTableDel(tStarbaseTable *tabStarbases, tStarbaseId starbaseId);

/* Find a starbase in the table */
int starbaseTableFind(tStarbaseTable tabStarbases, tStarbaseId id);

/* Find starbases of a certain sector */
void starbaseTableFilterBySector(tStarbaseTable tabStarbase, tSectorId sectorId, tStarbaseTable *result);

/* Load the table of starbases from a file */
void starbaseTableLoad(tStarbaseTable *tabStarbases, const char* filename, tError *retVal);

/* Save a table of starbases to a file */
void starbaseTableSave(tStarbaseTable tabStarbases, const char* filename, tError *retVal);

/* Obtain the Occupation of the given starbase */
int starbaseOccupation(tStarbase starbase);

/* Obtain the maximum occupation of ships in starbase */
int starbaseMaxOccupation(tStarbase starbase);

/* Obtain the occupation percentage of the given starbase */
float starbaseOccupationPercent(tStarbase starbase);

/* Obtain starbases with a minimum occupation */
void starbaseTableFilterByOccupation(tStarbaseTable tabStarbases, float capacity, tStarbaseTable *result);

/* Obtain the starbase average occupation */
float starbaseTableAvgOccupation(tStarbaseTable tabStarbase);

/* Order starbase table by occupation */
void starbaseTableOrderByOccupation(tStarbaseTable *starbases);

/* Copies starbase table onto a starbase table */
void starbaseTableCpy(tStarbaseTable *tabDest, tStarbaseTable tabSrc);