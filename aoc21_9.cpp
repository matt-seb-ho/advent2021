#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;
string fname = "input.txt";
// string fname = "test.txt";

// tested and works ^ -^)b
void readFile(vector<vector<short>>& g) {
	ifstream in(fname);
	if (in.fail())
		return;
	string line;
	char c;
	vector<short> placeholder;
	g.push_back(placeholder);
	while (getline(in, line)) {
		vector<short> row;
		row.push_back(10);
		stringstream ss(line);
		while (ss >> c) {
			row.push_back(c - '0');
		}
		row.push_back(10);
		g.push_back(row);
	}
	in.close();
	vector<short> dummy(g[1].size(), 10);
	g[0] = dummy;
	g.push_back(dummy);
}

bool isLow(vector<vector<short>>& g, int x, int y) {
	return g[x][y] < g[x + 1][y] &&
		g[x][y] < g[x - 1][y] &&
		g[x][y] < g[x][y + 1] &&
		g[x][y] < g[x][y - 1];
}

void solve9a(vector<vector<short>>& g) {
	int n = g.size() - 2;
	int m = g[0].size() - 2;
	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (isLow(g, i, j)) {
				res += g[i][j] + 1;
			}
		}
	}
	cout << "9a: " << res << endl;
}

struct Coord {
	Coord() {}
	Coord(int x, int y) 
		: x(x), y(y) {}
	void operator+=(Coord& other) {
		x += other.x;
		y += other.y;
	}
	void operator-=(Coord& other) {
		x -= other.x;
		y -= other.y;
	}
	int x, y;
};

Coord delta[4];

void getLowPoints(vector<vector<short>>& g, vector<Coord>& lo) {
	int n = g.size() - 2;
	int m = g[0].size() - 2;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (isLow(g, i, j)) {
				lo.push_back(Coord(i, j));
			}
		}
	}
}

bool valid(vector<vector<short>>& g, Coord& c) {
	bool res = c.x >= 0 && c.y >= 0 && c.x < g.size() && c.y < g[0].size();
	return res && g[c.x][c.y] < 9;
}

void bfs(vector<vector<short>>& g, Coord start, int& size) {
	queue<Coord> q;
	q.push(start);
	Coord c;
	g[start.x][start.y] = 11;
	while (!q.empty()) {	
		c = q.front();
		q.pop();
		size++;
		for (int i = 0; i < 4; i++) {
			c += delta[i];
			if (valid(g, c)) {
				q.push(c);
				g[c.x][c.y] = 11;
			}
			c -= delta[i];
		}
	}
}

void solve9b(vector<vector<short>>& g) {
	vector<Coord> lo;
	getLowPoints(g, lo);
	priority_queue<int> top3;
	int size;
	for (Coord& c : lo) {
		size = 0;
		bfs(g, c, size);
		top3.push(size);
	}
	int res = 1;
	for (int i = 0; i < 3; i++) {
		res *= top3.top();
		cout << i + 1 << ". " << top3.top() << endl;
		top3.pop();
	}
	cout << "9b: " << res << endl;
}

int main() {
	vector<vector<short>> g;
	readFile(g);
	cout << "num rows: " << g.size() << endl;
	cout << "num cols: " << g[0].size() << endl;
	solve9a(g);

	delta[0] = Coord(1, 0);
	delta[1] = Coord(-1, 0);
	delta[2] = Coord(0, 1);
	delta[3] = Coord(0, -1);

	solve9b(g);

	return 0;
}
