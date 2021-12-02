#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Day 1.1: count how many times the depth increases
void solve1a(string fname) {
	ifstream in(fname);
	if (in.fail()) {
		cout << "file open failed\n";
		return;
	}
	int prev;
	in >> prev;
	int curr;
	int res = 0;
	while (in >> curr) {
		if (curr > prev) {
			res++;
		}
		prev = curr;
	}
	cout << res << endl;
}

// Day 1.2: count how many times the sum of a sliding window of 3 increases
void solve1b(string fname) {
	ifstream in(fname);
	if (in.fail()) {
		cout << "file open failed\n";
		return;
	}
	int window[4] = {0};
	for (int i = 0; i < 3; i++) {
		in >> window[i];
	}

	int res = 0;
	while (in >> window[3]) {
		if (window[3] > window[0]) {
			res++;
		}
		for (int i = 0; i < 3; i++) {
			window[i] = window[i + 1];
		}
	}
	cout << res << endl;
}

int main() {
	solve1a("aoc2021_1a_in.txt");
	solve1b("aoc2021_1a_in.txt");
	return 0;
}
