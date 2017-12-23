#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

namespace sylib
{/*{{{*/

class FileStream
{/*{{{*/
	public:
		FileStream (string filename);
		bool readOneLine (vector<string>& output, char split_char);
	private:
		ifstream ifs_;
};/*}}}*/

}/*}}}*/
