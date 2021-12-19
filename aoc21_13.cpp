#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <utility>
#include <algorithm>

using namespace std;
struct Dot {
	Dot() {}
	Dot(int n)
		: x(n / 892), y(n % 892) {}
	Dot(int a, int b) 
		: x(a), y(b) {}
	int x, y;
	friend ostream& operator<<(ostream& o, Dot d);
};

ostream& operator<<(ostream& o, Dot d) {
	o << d.x << ", " << d.y;
	return o;
}

int convert(Dot d) {
	return 892 * d.x + d.y;
}

Dot convert(int n) {
	return Dot(n / 892, n % 892);
}

int convert(int x, int y) {
	return 892 * x + y;
}

class Paper {
	public:
		void fold(int n) {
			if (n < 0) {
				foldx(-n);
				return;
			}
			if (n > 0) {
				foldy(n);
				return;
			}
			cout << "fold at zero. big sad.\n";
		}
				
		void foldx(int f) {
			cout << "folding along x=" << f << '\n';
			unordered_set<int> next;
			int x, y, updatedWidth;
			if (f > (w / 2)) {
				// left side bigger
				updatedWidth = f;
				for (int p : points) {
					x = p / 892;
					y = p % 892;
					if (x == f)
						continue;
					if (x > f) {
						x = updatedWidth - (x - f);
					}
					next.insert(convert(x, y));
				}
			} else {
				// right side bigger
				updatedWidth = w - f - 1;
				for (int p : points) {
					x = p / 892;
					y = p % 892;
					if (x == f)
						continue;
					if (x < f) {
						x += (updatedWidth - f);
					} else {
						x = updatedWidth - (x - f);
					}
					next.insert(convert(x, y));
				}
			}
			w = updatedWidth;
			points = next;
		}

		void foldy(int f) {
			unordered_set<int> next;
			int x, y, updatedHeight;
			if (f > (h / 2)) {
				// top portion bigger
				updatedHeight = f;
				for (int p : points) {
					x = p / 892;
					y = p % 892;
					if (y == f)
						continue;
					if (y > f) {
						y = updatedHeight - (y - f);
					}
					next.insert(convert(x, y));
				}
			} else {
				// bottom portion bigger
				updatedHeight = h - f - 1;
				for (int p : points) {
					x = p / 892;
					y = p % 892;
					if (y == f)
						continue;
					if (y < f) {
						y += (updatedHeight - f);
					} else {
						y = updatedHeight - (y - f);
					}
					next.insert(convert(x, y));
				}
			}
			h = updatedHeight;
			points = next;
			cout << "yfold report: " << points.size() << " points, h: " << h << ", w: " << w << '\n';
			
		}

		void print() {
			int p;
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					p = convert(j, i);
					cout << (points.find(p) != points.end() ? '#' : '.');
				}
				cout << '\n';
			}
		}

	public:
		int w, h;
		unordered_set<int> points;
} paper;

// string fname = "test.txt";
string fname = "input.txt";
// x = neg, y = pos
vector<int> folds;

void readFile() {
	ifstream in(fname);
	if (in.fail())
		return;
	string line;
	int delim, fold, x, y, maxX = -1, maxY = -1;
	while (getline(in, line)) {
		if (line.size() == 0) {
			continue;
		}
		if (line[0] == 'f') {
			delim = line.find('=');
			fold = stoi(line.substr(delim + 1));
			if (line[delim - 1] == 'x') {
				fold *= -1;
			}
			folds.push_back(fold);
		} else {
			delim = line.find(',');
			x = stoi(line.substr(0, delim));
			y = stoi(line.substr(delim + 1));
			paper.points.insert(convert(x, y));
			maxX = max(maxX, x);
			maxY = max(maxY, y);
		}
		// cout << "line: " << line << endl;
	}
	paper.w = maxX + 1;
	paper.h = maxY + 1;
	in.close();
}

void reportEx(vector<int>& v) {
	cout << "min: "  << *min_element(v.begin(), v.end()) << endl;
	cout << "max: "  << *max_element(v.begin(), v.end()) << endl;
}


int main() {
	readFile();
	// cout << "before: " << paper.points.size() << endl;
	for (int fold : folds) {
		paper.fold(fold);
	}
	paper.print();
		

	return 0;
}
