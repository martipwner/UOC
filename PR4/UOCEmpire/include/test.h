#include "data.h"
#include "api.h"

/* Hardcoded data */
#define STARBASE1 "1 DEATH_STAR_II YAVIN 13 4"
#define LEVEL14 "14 1"
#define HANGAR141 "141 1 2 3 5 38 39 40 41 42"

#define STARBASE2 "2 STARKILLER ILUM 25 3"

#define STARBASE3 "3 RESURGENT SCARIF 13 3"
#define LEVEL11 "11 3"
#define HANGAR111 "111 1 2 4 3 58 59 60"
#define HANGAR112 "112 1 2 2 3 53 54 55"
#define HANGAR113 "113 1 2 5 2 56 57"
#define LEVEL12 "12 2"
#define HANGAR121 "121 1 1"
#define HANGAR122 "122 1 1"
#define LEVEL13 "13 4"
#define HANGAR131 "131 0 3"
#define HANGAR132 "132 1 3"
#define HANGAR133 "133 1 3"
#define HANGAR134 "134 0 3"

#define STARBASE4 "4 HYPERION DRASSAL 25 3"
#define STARBASE5 "5 IMPERIAL MAHER 25 3"

#define MISSION1 "1 1 15 3 3 3 3 3 0"
#define MISSION2 "2 2 10 1 1 6 1 1 0"
#define MISSION3 "3 1 5 1 1 1 1 1 0"
#define MISSION4 "4 3 5 0 2 1 1 1 0"


#define MAX_TEST_SHIPS 60
#define MAX_TEST_MISSIONS 4

/* start DSLab */
#define TEST_MODE 1
#define DSLAB_MODE 2
#define MAX_CHARS 125
#define MAX_LINES 150
typedef char tLine[MAX_CHARS];
typedef struct {
    tLine lines[MAX_LINES];
    int nLines;
} tLinesTable;

void addLine(tLinesTable *lines, char line[]);

void printLines(int mode, tLinesTable lines, char *dsLabOutput);
/* end DSLab */

/* Runs the applications tests */
void runTests(int mode);

/* Tests the copy and comparison actions/functions */
void testCpyCmp(int *totalTest, int *passedTest, int mode, tLinesTable *lines);

/* Tests the table basic operations */
void testTableOperations(int *totalTest, int *passedTest, int mode, tLinesTable *lines);

/* Tests the sort and filters actions/functions */
void testSortAndFilters(int *totalTest, int *passedTest, int mode, tLinesTable *lines) ;

/* Tests the missions actions/functions */
void testMissions( int *totalTest, int *passedTest, int mode, tLinesTable *lines);

/* Tests the statistics and filters actions/functions */
void testStatistics(int *totalTest, int *passedTest, int mode, tLinesTable *lines);
