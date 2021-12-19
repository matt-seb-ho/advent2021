#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;

struct Entry {
	vector<string> f10;
	vector<string> ou4;
};

vector<string> str2vec(string& s, int num) {
	stringstream ss(s);
	vector<string> res(num);
	string token;
	int idx = 0;
	while (getline(ss, token, ' ')) {
		res[idx++] = token;
	}
	return res;
}


void readfile(string fname, vector<Entry>& input) {
	ifstream in(fname);
	if (in.fail())
		return;
	int baridx;
	string line, front, back;
	while (getline(in, line)) {
		baridx = line.find('|');
		front = line.substr(0, baridx - 1);
		back = line.substr(baridx + 2);
		Entry en;
		en.f10 = str2vec(front, 10);
		en.ou4 = str2vec(back, 4);
		input.push_back(en);
	}
	in.close();
}	

void solve8a(vector<Entry>& input) {
	int counter = 0, si;
	for (Entry& en : input) {
		for (string& s : en.ou4) {
			si = s.size();
			if (si == 2 || si == 4 || si == 3 || si == 7) {
				counter++;
			}
		}
	}
	cout << "8a: " << counter << endl;
}

unordered_map<int, int> known;

bool has(string& s, string& sub) {
	for (char c : sub) {
		if (s.find(c) == string::npos) {
			return false;
		}
	}
	return true;
}

int overlap(string& beeg, string& smol) {
	int res = 0;
	for (char c : smol) {
		if (beeg.find(c) != string::npos) {
			res++;
		}
	}
	return res;
}

unordered_map<string, int> decipher(Entry& en) {
	vector<string> ciper(10, "");
	unordered_map<int, vector<string>> hm;
	for (string& s : en.f10) {
		sort(s.begin(), s.end());
		if (known.find(s.size()) != known.end()) {
			ciper[known[s.size()]] = s;
		} else {
			hm[s.size()].push_back(s);
		}
	}
	for (string& s : hm[5]) {
		if (has(s, ciper[1])) {
			ciper[3] = s;
			break;
		}
	}
	for (string& s : hm[6]) {
		if (!has(s, ciper[1])) {
			ciper[6] = s;
		} else if (has(s, ciper[3])) {
			ciper[9] = s;
		} else {
			ciper[0] = s;
		}
	}
	for (string& s : hm[5]) {
		if (overlap(ciper[6], s) == 5) {
			ciper[5] = s;
		} else if (ciper[3] != s) {
			ciper[2] = s;
		}
	}
	unordered_map<string, int> cip;
	for (int i = 0; i < 10; i++) {
		cip[ciper[i]] = i;
	}
	return cip;
}

int fourDigNum(vector<string>& v, unordered_map<string, int>& ciper) {
	int res = 0;
	res += ciper[v[0]] * 1000;
	res += ciper[v[1]] * 100;
	res += ciper[v[2]] * 10;
	res += ciper[v[3]];
	return res;
}

void solve8b(vector<Entry>& input) {
	int res = 0;
	string decoded;
	unordered_map<string, int> ciper;
	for (Entry& en : input) {
		for (string& s : en.ou4) {
			sort(s.begin(), s.end());
		}
		ciper = decipher(en);
		res += fourDigNum(en.ou4, ciper);
	}
	cout << "8b: " << res << endl;
}
			

int main() {
	known[2] = 1;
	known[3] = 7;
	known[4] = 4;
	known[7] = 8;
	vector<Entry> input;
	readfile("input.txt", input);
	// readfile("input.txt", input);
	// solve8a(input);
	solve8b(input);
	// cout << input.size() << endl;
	return 0;
}
