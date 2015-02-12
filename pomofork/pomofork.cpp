#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <ctime>

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
		fprintf(fp, "%s", r);
		fclose(fp);
		sleep(1);
		time_t now = time(0);
		tm *ltm = localtime(&now);
		//cout << "Year: "<< 1900 + ltm->tm_year << endl;
		//cout << "Month: "<< 1 + ltm->tm_mon<< endl;
		//cout << "Day: "<<  ltm->tm_mday << endl;
		//cout << "Time: "<< 1 + ltm->tm_hour << ":";
		//cout << 1 + ltm->tm_min << ":";
		//cout << 1 + ltm->tm_sec << endl;
		//if(ltm->tm_min == 49)
		//	break;
	}


	return 0;
}

