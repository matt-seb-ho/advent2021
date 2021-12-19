#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using std::cout, std::string, std::endl;
// string fname = "test.txt";
string fname = "input.txt";
string polymer, backup;
std::unordered_map<int, long> polymap;
const int TWO_CHARS = 65536;
// const int ONE_CHAR = 256;
const int LOWER8 = (1 << 8) - 1;
char temps[TWO_CHARS];

void readFile() {
	std::ifstream in(fname);
	if (in.fail())
		return;
	
	std::getline(in, polymer);
	string line, pair;
	// throw away spacer line
	std::getline(in, line);

	memset(temps, ' ', TWO_CHARS);
	int key;
	while (std::getline(in, line)) {
		key = (line[0] << 8) + line[1];
		temps[key] = line[line.size() - 1];
	}
	in.close();
}

void applyRules(string& base) {
	// cout << 'a';
	if (base == "") {
		return;
	}
	int key;
	string res = "";
	char c = base[0];
	for (int i = 1; i < base.size(); i++) {
		res += c;
		key = c << 8;
		key += base[i];
		if (temps[key] != ' ') {
			res += temps[key];
		}
		c = base[i];
	}
	base = res + c;
}

// brute force rule application
void solve14a(int n) {
	for (int i = 0; i < n; i++) {
		// cout << i << ' ';
		applyRules(polymer);
		// cout << "polymer len: " << polymer.size() << endl;
	}
	long long counts[26] = {0};
	for (char c : polymer) {
		counts[c - 'A']++;
	}
	long long beeg = -1, smol = 1e18;
	for (int i = 0; i < 26; i++) {
		beeg = std::max(beeg, counts[i]);
		if (counts[i])
			smol = std::min(smol, counts[i]);
	}
	cout << "14a: " << beeg - smol << '\n';
}

void initPolymap() {
	char c = polymer[0];
	int key;
	for (int i = 1; i < polymer.size(); i++) {
		key = c << 8;
		key += polymer[i];
		polymap[key]++;
		c = polymer[i];
	}
}

void polymapStep() {
	std::unordered_map<int, long> next;
	int nextKey, l, r, m;
	for (auto& p : polymap) {
		if (temps[p.first] != ' ') {
			l = p.first >> 8;
			r = p.first & LOWER8;
			m = temps[p.first];
			nextKey = (l << 8) + m;
			next[nextKey] += p.second;
			nextKey = (m << 8) + r;
			next[nextKey] += p.second;
		}
	}
	polymap = next;
}

void printMap() {
	cout << "-- polymap --\n";
	char c1, c2;
	for (auto& p : polymap) {
		c1 = (p.first >> 8);
		c2 = (p.first & ((1 << 8) - 1));
		cout << c1 << c2 << ": " << p.second << '\n';
	}
	cout << "-------------\n";
}

void solve14b(int n) {
	backup = polymer;
	initPolymap();
	// printMap();
	for (int i = 0; i < n; i++) {
		polymapStep();
		// printMap();
		// cout << "distinct keys: " << polymap.size() << endl;
	}
	// printMap();
	long long counts[26] = {0};
	int l, r;
	for (auto& p : polymap) {
		l = p.first >> 8;
		r = p.first & LOWER8;
		counts[l - 'A'] += p.second;
		counts[r - 'A'] += p.second;
	}
	long long beeg = -1, smol = 1e18;
	
	for (int i = 0; i < 26; i++) {
		if (i + 'A' == backup[0] || i + 'A' == backup[backup.size() - 1]) {
			counts[i]++;
		}
		counts[i] >>= 1;
		beeg = std::max(beeg, counts[i]);
		if (counts[i])
			smol = std::min(smol, counts[i]);
	}
	cout << "14b: " << beeg - smol << '\n';
}

int main() {
	readFile();
	cout << "polymer: " << polymer << '\n';
	

	// 14a
	// solve14a(10);
	solve14b(40);
	
	return 0;
}
