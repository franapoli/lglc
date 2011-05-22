/*
 * SymbolTable.cpp
 *
 *  Created on: 06/mag/2010
 *      Author: ciccio
 */

#include "SymbolTable.h"
#include "NameSpace.h"

SymbolTable::SymbolTable() {
	NameSpace *global = new NameSpace;
	this->addNameSpace("global", *global);

}

SymbolTable::~SymbolTable() {
	// TODO Auto-generated destructor stub
}
