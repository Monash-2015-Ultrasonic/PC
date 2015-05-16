//#define DEBUG

#define BUFFERSIZE  4
#define EXTRA       4

#include <cstdlib>
#include <iostream>
#include <windows.h>

#ifndef _TASK_H_
#define _TASK_H_

extern FILE *fOutput;
extern char serialBuffer[BUFFERSIZE + EXTRA];
extern DWORD dwBytesRead;

int logSetup(char *argv[]);
int readTask();

#endif
