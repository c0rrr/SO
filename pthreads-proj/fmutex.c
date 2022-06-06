#include <stdio.h>

int Generate(int num);

int Fmutex(int debugflag, int clientnum, int chairnum, int fryztime)
{
	int debug = debugflag;
	printf("Fmutex\n");

	if(clientnum == -1)clientnum = Generate(1);
	if(chairnum == -1)chairnum = Generate(2);
	if(fryztime == -1)fryztime = Generate(3);

	return 0;
}
