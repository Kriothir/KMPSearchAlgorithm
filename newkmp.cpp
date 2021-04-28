#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

ofstream out;

string inputText(const string& pot) {
	ifstream input(pot);
	stringstream sstream;

	if (!input.is_open()) {
		return string();
	}

	sstream << input.rdbuf();
	return sstream.str();
}

void izpis_KMPnext(const int* polje, int len, std::vector <int> n) {
	for (int i = 0; i < len; i++) {
		out << polje[i] << ' ';
	}
	out << endl;
	for (int i : n) {
		out << i << ' ';
	}
	out << endl;
}


void KMP(const string& text, const string& vzorec) {
	int n = text.length();
	int m = vzorec.length();
	int* table = new int[m];
	std::vector<int> match;
	table[0] = -1;
	table[1] = 0;
	int k = 0;

	for (int l = 2; l < vzorec.length(); l++) {
		if (k == 0) {
			table[l] = 0;
		}
		if (k != 0) {
			k = table[k];
		}
		if (vzorec[l - 1] == vzorec[k]) {
			table[l] = k + 1;
			k++;
		}
	}
	string x = vzorec;
	string y = text;
	int j = 0;
	int i = 0;
	for (i = 0; i < m; ++i)
	{
		if (x[i] != y[j + i])
		{
			j = j + i - table[i];
			i = 0;
		}
		else if (x[i] == y[j + i])
		{
			if (i == (m - 1)) {
				match.push_back(j);
				j = j + m;
				i = 0;
			}
			else {
				continue;
			}
		}
		if (j >= n) {
			break;
		}
	}
	izpis_KMPnext(table, m, match);

}

int main(int argc, const char* const argv[]) {
	if (argc != 3) {
		return -1;
	}

	string text = inputText(argv[2]);
	string vzorec = argv[1];
	out.open("out.txt");

	if (!out) {
		return -2;
	}

	KMP(text, vzorec);
	return 0;
}