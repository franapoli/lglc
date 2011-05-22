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

class Environment {
public:
	Environment();
	virtual ~Environment();
	void addNameSpace(std::string name, NameSpace &n)
	{_namespaces[name]=&n;}
	void addSymbol(std::string space, std::string symbol, Linkable *l)
	{_namespaces.find(space)->second->AddSymbol(symbol, l);}

	Linkable *getSymbol(std::string symbol)
	{return _namespaces.find("global")->second->GetObject(symbol);}
	Linkable *getSymbol(std::string space, std::string symbol)
	{Linkable *l =_namespaces.find(space)->second->GetObject(symbol);
	if(l)
		return l;
		else return _namespaces.find("global")->second->GetObject(symbol);}


private:
	std::map<std::string, NameSpace *> _namespaces;

};

#endif /* SYMBOLTABLE_H_ */
