#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
// global vars
string fname = "input.txt";
// string fname = "test.txt";
vector<vector<short>> g;

void printb() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << g[i][j];
		}
		cout << endl;
	}
}

struct Coord {
	Coord() {}
	Coord(int a, int b) : x(a), y(b) {}
	void operator+=(Coord& o) {
		x += o.x;
		y += o.y;
	}
	void operator-=(Coord& o) {
		x -= o.x;
		y -= o.y;
	}
	int x, y;
};

void readFile() {
	ifstream in(fname);
	if (in.fail())
		return;
	string line;
	vector<short> row(10, -1);
	while (getline(in, line)) {
		for (int i = 0; i < 10; i++) {
			row[i] = line[i] - '0';
		}
		g.push_back(row);
	}
	in.close();
	// printb();
	cout << "file read successfully!\n";
}

bool valid(Coord& c) {
	bool res = c.x >= 0 && c.y >= 0 && c.x < g.size() && c.y < g[0].size();
	return res && g[c.x][c.y] >= 0;
}

Coord delta[8];
int step() {
	queue<Coord> q;
	Coord c;
	for (int i = 0; i < 10; i++) {
		c.x = i;
		for (int j = 0; j < 10; j++) {
			c.y = j;
			g[i][j]++;
			if (g[i][j] == 10) {
				g[i][j] = -1;
				q.push(c);
			}
		}
	}

	int res = 0;
	while (!q.empty()) {
		c = q.front();
		q.pop();
		res++;
		for (int i = 0; i < 8; i++) {
			c += delta[i];
			if (valid(c)) {
				g[c.x][c.y]++;
				if (g[c.x][c.y] > 9) {
					q.push(c);
					g[c.x][c.y] = -1;
				}
			}
			c -= delta[i];
		}
	}

	// clean-up
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			g[i][j] += (g[i][j] == -1);
		}
	}

	return res;
}
		
void solve11a() {
	int res = 0;
	int diff;
	for (int i = 0; i < 100; i++) {
		diff = step();
		// cout << "step " << i + 1 << ": " << diff << endl;
		res += diff;
	}
	cout << "11a: " << res << endl;
}

void solve11b() {
	int counter = 1;
	bool done = false;
	while (!done) {
		done = true;
		step();
		for (int i = 0; i < 100 && done; i++) {
			if (g[i / 10][i % 10]) {
				done = false;
			}
		}
		if (done) {
			cout << "11b: " << counter << endl;
			return;
		}
		counter++;
	}
}

int main() {
	delta[0] = Coord(1, 0);
	delta[1] = Coord(-1, 0);
	delta[2] = Coord(0, 1);
	delta[3] = Coord(0, -1);
	delta[4] = Coord(1, 1);
	delta[5] = Coord(-1, 1);
	delta[6] = Coord(1, -1);
	delta[7] = Coord(-1, -1);
	readFile();
	
	// solve11a();
	solve11b();
	/*
	printb();
	cout << step() << endl;
	printb();
	cout << step() << endl;
	printb();
	cout << step() << endl;
	printb();
	cout << step() << endl;
	*/

	return 0;
}
