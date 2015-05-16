//#define DEBUG

//#define BAUD 230400
#define BAUD 1843200

#include <cstdlib>
#include <iostream>
#include <windows.h>

#ifndef _SETUP_H_
#define _SETUP_H_

extern HANDLE hSerial;
extern DCB dcbSerialParams;
extern COMMTIMEOUTS timeouts;

int argumentCheck(int argc, char *argv[]);
int serialOpen(char *argv[]);

#endif
