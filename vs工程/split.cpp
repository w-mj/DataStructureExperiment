#include <sstream>
#include <cctype>
#include "split.h"
using namespace std;
vector<double> splitd(string s) {
	vector<double> result;
	double n;
	stringstream ss;
	string::iterator numBegin = s.begin();
	string::iterator iter = s.begin();
	while (!isdigit(*iter) && iter != s.end())
		iter++;
	numBegin = iter;
	for (; iter != s.end(); iter++) {
		if (!isdigit(*iter) && *iter!='.') {
			if (numBegin == iter) {
				numBegin++;
				continue;
			}
			ss << string(numBegin, iter);
			ss >> n;
			ss.clear();
			result.push_back(n);
			numBegin = iter + 1;
		}
	}
	ss.clear();
	if (numBegin != iter) {
		string sss = string(numBegin, iter);
		ss << sss;
		ss >> n;
		result.push_back(n);
	}
	return result;
}

vector<int> split(string s) {
	vector<double> a = splitd(s);
	vector<int> r;
	for (double x : a)
		r.push_back((int)x);
	return r;
}