/*
 * SymbolTable.h
 *
 *  Created on: 06/mag/2010
 *      Author: ciccio
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
