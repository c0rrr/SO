#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

volatile int Flag=1;

void handler(int signum){
	Flag = 0;
	printf("Controlled exit");
	syslog(LOG_NOTICE, "Sigquit captured");
}

void handler2(int signum){
	printf("Interrupt");
}

int main(void){
	signal(SIGQUIT, handler);
	signal(SIGINT, handler2);
	openlog("Signal program:", LOG_PID, LOG_USER);
	syslog(LOG_NOTICE, "Program running");
	while(Flag)
	{	
		printf("working...\n");
		sleep(1);
	}
	closelog();
	return 0;
}
