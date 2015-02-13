#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<string.h>

using namespace std;

int main(){
	FILE *fs = fopen("stats", "r");
	if(!fs) return 0;

	char time[100];
	char app[1100];
	map<string, map<string,int> > apps;
	int total = 0;
	while(fscanf(fs, "%s ",time) != EOF){
		fgets(app, 1000, fs);
		app[strlen(app)-1] = 0;
		string s(app);
		total++;
		int y, m, d;
		sscanf(time, "%d%*c%d%*c%d", &d, &m, &y);
		sprintf(time, "%d/%d/%d", d, m, y);
		string t(time);
		if(apps.find(t) == apps.end()){
			map<string,int> m;
			apps[t] = m;
		}
		apps[t][app]++;
	}

	fclose(fs);
	
	FILE *fp = fopen("history", "a+");
	if(!fp) return 0;
	for(auto &t : apps){
		for(auto &a : t.second){
			fprintf(fp, "%s %s %d\n", t.first.c_str(), a.first.c_str(), a.second);
		}
	}
	fclose(fp);
	
	fs = fopen("stats", "w");
	if(fs)
		fclose(fs);

	return 0;
}
