#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

volatile int Flag=1;

void handler(int signum){
	Flag = 0;
	printf("Controlled exit");
	//printf("signal!\n");
	//printf("%s\n", strsignal(signum));
}

void handler2(int signum){
	printf("Interrupt");
}

int main(void){
	signal(SIGQUIT, handler);
	signal(SIGINT, handler2);
	while(Flag)
	{
		printf("working...\n");
		sleep(1);
	}
	return 0;
}
