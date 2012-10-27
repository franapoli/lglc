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
