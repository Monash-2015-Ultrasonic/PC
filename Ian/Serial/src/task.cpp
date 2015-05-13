#include "..\inc\task.h"
#include "..\inc\setup.h"

FILE *output;
char serialBuffer[BUFFERSIZE + 4] = {0};
DWORD dwBytesRead = 0;

//==================================================//
// Create Log File:                                 //
//==================================================//
int logSetup(char *argv[])
{
    /* Create output file overwriting existing file: */
    output = fopen(argv[2], "w");
    
    /* If file cannot be created: */
    if (output == NULL) {
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
    if (!ReadFile(hSerial, serialBuffer, BUFFERSIZE, &dwBytesRead, NULL)) {
        /* Read failed: */
        printf("ERROR! Unable to read port!\n\n");
           
        CloseHandle(hSerial);
        fclose(output);
            
        printf("\n\nEXITING\n\n");
        return -1;
    } else {
        /* Read succeeded; output results to console and file: */
        for (int i = 0; i < BUFFERSIZE; i++) {
            printf("%c", serialBuffer[i+3, i+2, i+1, i]);
            fprintf(output, "%c", serialBuffer[i+3, i+2, i+1, i]);
        }
        return 0;
    }
}
