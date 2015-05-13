#include <cstdlib>
#include <iostream>
#include <windows.h>

#include "..\inc\setup.h"
#include "..\inc\task.h"

using namespace std;

int main(int argc, char *argv[])
{
    //==================================================//
    // Check to make sure enough arguments are input:   //
    //==================================================//    
    if (argumentCheck(argc, argv) != 0) {
        system("PAUSE");
        return -1;
    }
    
    //==================================================//
    // Open Serial Port:                                //
    //==================================================//
    if (serialOpen(argv) != 0) {
        system("PAUSE");
        return -1;
    }

    //==================================================//
    // Create Log File:                                 //
    //==================================================//
    if (logSetup(argv) != 0) {
        system("PAUSE");
        return -1;
    }
    
    //==================================================//
    // System ready...                                  //
    //==================================================//
    printf("READY! Now logging...\n\n");

    //==================================================//
    // Run until error:                                 //
    //==================================================//
    int run = 1;
    
    while (run) {
        run = (readTask() == 0) ? 1 : 0;
    }
    
    //==================================================//
    // Closing house-keeping tasks:                     //
    //==================================================//
    CloseHandle(hSerial);
    fclose(output);
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
