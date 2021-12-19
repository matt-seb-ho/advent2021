#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;
// global vars
// string fname = "test.txt";
string fname = "input.txt";
vector<string> file;
unordered_map<char, int> scoreTableA;
unordered_map<char, int> scoreTableB;
unordered_map<char, char> bracketTypes;

void readFile() {
	ifstream in(fname);
	if (in.fail())
		return;
	string line;
	while (getline(in, line)) {
		file.push_back(line);
	}
	in.close();
}

// find corrupted lines
char corruptionCheck(string& line) {
	stack<char> s;
	for (char c : line) {
		if (bracketTypes.find(c) != bracketTypes.end()) {
			s.push(bracketTypes[c]);
		} else {
			if (c == s.top()) {
				s.pop();
			} else {
				// cout << "bad line: " << line << endl;
				return c;
			}
		}
	}
	return ' ';
}

void solve10a() {
	int res = 0;
	char c;
	for (string& line : file) {
		c = corruptionCheck(line);
		if (c != ' ') {
			res += scoreTableA[c];
		}
	}
	cout << "10a: " << res << endl;
}

long long scoreLine(string& line) {
	stack<char> s;
	for (char c : line) {
		if (bracketTypes.find(c) != bracketTypes.end()) {
			s.push(bracketTypes[c]);
		} else {
			if (s.empty() || c != s.top()) {
				return 0;
			} else {
				s.pop();
			}
		}
	}
	long long res = 0;
	while (!s.empty()) {
		res *= 5;
		res += scoreTableB[s.top()];
		s.pop();
	}
	return res;
}

void solve10b() {
	vector<long long> scores;
	long long score;
	for (string& line : file) {
		score = scoreLine(line);
		if (score) {
			cout << "score: " << score << endl;
			scores.push_back(score);
		}
	}
	cout << scores.size() << endl;
	sort(scores.begin(), scores.end());
	cout << "10b: " << scores[scores.size() / 2] << endl;
}

int main() {
	bracketTypes['('] = ')';
	bracketTypes['['] = ']';
	bracketTypes['{'] = '}';
	bracketTypes['<'] = '>';
	scoreTableA[')'] = 3;
	scoreTableA[']'] = 57;
	scoreTableA['}'] = 1197;
	scoreTableA['>'] = 25137;
	scoreTableB[')'] = 1;
	scoreTableB[']'] = 2;
	scoreTableB['}'] = 3;
	scoreTableB['>'] = 4;

	readFile();
	// cout << file.size() << endl;
	// solve10a();
	solve10b();
	return 0;
}
