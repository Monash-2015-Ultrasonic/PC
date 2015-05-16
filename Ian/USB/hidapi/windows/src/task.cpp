#include "..\windows\inc\task.h"
#include "..\windows\inc\setup.h"


void readTask(void) 
{
#ifdef NONBLOCK
	dataIn = 0;
	while (dataIn == 0) {
		dataIn = hid_read(hHID, buffer, sizeof(buffer));
		if (_kbhit())
			return;
	}
#else
	dataIn = hid_read(hHID, buffer, sizeof(buffer));
#endif
		
	for (int i = 0; i < dataIn; i++) {
		printf("%02hhx ", buffer[i]);
		fprintf(fOutput, "%02hhx ", buffer[i]);
	}
	printf("\n");
	fprintf(fOutput, "\n");
}
