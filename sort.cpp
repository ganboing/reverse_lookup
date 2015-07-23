#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

vector<string> split_str(const string& str, char delim){
	stringstream s(str);
	vector<string> ret;
	string sub;
	while(s.good()){
		getline(s, sub, delim);
		ret.push_back(move(sub));
	}
	return ret;
}

struct str_rev_less {
	bool operator ()(const string& lhs, const string& rhs) {
		reverse_iterator<decltype(lhs.data())>
		last1(lhs.data()), first1(lhs.data()+lhs.size()),
		last2(rhs.data()), first2(rhs.data()+rhs.size());
		return lexicographical_compare(first1, last1, first2, last2);
	}
};

int main(int, char**){
	string line;
	map<vector<string>, string> rev_domain;
	while(getline(cin, line)){
		auto splited = split_str(line, ' ');
		try{
			if(splited.size() != 5){
				fprintf(stderr, "(size=%zu)", splited.size());
				throw runtime_error("check element");
			}
			if(splited[2] != "IN" || splited[3] != "PTR"){
				fprintf(stderr, "[2]=%s, [3]=%s", splited[1].c_str(), splited[2].c_str());
				throw runtime_error("wrong format");
			}
			auto hosts = split_str(splited[4], '.');
			reverse(hosts.begin(), hosts.end());
			rev_domain.insert(make_pair(hosts, line));
		}
		catch(exception& e){
			fprintf(stderr, "invalid line %s, reason=%s\n", line.c_str(), e.what());
			exit(-1);
		}
	}
	for(auto i=rev_domain.begin(), j= rev_domain.end();i!=j;++i){
		cout << "[";
		for(auto p=i->first.begin(), q=i->first.end();p!=q;++p){
			cout << "." << *p;
		}
		cout <<"] ";
		cout << i->second << endl;
	}
	return 0;
}
