//#define DEBUG

#define BUFFERSIZE 8192

#include <cstdlib>
#include <iostream>
#include <windows.h>

#ifndef _TASK_H_
#define _TASK_H_

extern FILE *output;
extern char serialBuffer[BUFFERSIZE + 4];
extern DWORD dwBytesRead;

int logSetup(char *argv[]);
int readTask();

#endif
