#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <map>

using namespace std;

#define TOTAL_TIME 60
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

	FILE *fp = fopen("stats", "w+");
	if(!fp) return 0;
	
	map<string, int> stats;
	int seconds = 0;
	while(seconds < TOTAL_TIME){
		run("getactivewindow", r);
		run(string("getwindowname ") + r, r);
		string window(r);
		stats[window]++;
		fprintf(fp, "%s", r);
		sleep(1);
		seconds++;
	}

	fclose(fp);

	return 0;
}

