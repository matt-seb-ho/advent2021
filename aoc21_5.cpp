#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
string fname = "input.txt";

// Day 5.1: consider
void readline(string line, int& x1, int& x2, int& y1, int& y2) {
	int delimPos = line.find(',');
	x1 = stoi(line.substr(0, delimPos));
	line = line.substr(delimPos + 1);
	delimPos = line.find(' ');
	y1 = stoi(line.substr(0, delimPos));
	line = line.substr(delimPos + 4);
	delimPos = line.find(',');
	x2 = stoi(line.substr(0, delimPos));
	line = line.substr(delimPos + 1);
	y2 = stoi(line);
}

void handleHori(int x, int y1, int y2, int& res, vector<vector<int>>& g) {
	if (y1 > y2) {
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	for (int y = y1; y <= y2; y++) {
		g[x][y]++;
		if (g[x][y] == 2) {
			res++;
		}
	}
}

void handleVert(int y, int x1, int x2, int& res, vector<vector<int>>& g) {
	if (x1 > x2) {
		int temp = x1;
		x1 = x2;
		x2 = temp;
	}
	for (int x = x1; x <= x2; x++) {
		g[x][y]++;
		if (g[x][y] == 2) {
			res++;
		}
	}
}

void goUpRight(int x1, int y1, int y2, int& res, vector<vector<int>>& g) {
	for (int x = x1; y1 <= y2; x++) {
		g[x][y1++]++;
		if (g[x][y1 - 1] == 2) {
			res++;
		}
	}
}

void goDownRight(int x1, int y1, int y2, int& res, vector<vector<int>>& g) {
	for (int x = x1; y1 >= y2; x++) {
		g[x][y1--]++;
		if (g[x][y1 + 1] == 2) {
			res++;
		}
	}
}

int solve5a(string fname, vector<vector<int>>& g) {
	ifstream in(fname);
	if (in.fail())
		return -1;
	
	string line;
	int x1, x2, y1, y2;
	int res = 0;
	// getline(in, line);
	int counter = 0;
	// readline(line, x1, x2, y1, y2);
	// cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	while (getline(in, line)) {
		counter++;
		readline(line, x1, x2, y1, y2);
		if (x1 == x2) {
			handleHori(x1, y1, y2, res, g);
		} else if (y1 == y2) {
			handleVert(y1, x1, x2, res, g);
		} else {
			if (x1 < x2 && y1 < y2) {
				goUpRight(x1, y1, y2, res, g);
			} else if (x1 > x2 && y1 < y2) {
				goDownRight(x2, y2, y1, res, g);
			} else if (x1 < x2 && y1 > y2) {
				goDownRight(x1, y1, y2, res, g);
			} else {
				goUpRight(x2, y2, y1, res, g);
			}
		}
	}
	in.close();
	int ans = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (g[i][j] > 1) {
				ans++;
			}
		}
	}
	cout << counter << endl;
	cout << ans << endl;
	return res;
}

int main() {
	vector<vector<int>> g(1000, vector<int>(1000, 0));
	cout << solve5a(fname, g) << endl;
	return 0;
}
