#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
// string fname = "input.txt";
// int days = 256;
string fname = "test.txt";
int days = 256;

vector<long long> fileread(string f) {
	ifstream in(f);
	if (in.fail())
		return {};
	string line;
	getline(in, line);
	in.close();
	
	stringstream ss(line);
	string token;
	int timer;
	vector<long long> res(9, 0);
	while (getline(ss, token, ',')) {
		timer = stoi(token);
		// cout << "timer: " << timer << ", ";
		res[timer]++;
	}
	return res;
}

// Day 6.1: return how many fish after 80 days

template <typename T>
void printv(vector<T> v) {
	for (T& x : v) {
		cout << x << ", ";
	}
	cout << endl;
}

// transition from day to day
void passDay(vector<long long>& fish) {
	long long zerofish = fish[0];
	// count down all timers
	for (int i = 1; i < 9; i++) {
		fish[i - 1] = fish[i];
	}
	// fish at timer 0 loop back to 6, and new fish start with 8
	fish[6] += zerofish;
	fish[8] = zerofish;
}
	
long long solve6a(vector<long long>& fish, int days) {
	for (int i = 0; i < days; i++) {
		passDay(fish);
	}
	long long res = 0;
	for (long long& num : fish) {
		res += num;
	}
	return res;
}

int main() {
	vector<long long> fish = fileread(fname);
	printv(fish);
	cout << solve6a(fish, days) << endl;
	return 0;
}
