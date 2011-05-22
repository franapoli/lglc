/*
 * SymbolTable.cpp
 *
 *  Created on: 06/mag/2010
 *      Author: ciccio
 */

#include "Environment.h"
#include "NameSpace.h"

Environment::Environment() {
	NameSpace *global = new NameSpace;
	this->addNameSpace("global", *global);

}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
}
