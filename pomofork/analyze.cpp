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
	char time[100];
	char app[1100];
	map<string,int> apps;
	int total = 0;
	while(scanf("%s ",time) != EOF){
		fgets(app, 1000, stdin);
		app[strlen(app)-1] = 0;
		string s(app);
		apps[app]++;
		total++;
	}

	for(auto &a : apps){
		cout << a.first << " " << a.second << endl;
	}
	return 0;
}
