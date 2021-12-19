#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
// custom type
struct Cave {
	Cave() {}
	Cave(string s) 
		: name(s), revisit(s[0] <= 'Z') {}
	string name = "no name";
	bool revisit = false;
	bool visited = false;
	vector<Cave*> next;
};

void printc(Cave* c) {
	cout << "Cave-- name: " << c->name 
		<< ", revisit: " << c->revisit
		<< ", num neighbors: " << c->next.size()
		<< endl;
}

// global variables
// string fname = "test.txt";
string fname = "input.txt";
unordered_map<string, Cave*> caveSystem;
Cave* start = nullptr;

bool caveExists(string& s) {
	return caveSystem.find(s) != caveSystem.end();
}

void buildGraph() {
	ifstream in(fname);
	if (in.fail())
		return;
	string line, c1, c2;
	Cave *p1, *p2;
	short delim;
	while (getline(in, line)) {
		delim = line.find('-');
		c1 = line.substr(0, delim);
		c2 = line.substr(delim + 1);
		if (!caveExists(c1)) {
			p1 = new Cave(c1);
			caveSystem[c1] = p1;
			if (c1 == "start")
				start = p1;
		} else {
			p1 = caveSystem[c1];
		}
		if (!caveExists(c2)) {
			p2 = new Cave(c2);
			caveSystem[c2] = p2;
			if (c2 == "start")
				start = p2;
		} else {
			p2 = caveSystem[c2];
		}
		p1->next.push_back(p2);
		p2->next.push_back(p1);
	}
	in.close();
}
		
int dfs12a(Cave* cave) {
	if (cave->name == "end") {
		return 1;
	}
	cave->visited = true;
	int res = 0;
	for (Cave* nextCave : cave->next) {
		if (!nextCave->visited || nextCave->revisit) {
			res += dfs12a(nextCave);
		}
	}
	cave->visited = false;
	return res;
}

// dfs approach
void solve12a() {
	// cout << "start: " << start << endl;
	int ans = dfs12a(start);
	cout << "12a: " << ans << endl;
}

int dfs12b(Cave* cave, bool revisited, bool revisiting) {
	// cout << " >> " << cave->name;
	if (cave->name == "end") {
		// cout << endl;
		return 1;
	}
	cave->visited = true;
	int res = 0;
	for (Cave* nx : cave->next) {
		if (!nx->visited || nx->revisit) {
			res += dfs12b(nx, revisited, false);
		} else if (!revisited && nx->name != "start") {
			res += dfs12b(nx, true, true);
		}
	}
	if (!revisiting) {
		cave->visited = false;
	}
	return res;
}

void solve12b() {
	int ans = dfs12b(start, false, false);
	cout << "12b: " << ans << endl;
}

int main() {
	buildGraph();
	/*
	for (auto& p : caveSystem) {
		printc(p.second);
	}
	*/
	// cout << "start: " << start << endl;
	// solve12a();
	solve12b();
	return 0;
}
