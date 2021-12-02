#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Day 2.1: find product of final x and y pos
void solve2a(string fname) {
	ifstream in(fname);
	if (in.fail())
		return;
	int x = 0, y = 0;
	string d;
	int amt;
	while (in >> d) {
		in >> amt;
		switch (d[0]) {
			case 'f':
				x += amt;
				break;
			case 'u':
				y -= amt;
				break;
			case 'd':
				y += amt;
				break;
		}
	}
	cout << x * y << endl;
}

// Day 2.2: same thing, but up/down affect aim where aim = slope
void solve2b(string fname) {
	ifstream in(fname);
	if (in.fail())
		return;
	int x = 0, y = 0, aim = 0, amt;
	string d;
	while (in >> d) {
		in >> amt;
		switch (d[0]) {
			case 'f':
				x += amt;
				y += amt * aim;
				break;
			case 'u':
				aim -= amt;
				break;
			case 'd':
				aim += amt;
				break;
		}
	}
	cout << x * y << endl;
}

int main() {
	solve2a("input.txt");
	solve2b("input.txt");
	return 0;
}
