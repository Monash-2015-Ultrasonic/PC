#include "..\inc\task.h"
#include "..\inc\setup.h"

FILE *fOutput;
char serialBuffer[BUFFERSIZE + EXTRA] = "0";
DWORD dwBytesRead = 0;

//==================================================//
// Create Log File:                                 //
//==================================================//
int logSetup(char *argv[])
{
    /* Create output file overwriting existing file: */
    fOutput = fopen(argv[2], "w");
    
    /* If file cannot be created: */
    if (fOutput == NULL) {
        printf("ERROR! Cannot create log file.\n\n");
        
        printf("\n\nEXITING\n\n");
        return -1;
    }
}

//==================================================//
// Read serial data and log:                        //
//==================================================//
int readTask()
{
    /* Read serial data and store into buffer: */
    int result = ReadFile(hSerial, serialBuffer, sizeof(serialBuffer), &dwBytesRead, NULL);
    if (!result) {
        /* Read failed: */
        printf("ERROR! Unable to read port!\n\n");
           
        CloseHandle(hSerial);
        fclose(fOutput);
            
        printf("\n\nEXITING\n\n");
        return -1;
    } else { 
        if (dwBytesRead != 0) {
            /* Read succeeded; output results to console and file: */
            for (int i = 0; i < dwBytesRead; i++) {
                //printf("%c", serialBuffer[i+3, i+2, i+1, i]);
                fprintf(fOutput, "%c", serialBuffer[i+3, i+2, i+1, i]);
            }
        }
        return 0;
    }
}
