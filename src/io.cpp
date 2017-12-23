#include <sylib/io.h>

using namespace sylib;
using namespace std;

FileStream::FileStream (string filename)
{/*{{{*/
	ifs_ = ifstream(filename);
	if (!ifs_) {
		cerr<<"Cannot open "<<filename<<endl;
		return;
	}
}/*}}}*/

bool FileStream::readOneLine (vector<string>& output, char split_char)
{/*{{{*/
	string str;
	if (!getline(ifs_, str)) return false;
	stringstream ss(str);
	while (getline(ss, str, split_char)) {
		output.push_back(str);
	}
	return true;
}/*}}}*/
