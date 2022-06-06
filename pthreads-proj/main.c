#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "fvaria.h"
#include "fmutex.h"
#include "utils.h"

void Fmutex(int debugflag, int clientnum, int chairnum, int fryztime);
void Fvaria(int debugflag, int clientnum, int chairnum, int fryztime);
int PrintStatus(int resigned, int wcurrent, int wmax, int current, int res[], int wcurr[], int debug);

int main(int argc, char **argv)
{
	int debugflag;
	int clientnum = -1;
	int chairnum = -1;
	int fryztime = -1;
	int c;
	opterr = 0;

	while((c = getopt (argc, argv, "dc:h:f:")) != -1)
		switch(c)
		{
			case 'd':
				debugflag = 1;
				break;
			case 'c':
				clientnum = atoi(optarg);
				break;
			case 'h':
				chairnum = atoi(optarg);
				break;
			case 'f':
				fryztime = atoi(optarg);
				break;
			case '?':
				if(optopt=='c'||optopt=='h'||optopt=='f')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if(isprint (optopt))
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
				return 1;
			default:
				abort();
		}

	int choice;
	printf("Wybierz wersje programu do uruchomienia\n1.Wersja oparta na mutexach/semaforach\n2.Wersja oparta na zmiennych warunkowych\n");
	scanf("%d", &choice);
	if(choice == 1) Fmutex(debugflag, clientnum, chairnum, fryztime);
	else if(choice == 2) Fvaria(debugflag, clientnum, chairnum, fryztime);
	else
	{
		fprintf(stderr, "Invalid option\n");
		exit(EXIT_FAILURE);
	}
}
