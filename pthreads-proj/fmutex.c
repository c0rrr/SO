#include <stdio.h>

int Generate(int num);

<<<<<<< HEAD
int Fmutex(int debugflag, int clientnum, int chairnum, int fryztime)
=======
int Fmutex(int debug)
>>>>>>> c2a998fcdfc7310b7b222029b7ad91825928f43c
{
	int debug = debugflag;
	printf("Fmutex\n");
<<<<<<< HEAD

	if(clientnum == -1)clientnum = Generate(1);
	if(chairnum == -1)chairnum = Generate(2);
	if(fryztime == -1)fryztime = Generate(3);

	return 0;
=======
	int clients = Generate(1);
	int wmax = Generate(2);
	printf("Wygenerowana ilość klientow: %d\n",clients);
	printf("Wygenerowana ilość miejsc w poczekalni: %d\n",wmax);
>>>>>>> c2a998fcdfc7310b7b222029b7ad91825928f43c
}
