#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Day 3.1: given list of binary numbers, find product of epilon and gamma
// where epsilon = most common bit in that slot, gamma is opposite

string fname = "input.txt";
const int NUM_BITS = 12;
// string fname = "test.txt";
// const int NUM_BITS = 5;

void solve3a() {
	ifstream in(fname);
	if (in.fail()) 
		return;
	int vote[NUM_BITS] = {0};
	string line;
	while (getline(in, line)) {
		// cout << line << endl;
		for (int i = 0; i < NUM_BITS; i++) {
			// cout << line[i] << " ";
			vote[i] += (line[i] == '1' ? 1 : -1);
		}
		// cout << endl;
	}
	in.close();
	
	int power = 1, gamma = 0, epsilon = 0;
	for (int i = NUM_BITS - 1; i >= 0; i--) {
		if (vote[i] > 0) {
			gamma += power;
		} else {
			epsilon += power;
		}
		power <<= 1;
	}

	cout << gamma * epsilon << endl;
}

// Day 3.2

struct TreeNode {
	int precount = 0;
	TreeNode* zer = nullptr;
	TreeNode* one = nullptr;
	~TreeNode() {
		delete zer;
		delete one;
	}
};

// Day 3.2: get product of o2 and co2 ratings where o2r = keep removing
int count(TreeNode* node) {
	if (node) {
		return node->precount;
	}
	return -1;
}

void solve3b() {
	ifstream in(fname);
	if (in.fail()) 
		return;
	// int vote[NUM_BITS] = {0};
	string line;
	TreeNode* root = new TreeNode();
	TreeNode* node;
	// fileread builds tree
	while (getline(in, line)) {
		node = root;
		for (int i = 0; i < NUM_BITS; i++) {
			// count how many times you pass through this node
			node->precount++;
			if (line[i] == '1') {
				if (!node->one) {
					node->one = new TreeNode();
				} 
				node = node->one;
			} else {
				if (!node->zer) {
					node->zer = new TreeNode();
				}
				node = node->zer;
			}
		}
	}
	in.close();
	
	string gstr = "", estr = "";
	TreeNode* gamma = root;
	TreeNode* epsil = root;
	// solution: once you have things in a tree, you can just pick a branch to only
	// search the correct remaining strings. If there is no choice, pick that one
	for (int i = 0; i < NUM_BITS; i++) {
		// since count = -1 for nullptr, this one always picks the non-null branch
		if (count(gamma->one) >= count(gamma->zer)) {
			gamma = gamma->one;
			gstr += '1';
		} else {
			gamma = gamma->zer;
			gstr += '0';
		}
		if (epsil->zer == nullptr || 
			((count(epsil->one) < count(epsil->zer)) && epsil->one)) {
			epsil = epsil->one;
			estr += '1';
		} else {
			epsil = epsil->zer;
			estr += '0';
		}
	}

	int gval = stoi(gstr, 0, 2);
	int eval = stoi(estr, 0, 2);
	cout << "gval: " << gval << " ::: eval: " << eval << endl;
	cout << stoi(gstr, 0, 2) * stoi(estr, 0, 2) << endl;

	delete root;
}


int main() {
	// solve3a();
	solve3b();
	return 0;
}
