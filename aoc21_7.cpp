#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
// string fname = "test.txt";
string fname = "input.txt";

vector<int> fileread(string fname) {
	ifstream in(fname);
	if (in.fail()) {
		return {};
	}
	string line;
	getline(in, line);
	in.close();

	stringstream ss(line);
	string token;
	int pos;
	vector<int> res;
	while (getline(ss, token, ',')) {
		pos = stoi(token);
		res.push_back(pos);
	}
	return res;
}

int solve7a(vector<int>& pos) {
	sort(pos.begin(), pos.end());
	int med = pos[pos.size() / 2];
	int fuel = 0;
	for (int x : pos) {
		fuel += abs(x - med);
	}
	return fuel;
}

// part 2

int fuel(int d) {
	d = abs(d);
	return (d + 1) * d / 2;
}

int test(vector<int>& crab, int spot) {
	int res = 0;
	for (int x : crab) {
		res += fuel(x - spot);
	}
	return res;
}

int solve7b(vector<int>& pos) {
	int smol = test(pos, 0);
	int maxPos = *max_element(pos.begin(), pos.end());
	int f;
	for (int i = 0; i < maxPos; i++) {
		f = test(pos, i);
		smol = min(smol, f);
	}
	return smol;
}

int main() {
	vector<int> crab;
	crab = fileread(fname);
	// cout << solve7a(crab) << endl;
	cout << solve7b(crab);

	cout << fuel(4) << endl;
	return 0;
}
