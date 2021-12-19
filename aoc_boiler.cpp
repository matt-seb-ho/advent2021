#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using std::string, std::vector, std::cout;

string fname;
bool test = 1;

int main() {
	fname = test ? "test.txt" : "input.txt";
	return 0;
}
