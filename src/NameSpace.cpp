/* 
   The MIT License (MIT)

   Copyright (c) 2012-2013 Francesco Napolitano, franapoli@gmail.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include "NameSpace.h"
#include "Linkable.h"

NameSpace::NameSpace() {
	// TODO Auto-generated constructor stub

}

NameSpace::~NameSpace() {
	// TODO Auto-generated destructor stub
}

Linkable *NameSpace::getObject(std::string s) {
	std::map<std::string, Linkable *>::iterator i;
	i = _symvalues.find(s);
	if (i == _symvalues.end())
		return 0;
	return i->second;
}

std::ostream& NameSpace::operator>>(std::ostream &str) {
	std::map<std::string, Linkable *>::iterator i;
	str << "Symbol table {" << std::endl;
	int j = 0;

	if (_symvalues.empty()) {
		str << "<empty>" << std::endl << "}" << std::endl;
		return str;
	}
	for (i = _symvalues.begin(); i != _symvalues.end(); i++, j++) {
		str << i->first << ":\t";
		*(i->second) >> str;
		str << std::endl;
	}
	/*str << *i << std::endl << "}" << std::endl;*/
	return str;

}
