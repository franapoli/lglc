/*
 * Copyright (c) 2012 Francesco Napolitano.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/gpl.html
 * 
 * Contributors:
 *     Francesco Napolitano - initial API and implementation
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
