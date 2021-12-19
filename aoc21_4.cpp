#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Board {
  public:
	// methods
	Board() {}

	bool set(int num) {
		if (hm.find(num) == hm.end())
			return false;

		int idx = hm[num];
		gr[idx / 5][idx % 5] = true;
		return true;
	}

	bool winner() {
		// check rows
		bool good;
		for (int i = 0; i < 5; i++) {
			good = true;
			for (int j = 0; j < 5; j++) {
				good = (good && gr[i][j]);
				idcs[j] = convert(i, j);
			}
			if (good) {
				return true;
			}
		}

		// check columns
		for (int j = 0; j < 5; j++) {
			good = true;
			for (int i = 0; i < 5; i++) {
				good = (good && gr[i][j]);
				idcs[i] = convert(i, j);
			}
			if (good) {
				return true;
			}
		}
		return false;
	}

	int score() {
		unordered_map<int, int> reverse;
		for (auto& p : hm) {
			reverse[p.second] = p.first;
		}
		int res = 0;
		for (int i = 0; i < 25; i++) {
			if (!gr[i / 5][i % 5]) {
				res += reverse[i];
			}
		}
		return res * last;
	}

	static int convert(int y, int x) {
		return y * 5 + x;
	}

	// data
	unordered_map<int, int> hm;
	bool gr[5][5] = {{0}};
	static int idcs[5];
	static int last;
};

int Board::idcs[5] = {0};
int Board::last = 0;

void fileread(string& fname, vector<int>& nums, vector<Board>& boards) {
	ifstream in(fname);
	string line;
	int num;
	vector<int> board(25);

	getline(in, line);
	istringstream ss(line);
	string token;
	while (getline(ss, token, ',')) {
		nums.push_back(stoi(token));
	}

	while (in >> num) {
		Board b;
		b.hm[num] = 0;
		for (int i = 1; i < 25; i++) {
			in >> num;
			b.hm[num] = i;
		}
		boards.push_back(b);
	}
	in.close();

	cout << "board size: " << boards.size() << endl;
}

// Day 4.1: find score of first winner
int solve4a(vector<int>& nums, vector<Board>& boards) {
	for (int num : nums) {
		for (int i = 0; i < boards.size(); i++) {
			if (boards[i].set(num) && boards[i].winner()) {
				Board::last = num;
				// return i;
				return boards[i].score();
				// return i;
			}
		}
	}
	return -1;
}

// Day 4.2: find score of last winner
int solve4b(vector<int>& nums, vector<Board>& boards) {
	unordered_set<int> remain;
	for (int i = 0; i < boards.size(); i++)
		remain.insert(i);
	
	for (int num : nums) {
		for (int i = 0; i < boards.size(); i++) {
			if (remain.find(i) != remain.end() && 
				boards[i].set(num) && 
				boards[i].winner()) {

				remain.erase(i);
				if (remain.size() == 0) {
					Board::last = num;
					return boards[i].score();
				}
				// return i;
			}
		}
	}
	return -1;
}

void printv(vector<int>& v) {
	for (int x : v) {
		cout << x << ", ";
	}
	cout << endl;
}
			
int main() {
	string fname = "input.txt";
	vector<int> nums;
	vector<Board> boards;

	fileread(fname, nums, boards);
	// cout << "nums:\n";
	// printv(nums);

	cout << solve4a(nums, boards) << endl;
	cout << solve4b(nums, boards) << endl;

	// vector<vector<int>> boards;
	// printv(boards[98]);
	return 0;
}
