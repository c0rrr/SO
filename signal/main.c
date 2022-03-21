#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void handler(int signum){
	printf("signal!\n");
	printf("%s\n", strsignal(signum));
}

int main(void){
	signal(SIGINT, handler);
	while(1)
	{
		printf("working...\n");
		sleep(1);
	}
	return 0;
}
