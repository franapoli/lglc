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

#ifndef SYMBOLS_H_
#define SYMBOLS_H_

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <ostream>
#include "Linkable.h"
#include "Function.h"

class NameSpace {
public:
	NameSpace();
	virtual ~NameSpace();
	void AddSymbol(std::string s, Linkable *l) {
		_symvalues.insert(std::pair<std::string, Linkable*>(s, l));
	}
	bool HasSymbol(std::string s) {
		return !(_symvalues.find(s) == _symvalues.end());
	}
	Linkable *getObject(std::string s);
	std::ostream& operator>>(std::ostream &);
	std::string getName() const {
		return _name;
	}

	void setName(std::string _name) {
		this->_name = _name;
	}

private:
	std::map<std::string, Linkable *> _symvalues;
	std::map<std::string, Function *> __functions;
	std::string _name;
};

#endif /* SYMBOLS_H_ */
