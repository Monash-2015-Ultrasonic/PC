#include "..\windows\inc\setup.h"


int				dataIn;
unsigned char	buffer[BUFFERSIZE];
wchar_t			wstr[MAX_STR];

hid_device		*hHID;

FILE			*fOutput;


//==================================================//
// Check to make sure enough arguments are input:   //
//==================================================//
int argumentCheck(int argc, char *argv[]) {
    /* Aesthetics: */
    system("CLS");
    printf("Ultrasonic Array FYP\n=============================\n");
    printf("USB Helper Program\n\n");
    
    /* Need 2 input arguments to program: */
    if (argc != 2) {
        printf("ERROR! Please enter a log FILE NAME.\n\n");
        printf("EXITING\n\n");
        return -1;
    }
    else {
        return 0;
    }
}


//==================================================//
// Open HID:										//
//==================================================//
int hidOpen(void)
{
	/* Set up the command buffer: */
	memset(buffer ,0x00, sizeof(buffer));
	buffer[0] = 0x01;
	buffer[1] = 0x81;
	
	/* Open the device using the VID, PID & Serial# (optional): */
	hHID = hid_open(VENDOR, PRODUCT, NULL);
	if (!hHID) {
		printf("ERROR! Unable to find USB HID.\n\n");
		printf("EXITING\n\n");
 		return -1;
	}

	/* Read the Manufacturer String: */
	wstr[0] = 0x0000;
	dataIn = hid_get_manufacturer_string(hHID, wstr, MAX_STR);
	if (dataIn < 0)
		printf("WARNING! Unable to read Manufacturer String.\n");
	else
		printf("Manufacturer String: %ls\n", wstr);

	/* Read the Product String: */
	wstr[0] = 0x0000;
	dataIn = hid_get_product_string(hHID, wstr, MAX_STR);
	if (dataIn < 0)
		printf("WARNING! Unable to read Product String.\n");
	else
		printf("Product String: %ls\n", wstr);

	/* Read the Serial Number String: */
	wstr[0] = 0x0000;
	dataIn = hid_get_serial_number_string(hHID, wstr, MAX_STR);
	if (dataIn < 0)
		printf("WARNING! Unable to read Serial Number String.\n");
	else
		printf("Serial Number String: (%d) %ls\n", wstr[0], wstr);

	/* Read Indexed String 1: */
	wstr[0] = 0x0000;
	dataIn = hid_get_indexed_string(hHID, 1, wstr, MAX_STR);
	if (dataIn < 0)
		printf("WARNING! Unable to read Indexed String 1.\n");
	else
		printf("Indexed String 1: %ls\n", wstr);

#ifdef NONBLOCK
	/* Set HID Read to non-blocking: */
	hid_set_nonblocking(hHID, 1);
#endif

	return 0;
}


//==================================================//
// Create Log File:                                 //
//==================================================//
int logSetup(char *argv[])
{
    /* Create output file overwriting existing file: */
    fopen_s(&fOutput, argv[1], "w");
    
    /* If file cannot be created: */
    if (fOutput == NULL) {
        printf("ERROR! Cannot create log file.\n\n");
        printf("EXITING\n\n");
        return -1;
    }
	return 0;
}
