#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "starbase.h"
#include "mission.h"

void getLevelStr(tLevel level, int maxSize, char *str) 
{
  
    /* Build the string */	
    snprintf(str,maxSize-1,"%d %d", 
            (int)level.id, level.hangars.nHangars);

}

void getHangarStr(tHangar hangar, int maxSize, char *str) 
{
    char tempStr[MAX_LINE];  
    int i;

    /* Build the string */	
    snprintf(str,maxSize-1,"%d %d %d", 
             (int)hangar.id, (int)hangar.isAvailable, (int)hangar.hangarType);
    if (hangar.hangarType == SHIPS){
            strcpy(tempStr, str);
            snprintf(str,maxSize-1,"%s %d %d", tempStr, (int)hangar.hangarShipType, hangar.nShips);
            for (i=0; i < hangar.nShips ; i++){
                strcpy(tempStr,str);
                snprintf(str,maxSize-1,"%s %d", tempStr, (int)hangar.shipsId[i]);
            }
        }
}



/* The content of the fields of the starbase structure is written into the string str */
void getStarbaseStr(tStarbase starbase, int maxSize, char *str) {
    
    /* Build the string */	
    snprintf(str,maxSize-1,"%d %s %s %d %d", 
         (int)starbase.id, starbase.baseName, starbase.planet, 
         (int)starbase.sector, starbase.levels.nLevels);          
}


/* The content of the string str is parsed into the fields of the level structure */
void getLevelObject(const char *str, tLevel *level) {

    int auxId;
  
    /* read level data */
    sscanf(str, "%d %d", 
        &auxId, &level->hangars.nHangars);

    level->id = (tLevelId)auxId;
}
  

/* The content of the string str is parsed into the fields of the hangar structure */
void getHangarObject(const char *str, tHangar *hangar) 
{
    char buffer[MAX_LINE];
    int auxId;
    int auxIsAvailable, auxHangarType, auxHangarShipType, auxShipId;
    int i;
    
    /* read hangar data */
    sscanf(str, "%d %d %d %[^\n]s",  
        &auxId, &auxIsAvailable, &auxHangarType, buffer);
    hangar->id = (tHangarId)auxId;
    hangar->isAvailable = (bool)auxIsAvailable;
    hangar->hangarType = (tHangarType)auxHangarType;

    if (hangar->hangarType == SHIPS){

        sscanf(buffer, "%d %d %[^\n]s", &auxHangarShipType, &hangar->nShips, buffer);
        hangar->hangarShipType = (tShipType)auxHangarShipType;
        /* read ships ids in hangar */

        for (i= 0; i < hangar->nShips ; i++){
            sscanf(buffer, "%d %[^\n]s", &auxShipId, buffer);
            hangar->shipsId[i] = (tShipId)auxShipId;
        }
    } else {
        hangar->hangarShipType = NO_SHIP_TYPE;
        hangar->nShips = 0;        
    }
}



/* The content of the string str is parsed into the fields of the starbase structure */
void getStarbaseObject(const char *str, tStarbase *starbase) {

    int auxId;
        int auxSectorId;

    /* read starbase data */
    sscanf(str, "%d %s %s %d %d", 
        &auxId, starbase->baseName, starbase->planet, &auxSectorId, &starbase->levels.nLevels);

    starbase->id = (tStarbaseId)auxId;
    starbase->sector = (tSectorId)auxSectorId;
}


void levelCpy(tLevel *dst, tLevel src) 
{
    int i;

    dst->id= src.id;
    dst->hangars.nHangars = src.hangars.nHangars;
    for (i= 0; i< src.hangars.nHangars; i++)
        hangarCpy(&dst->hangars.table[i],src.hangars.table[i]);
}
  

void hangarInit( tHangar *hangar )
{
    int i;

    hangar->id = NO_HANGAR;
    hangar->isAvailable = false;
    hangar->hangarType = NO_HANGAR_TYPE;
    hangar->hangarShipType = NO_SHIP_TYPE;
    hangar->nShips = 0;
    for (i=0; i < MAX_HANGAR_SHIPS ; i++)
        hangar->shipsId[i] = NO_SHIP;
}


void hangarCpy(tHangar *dst, tHangar src) 
{
/************* PR4 - EX2A ************/
 int i;
    
    //Copiamos el ID de hangar desde la estructura fuenta a destino
    dst->id = src.id;
    //Copiamos el estado de disponibilidad de hangar
    dst->isAvailable = src.isAvailable;
    //Copiamos el tipo de hangar 
    dst->hangarType = src.hangarType;
    //Copiamos el tipo de nave que almacena el hangar
    dst->hangarShipType = src.hangarShipType;
    //Copiamos el número de naves que actualmente están guardadas en el hangar
    dst->nShips = src.nShips;
    //Bucle para copiar id's de naves guardadas
    for (i = 0; i < src.nShips; i++) {
        //copiamos cada ID de nave de la estructura fuente a la estructura destino
        dst->shipsId[i] = src.shipsId[i];
    }

/*************************************/
}


   
void starbaseCpy(tStarbase *dst, tStarbase src) 
{    
    int i;
    
    dst->id = src.id;
    strcpy(dst->baseName,src.baseName);
    strcpy(dst->planet,src.planet);
    dst->sector = src.sector;
    dst->levels.nLevels= src.levels.nLevels;
    for (i= 0; i< src.levels.nLevels; i++)
        levelCpy(&dst->levels.table[i], src.levels.table[i]);
}

void starbaseAssignId(tStarbase *starbase, tStarbaseId id)
{
    starbase->id = id;      
}


int starbaseOccupation(tStarbase starbase)
{
    int result = 0;
    int i,j;

    for (i=0; i<starbase.levels.nLevels; i++) {
        for (j=0; j<starbase.levels.table[i].hangars.nHangars ; j++) {
            result = result + starbase.levels.table[i].hangars.table[j].nShips;
        }
    }

    return result;
}


int starbaseMaxOccupation(tStarbase starbase)
{
    int result = 0;
    int i,j;

    for (i=0; i<starbase.levels.nLevels; i++) {
        for (j=0; j<starbase.levels.table[i].hangars.nHangars ; j++) {
            if (starbase.levels.table[i].hangars.table[j].hangarType==SHIPS)
            result = result + MAX_HANGAR_SHIPS;
        }
    }
    
    return result;
}

int levelNumberOperativeHangars(tLevelTable levels)
{
    int i,j,result;
  
    result = 0;
    for( i=0; i < levels.nLevels ; i++){
        for( j=0; j < levels.table[i].hangars.nHangars ; j++){
            if (levels.table[i].hangars.table[j].isAvailable)
                result++;
        }
    }

    return result;

}

int starbaseCmp(tStarbase sb1, tStarbase sb2)
{
    int result = 0;

    /************* PR4 - EX2B ************/
    // Calcular el porcentaje de ocupación para sb1 y sb2
    float occupation1 = ((float) starbaseOccupation(sb1)) / starbaseMaxOccupation(sb1);
    float occupation2 = ((float) starbaseOccupation(sb2)) / starbaseMaxOccupation(sb2);

    // Comparar porcentaje de ocupación (en orden descendente)
    if (occupation1 > occupation2) {
        result = 1;
    } else if (occupation1 < occupation2) {
        result = -1;
    } else {
        // Si los porcentajes de ocupación son iguales, olvidarse de lo anterior, comparar nombre de la base (en orden ascendente)
        result = strcmpUpper(sb1.baseName, sb2.baseName);
        if (result == 0) {
            // Si los nombres de la base son iguales, comparar nombre del planeta (en orden ascendente)
            result = strcmpUpper(sb1.planet, sb2.planet);
            if (result == 0) {
                // Si los nombres del planeta son iguales, comparar los sectores (en orden ascendente)
                if (sb1.sector < sb2.sector) {
                    result = -1;
                } else if (sb1.sector > sb2.sector) {
                    result = 1;
                } else {
                    // Si los sectores son iguales, comparar número de niveles en la base (en orden descendente)
                    if (sb1.levels.nLevels > sb2.levels.nLevels) {
                        result = 1;
                    } else if (sb1.levels.nLevels < sb2.levels.nLevels) {
                        result = -1;
                    } else {
                        // Si el número de niveles es igual, comparar el número de hangares operativos (en orden descendente)
                        int operativeHangar1 = levelNumberOperativeHangars(sb1.levels);
                        int operativeHangar2 = levelNumberOperativeHangars(sb2.levels);
                        if (operativeHangar1 > operativeHangar2) {
                            result = 1;
                        } else if (operativeHangar1 < operativeHangar2) {
                            result = -1;
                        } else { // Entonces sb1 = sb2
                            result = 0;
                        }
                    }
                }
            }
        }
    }
    /*************************************/

    return result;
}




void starbaseInit( tStarbase *starbase ) 
{    
    starbase->id = NO_STARBASE;
    strcpy( starbase->baseName, "");
    strcpy( starbase->planet, "");
    starbase->sector = NO_SECTOR;
    starbase->levels.nLevels = 0;
}


void starbaseTableInit(tStarbaseTable *starbaseTable) {
    
    starbaseTable->nStarbases= 0;
}

void starbaseTableAdd(tStarbaseTable *tabStarbases, tStarbase starbase, tError *retVal) 
{
    *retVal = OK;

    /* Check if there enough space for the new starbase */
    if(tabStarbases->nStarbases>=MAX_STARBASES)
        *retVal = ERR_MEMORY;
        
    if (*retVal == OK) {
        /* Add the new starbase to the end of the table */
        starbaseCpy(&tabStarbases->table[tabStarbases->nStarbases],starbase);
        tabStarbases->nStarbases++;
    }
    
}


void starbaseTableDel(tStarbaseTable *tabStarbases, tStarbaseId starbaseId)
{
    int i;
    int pos;

    /* Check if starbase is in starbases table */
    pos = starbaseTableFind(*tabStarbases, starbaseId);
    if (pos!=NO_STARBASE){
        for (i=pos; i < tabStarbases->nStarbases-1 ; i++) {
            starbaseCpy(&tabStarbases->table[i], tabStarbases->table[i+1]);
        }
        tabStarbases->nStarbases = tabStarbases->nStarbases-1;
    }
}



int starbaseTableFind(tStarbaseTable tabStarbases, tStarbaseId id)
{
    int idx = NO_STARBASE;
    int i=0;

    while( i < tabStarbases.nStarbases && idx == NO_STARBASE) {
        /* Check if the id is the same */
        if( id == tabStarbases.table[i].id ) 
            idx = i;
        i++;
    }
    
    return idx;
}


void starbaseTableFilterBySector(tStarbaseTable tabStarbase, tSectorId sectorId, tStarbaseTable *result)
{
/************* PR4 - EX5A ************/
    int i;
    tError retVal;

    // Inicializar tabla de resultados
    starbaseTableInit(result);

    // Recorrer toda la tabla de bases estelares de entrada
    for (i = 0; i < tabStarbase.nStarbases; i++) {
        // Comprobar si el sector de la base estelar, coincide con el sector que se dá 
        if (tabStarbase.table[i].sector == sectorId) {
            // Agregar la base estelar a la tabla de resultados
            starbaseTableAdd(result, tabStarbase.table[i], &retVal);
            // Verificar si hubo un error al agregar la base estelar
            if (retVal != OK) {
                printf("Error adding starbase to the table %d !\n", retVal);
                return;
            }
        }
    }

/**************************************/
}


void starbaseTableSave(tStarbaseTable tabStarbases, const char* filename, tError *retVal) {

    *retVal = OK;

    FILE *fout=NULL;
    int i, j, k;
    char str[MAX_LINE];
    
    /* Open the output file */
    if((fout=fopen(filename, "w"))==0) {
        *retVal = ERR_CANNOT_WRITE;
    } else {
    
        /* Save all starbases to the file */
        for(i=0;i<tabStarbases.nStarbases;i++) {
            /* Save starbase info */
            getStarbaseStr(tabStarbases.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);

            /* Save all levels within the starbase */
            for (j= 0; j< tabStarbases.table[i].levels.nLevels; j++) {
                getLevelStr(tabStarbases.table[i].levels.table[j], MAX_LINE, str);
                fprintf(fout, "%s\n", str);
            
                /* Save all hangars within the levels */
                for (k= 0; k< tabStarbases.table[i].levels.table[j].hangars.nHangars; k++) {
                    getHangarStr(tabStarbases.table[i].levels.table[j].hangars.table[k], MAX_LINE, str);
                    fprintf(fout, "%s\n", str);
                }
            }
        }
            
        /* Close the file */
        fclose(fout);
    }
}

void starbaseTableLoad(tStarbaseTable *tabStarbases, const char* filename, tError *retVal) 
{
    FILE *fin=NULL;
    char line[MAX_LINE];
    tStarbase newStarbase;
    
    int j, k;
    *retVal = OK;
    
    /* Initialize the output table */
    starbaseTableInit(tabStarbases);
    
    /* Open the input file */
    if((fin=fopen(filename, "r"))!=NULL) {

        /* Read all the starbases */
        while(!feof(fin) && tabStarbases->nStarbases<MAX_STARBASES) {
            /* Remove any content from the line */
            line[0] = '\0';
            /* Read one line (maximum 511 chars) and store it in "line" variable */
            fgets(line, MAX_LINE-1, fin);
            /* Ensure that the string is ended by 0*/
            line[MAX_LINE-1]='\0';
            if(strlen(line)>0) {
                /* Obtain the object */
                getStarbaseObject(line, &newStarbase);
                
                /* Load all levels within the starbase */
                for (j= 0; j< newStarbase.levels.nLevels; j++) {
                    line[0] = '\0';
                    fgets(line, MAX_LINE-1, fin);
                    line[MAX_LINE-1]='\0';
                    if(strlen(line)>0) {
                        getLevelObject(line, &newStarbase.levels.table[j]);
                       
                        /* Load all hangars within the level */
                        for (k= 0; k < newStarbase.levels.table[j].hangars.nHangars; k++) {
                            line[0] = '\0';
                            fgets(line, MAX_LINE-1, fin);
                            line[MAX_LINE-1]='\0';
                            if(strlen(line)>0)
                               getHangarObject(line, &(newStarbase.levels.table[j].hangars.table[k]));
                        }

                    }                    
                } 
                
                /* Add the new starbase to the output table */
                starbaseTableAdd(tabStarbases, newStarbase, retVal);		        
            }
        }
        /* Close the file */
        fclose(fin);
        
    }else {
        *retVal = ERR_CANNOT_READ;
    }
}


void starbaseTableOrderByOccupation(tStarbaseTable *starbases)
{
/************* PR4 - EX5B ************/
    int i, j, minIdx;
    tStarbase temp;

    for (i = 0; i < starbases->nStarbases - 1; i++) {
        // Inicializar el índice del mínimo
        minIdx = i;
        // Buscar el índice del elemento con menor ocupación
        for (j = i + 1; j < starbases->nStarbases; j++) {
            if (starbaseOccupationPercent(starbases->table[j]) < starbaseOccupationPercent(starbases->table[minIdx])) {
                minIdx = j;
            }
        }
        // Intercambiar el elemento mínimo con el primer elemento no ordenado
        if (minIdx != i) {
            temp = starbases->table[i];
            starbases->table[i] = starbases->table[minIdx];
            starbases->table[minIdx] = temp;
        }
    }

/**************************************/
}

float starbaseTableAvgOccupation(tStarbaseTable starbases)
{
    float avgOccupation = 0.0;
    
/***************************** PR4 - EX8B *************************************/    
    float totalOccupation = 0.0;
    float totalCapacity = 0.0;

    // Calcular el total de ocupación y capacidad de todas las bases estelares
    for (int i = 0; i < starbases.nStarbases; i++) {
        int occupation = starbaseOccupation(starbases.table[i]);
        int capacity = starbaseMaxOccupation(starbases.table[i]);

        totalOccupation += occupation;
        totalCapacity += capacity;
    }

    // Calcular el porcentaje promedio de ocupación si hay bases estelares en la tabla
    if (starbases.nStarbases > 0) {
        avgOccupation = 100.0 * totalOccupation / totalCapacity;
    }

/******************************************************************************/

    return avgOccupation;
}


float starbaseOccupationPercent(tStarbase starbase)
{
    float avgOccupation = 0.0;
    int capacity;
    int occupation;
    
    occupation = starbaseOccupation(starbase);
    capacity = starbaseMaxOccupation(starbase);
    if (occupation > 0)
        avgOccupation = 100.0 * (float)occupation / (float)capacity;

    return avgOccupation;
}


void starbaseTableFilterByOccupation(tStarbaseTable tabStarbase, float pctOccupation, tStarbaseTable *result)
{
/********************************* PR4 - EX8A ***********************************/
// Inicializar tabla de resultados
    starbaseTableInit(result);

    // Recorrer todas las bases estelares de la tabla
    for (int i = 0; i < tabStarbase.nStarbases; i++) {
        // Calcular el porcentaje de ocupación de la base estelar actual
        float occupationPercent = starbaseOccupationPercent(tabStarbase.table[i]);
        
        // Comparar con el porcentaje de ocupación mínimo requerido
        if (occupationPercent >= pctOccupation) {
            // Agregar la base estelar a la tabla de resultados
            tError retVal;
            starbaseTableAdd(result, tabStarbase.table[i], &retVal);
            // Manejar posibles errores (opcional)
            if (retVal != OK) {
                printf("Error adding starbase to the table %d !\n", retVal);
                return; // O manejar el error de otra forma
            }
        }
    }
/********************************************************************************/
}

void starbaseTableCpy(tStarbaseTable *tabDest, tStarbaseTable tabSrc )
{
    int i;
    
    tabDest->nStarbases = tabSrc.nStarbases;
    for (i = 0; i < tabSrc.nStarbases; i++) {
        starbaseCpy(&tabDest->table[i], tabSrc.table[i]);
    }
}