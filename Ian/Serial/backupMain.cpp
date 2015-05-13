#include <cstdlib>
#include <iostream>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[])
{
    printf("Ultrasonic Array FYP\n=============================\n");
    printf("Serial UART Helper Program\n\n");
    
    if (argc < 2) {
        printf("ERROR! Need to enter PORT and FILE NAME.\n\n");
        
        printf("\n\nEXITING\n\n");
        system("PAUSE");
        return EXIT_SUCCESS;
    }
    
    if (argv[1] == NULL) {
        printf("ERROR! Please enter a valid COM PORT.\n\n");
        
        printf("\n\nEXITING\n\n");
        system("PAUSE");
        return EXIT_SUCCESS;
    }
    
    if (argv[2] == NULL) {
        printf("ERROR! Please enter a valid FILE NAME.\n\n");
        
        printf("\n\nEXITING\n\n");
        system("PAUSE");
        return EXIT_SUCCESS;
    }
    
    printf("Attempting to open COM PORT: %s ...\n", argv[1]);
    HANDLE hSerial = ::CreateFile(argv[1], GENERIC_READ, 0, 0, OPEN_EXISTING,
                                            FILE_ATTRIBUTE_NORMAL, 0);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
       if (GetLastError() == ERROR_FILE_NOT_FOUND) {
          printf("ERROR! Invalid port! \n\n");
          
          printf("\n\nEXITING\n\n");
          system("PAUSE");
          return EXIT_SUCCESS;
       }
    } else {
        printf("Opened port.\n\n");
    }      
    
    printf("Configuring COM PORT %s ...\n", argv[1]);
    DCB dcbSerialParams = {0};
    
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("ERROR! Cannot obtain port state.\n\n"); 
        CloseHandle(hSerial);
        
        printf("\n\nEXITING\n\n");
        system("PAUSE");
        return EXIT_SUCCESS;   
    } else {
        printf("Port state obtained...\n");
    }

    dcbSerialParams.BaudRate = 921600*2;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    
    COMMTIMEOUTS timeouts = {0};
    
    timeouts.ReadIntervalTimeout        = 50;
    timeouts.ReadTotalTimeoutConstant   = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("ERROR! Cannot configure port settings!\n\n");
        CloseHandle(hSerial);
        
        printf("\n\nEXITING\n\n");
        system("PAUSE");
        return EXIT_SUCCESS;
    } else {
        if (!SetCommTimeouts(hSerial, &timeouts)) {
            printf("ERROR! Unable to configure port timeout!\n\n");
            CloseHandle(hSerial);
            
            printf("\n\nEXITING\n\n");
            system("PAUSE");
            return EXIT_SUCCESS;
        } else {
            printf("Port configured!\n\n");
        }
    }
    
    int run = 1;
    
    char szBuff[4096 + 4] = {0};
    DWORD dwBytesRead = 0;
    
    FILE *output;
    output = fopen(argv[2], "w");
    
    if (output == NULL) {
        printf("ERROR! Cannot create log file.\n\n");
        
        printf("\n\nEXITING\n\n");
        system("PAUSE");
        return EXIT_SUCCESS;
    }
    
    printf("Program now ready to take in data. Press any key to begin logging...\n\n");
    
    system("PAUSE");
    
    while (run) {
        if (!ReadFile(hSerial, szBuff, 4096, &dwBytesRead, NULL)) {
            printf("ERROR! Unable to read port!\n\n");
            
            CloseHandle(hSerial);
            fclose(output);
            
            printf("\n\nEXITING\n\n");
            system("PAUSE");
            return EXIT_SUCCESS;
        } else {
            for (int i = 0; i < 4096; i++) {
//                for (int j = 0; j < 4; j++) {
  //                  szBuff[i+j] = (0x0) ? 0x30 : szBuff[i+j];
    //            }
                printf("%c", szBuff[i+3, i+2, i+1, i]);
                fputc(szBuff[i+3, i+2, i+1, i], output);
            }
        }
    }
    
    CloseHandle(hSerial);
    fclose(output);
    
    system("PAUSE");
    return EXIT_SUCCESS;
    
}
