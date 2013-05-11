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

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "NameSpace.h"
#include "Linkable.h"
#include <vector>
#include <string>

class SymbolTable {
public:
	SymbolTable();
	virtual ~SymbolTable();
	void addNameSpace(std::string name, NameSpace &n) {
		_namespaces[name] = &n;
	}
	void addSymbol(std::string space, std::string symbol, Linkable *l) {
		_namespaces.find(space)->second->AddSymbol(symbol, l);
	}

	Linkable *getSymbol(std::string symbol) {
		return _namespaces.find("global")->second->getObject(symbol);
	}
	Linkable *getSymbol(std::string space, std::string symbol) {
		Linkable *l = _namespaces.find(space)->second->getObject(symbol);
		if (l)
			return l;
		else
			return _namespaces.find("global")->second->getObject(symbol);
	}

private:
	std::map<std::string, NameSpace *> _namespaces;

};

#endif /* SYMBOLTABLE_H_ */
