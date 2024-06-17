#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "test.h"

int main(int argc, char **argv)
{
    int i;
    bool testMode=false;
    
    /* start DSLab */
    bool dsLabMode=false;
    /* end DSLab */
    
    /* Define the variable to store the application data */
    tAppData appData;
    
    setbuf(stdout, NULL);  
    
    /* Initialize the data object */
    appDataInit(&appData);

    /* Parse input parameters to see if we should run in normal mode or in test mode */
    for(i=1; i<argc; i++) {
        if(strcmp(argv[i], "-t")==0) {
            testMode=true;			
        } else {
            if(strcmp(argv[i], "-d")==0) {
                dsLabMode=true;
            }
        }
    }
    
    /* If test mode is active, run the tests. Otherwise, start the menu */
    if(testMode) {
        runTests(TEST_MODE); 
    } else {
        if(dsLabMode) {
            runTests(DSLAB_MODE);
        } else {
            mainMenu(&appData);
        }
    }
    
    return 0;
}
