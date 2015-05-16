#include "..\inc\setup.h"

HANDLE hSerial;
DCB dcbSerialParams = {0};
COMMTIMEOUTS timeouts = {0};

//==================================================//
// Check to make sure enough arguments are input:   //
//==================================================//
int argumentCheck(int argc, char *argv[]) {
    /* Aesthetics: */
    system("CLS");
    printf("Ultrasonic Array FYP\n=============================\n");
    printf("Serial UART Helper Program\n\n");
    
    /* Need 2 input arguments to program: */
    if (argc != 3) {
        printf("ERROR! Need to enter PORT and FILE NAME.\n\n");
        
        printf("\n\nEXITING\n\n");
        return -1;
    }
    else {
        return 0;
    }
}

//==================================================//
// Open Serial Port:                                //
//==================================================//
int serialOpen(char *argv[])
{
    printf("Attempting to open and configure COM PORT: %s ...\n", argv[1]);
   
    /* Create HANDLE for serial port: */
    hSerial = ::CreateFile(argv[1], GENERIC_READ, 0, 0, OPEN_EXISTING,
                                            FILE_ATTRIBUTE_NORMAL, 0);
    
    /* If failed to create HANDLE: */
    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            printf("ERROR! Invalid port! \n\n");
         
            printf("\n\nEXITING\n\n");
            return EXIT_SUCCESS;
        }
    } else {
        #ifdef DEBUG
        printf("Port handle succeeded.\n\n");
        #endif
    }
    
    /* Read port settings: */
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
   
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        /* Port read failed: */
        printf("ERROR! Uable to open port.\n\n"); 
        CloseHandle(hSerial);
       
        printf("\n\nEXITING\n\n");
        return -1;   
    } else {
        printf("SERIAL PORT OPENED...\n");         
    }
   
    /* Port configuration parameters: */
    dcbSerialParams.BaudRate = 1843200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.Parity   = NOPARITY;
    dcbSerialParams.StopBits = ONESTOPBIT;
    
    /* Connection timeout parameters: */
    COMMTIMEOUTS timeouts = {0};
   
    timeouts.ReadIntervalTimeout        = 50;
    timeouts.ReadTotalTimeoutConstant   = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    /* Set serial port configuration: */
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        /* Serial Port Configuration failed: */
        printf("ERROR! Cannot configure port!\n\n");
        CloseHandle(hSerial);
       
        printf("\n\nEXITING\n\n");
        return -1;
    } else {
        /* Serial Port Configuration succeeded */
        /* Set serial port timeout: */
        if (!SetCommTimeouts(hSerial, &timeouts)) {
            /* Serial Port Timeout Setting failed: */
            printf("ERROR! Unable to configure port timeout!\n\n");
            CloseHandle(hSerial);
           
            printf("\n\nEXITING\n\n");
            return -1;
        } else {
            printf("PORT CONFIGURED!\n\n");
            return 0;
        }
    }
}
