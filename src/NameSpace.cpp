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
