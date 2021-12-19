#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using std::string, std::vector, std::cout;

string fname;
int dim, shift, lower, rsize;
const int inf = 1e9;
bool test = 0;
bool partA = 0;

// grid
vector<vector<short>> g;
std::unordered_map<int, long> costs;
std::unordered_map<int, bool> visited;

// Day 15A
// given a grid where each cell's value is the cost associated with entering the cell, 
// find min cost from top left to bottom right

long cost(int x) {
	if (costs.find(x) == costs.end())
		return inf;
	return costs[x];
}

int entry(int x) {
	return g[x >> shift][x & lower];
}

void readFileA() {
	std::ifstream in(fname);
	if (in.fail())
		return;
	string line;
	g.resize(dim);
	vector<short> row(dim);
	int rnum = 0;
	while (std::getline(in, line)) {
		for (int i = 0; i < dim; i++) {
			row[i] = line[i] - '0';
		}
		g[rnum++] = row;
	}
	in.close();
}

void solve15a() {
	auto comp = [](int l, int r) {
		return cost(l) > cost(r);
	};
	std::priority_queue<int, vector<int>, decltype(comp)> pq(comp);
	costs[0] = 0;
	pq.push(0);
	int pos;
	while (!pq.empty()) {
		// get next unvisited
		pos = pq.top();
		pq.pop();
		while (visited[pos]) {
			pos = pq.top();
			pq.pop();
		}
		// mark visited
		/*
		cout << "looking at: " << (pos >> shift) << ", "  
			<< (pos & lower) << ": " << cost(pos) << '\n';
		*/
		visited[pos] = true;
		
		// update and visit neighbors as needed
		int next;

		// left
		next = pos - 1;
		if ((pos >> shift) == (next >> shift) &&
			cost(next) > cost(pos) + entry(next)) {
			costs[next] = cost(pos) + entry(next);
			pq.push(next);
		}

		// right
		next = pos + 1;
		if ((next & lower) < dim &&
			cost(next) > cost(pos) + entry(next)) {
			costs[next] = cost(pos) + entry(next);
			pq.push(next);
		}

		// up
		next = pos - rsize;
		if (next >= 0 &&
			cost(next) > cost(pos) + entry(next)) {
			costs[next] = cost(pos) + entry(next);
			pq.push(next);
		}

		// down
		next = pos + rsize;
		if (next < (dim << shift) &&
			cost(next) > cost(pos) + entry(next)) {
			costs[next] = cost(pos) + entry(next);
			pq.push(next);
		}
	}

	int last = ((dim - 1) << shift) + dim - 1;
	cout << "15a: " << cost(last) << '\n';
}

void solve15b() {
	auto comp = [](int l, int r) {
		return cost(l) > cost(r);
	};
	std::priority_queue<int, vector<int>, decltype(comp)> pq(comp);
	costs[0] = 0;
	pq.push(0);
	int pos;
	while (!pq.empty()) {
		// get next unvisited
		pos = pq.top();
		pq.pop();
		while (visited[pos]) {
			pos = pq.top();
			pq.pop();
		}
		// mark visited
		/*
		cout << "looking at: " << (pos >> shift) << ", "  
			<< (pos & lower) << ": " << cost(pos) << '\n';
		*/
		visited[pos] = true;
		
		// update and visit neighbors as needed
		int next;

		// left
		next = pos - 1;
		if ((pos >> shift) == (next >> shift) &&
			cost(next) > cost(pos) + entry(next)) {
			costs[next] = cost(pos) + entry(next);
			pq.push(next);
		}

		// right
		next = pos + 1;
		if ((next & lower) < 5 * dim &&
			cost(next) > cost(pos) + entry(next)) {
			costs[next] = cost(pos) + entry(next);
			pq.push(next);
		}

		// up
		next = pos - rsize;
		if (next >= 0 &&
			cost(next) > cost(pos) + entry(next)) {
			costs[next] = cost(pos) + entry(next);
			pq.push(next);
		}

		// down
		next = pos + rsize;
		if ((next >> shift) < (5 * dim) && 
			cost(next) > cost(pos) + entry(next)) {
			costs[next] = cost(pos) + entry(next);
			pq.push(next);
		}
	}

	// 15a:
	// int last = ((dim - 1) << shift) + dim - 1;
	// 15b:
	long last = ((5 * dim - 1) << shift) + 5 * dim - 1;
	cout << "15b: " << cost(last) << '\n';
}

void addNum(int num, int x, int y) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			g[x + (i * dim)][y + (j * dim)] = (num + i + j - 1) % 9 + 1;
		}
	}
}

void readFileB() {
	std::ifstream in(fname);
	if (in.fail())
		return;
	string line;
	g.resize(dim * 5, vector<short>(dim * 5, 100));
	int rnum = 0;
	while (std::getline(in, line)) {
		for (int i = 0; i < dim; i++) {
			// g[rnum][i] = line[i] - '0';
			addNum(line[i] - '0', rnum, i);
		}
		rnum++;
	}
	in.close();
}


void printv(vector<short>& v) {
	for (short &x : v) {
		cout << x << ", ";
	}
	cout << '\n';
}

int main() {
	fname = test ? "test.txt" : "input.txt";
	dim = test ? 10 : 100;
	shift = test ? (partA ? 4 : 6) : (partA ? 7 : 9);
	rsize = 1 << shift;
	lower = rsize - 1;

	// readFileA();
	// printv(g[9]);
	readFileB();
	printv(g[10]);

	solve15b();

	
	return 0;
}
