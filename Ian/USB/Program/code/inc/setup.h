#define NONBLOCK

#define VENDOR		0x9950
#define	PRODUCT		0x2015

#define BYTES		8
#define BUFFERSIZE	256			// 2^BYTES

#define MAX_STR		255

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "hidapi.h"


#ifndef _SETUP_H_
#define _SETUP_H_

extern FILE				*fOutput;
extern hid_device		*hHID;
extern int				dataIn;
extern unsigned char	buffer[BUFFERSIZE];

int argumentCheck(int argc, char *argv[]);
int hidOpen(void);
int logSetup(char *argv[]);

#endif
