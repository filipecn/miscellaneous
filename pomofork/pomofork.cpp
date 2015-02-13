#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <string.h>

using namespace std;

#define MAX_OUTPUT 1024

void run(string query, char* output){
	string command("/usr/bin/xdotool ");
	command += query;
	FILE *fp = popen(command.c_str(), "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return;
	}
	
	fgets(output, MAX_OUTPUT, fp);

	pclose(fp);
}

int main( int argc, char *argv[] )
{
	char r[MAX_OUTPUT];
	
	while(1){
		run("getactivewindow", r);
		run(string("getwindowname ") + r, r);
		string window(r);
		FILE *fp = fopen("stats", "a+");
		if(!fp) return 0;
		time_t now = time(0);
		tm *ltm = localtime(&now);
		fprintf(fp, "%d/%d/%d-%d:%d:%d ", 
				(ltm->tm_mday),
				(1 + ltm->tm_mon),
				(1900 + ltm->tm_year),
				(1 + ltm->tm_hour),
				(1 + ltm->tm_min),
				(ltm->tm_sec));
		fprintf(fp, "%s", r);
		fclose(fp);
		sleep(1);
	}


	return 0;
}

